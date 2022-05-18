from multiprocessing import connection
from sre_constants import ANY
from tabnanny import check
from time import sleep
from typing import List, Optional, Any, Dict, Tuple, Set, OrderedDict
import re, itertools
from collections import OrderedDict

# This graph implementation is non-oriented
class Graph:
	def __init__(self : 'Graph') -> None:
		self.vertices : Dict[Any, Dict[Any, int]] = dict()
		self.vert_count : int = 0

	def add_edge(self : 'Graph', from_vertex : Any, to_vertex : Any, weight: int, both_ways : bool = False) -> None:
		# Edge doesn't exist => update the number of them
		if self.vertices.get(from_vertex) is None or self.vertices.get(to_vertex) is None:
			self.vert_count += 1
		elif self.vertices[from_vertex].get(to_vertex) is None and self.vertices[to_vertex].get(from_vertex) is None:
			self.vert_count += 1
		
		# Edge doesn't exist => initialize it
		if self.vertices.get(from_vertex) is None:
			new = dict(); new[to_vertex] = weight
			self.vertices[from_vertex] = new
		# Else update it
		else:
			self.vertices[from_vertex][to_vertex] = weight

		# Set vertex both ways
		# ditto
		# if both_ways:
		# 	if self.vertices.get(to_vertex) == None:
		# 		new = dict(); new[from_vertex] = weight
		# 		self.vertices[to_vertex] = new
		# 	else:
		# 		self.vertices[to_vertex][from_vertex] = weight

	def __str__(self : 'Graph') -> str:
		return str(self.vertices) + "  No. of edges.: " + str(self.vert_count) + "  No. of vertices: " + str(self.get_edge_count())

	def parse(self : 'Graph', input : str, log : bool = False) -> None:
		for line in input.split("\n"):
			data_str = re.split(' *-> *', line)
			if log: print(data_str)
			assert len(data_str) == 2, "Parsing failed: probably an incorrect or empty line"

			from_ = data_str[0]

			for s in re.split(' *; *', data_str[1]):
				to_ = re.split(' *, *', s)[0][1:]
				weight = re.split(' *, *', s)[1][:-1]

				# self.add_edge(from_, to_, int(weight), True)
				self.add_edge(from_, to_, int(weight), False)

	def copy(self : 'Graph') -> 'Graph':
		copy = Graph()
		copy.vertices = dict()
		for from_node, verts in self.vertices.items():
			copy.vertices[from_node] = dict()
			for vert, weight in verts.items():
				copy.vertices[from_node][vert] = weight

		copy.vert_count = self.vert_count
		return copy

	def get_edges(self : 'Graph') -> List[Tuple[int, Any, Any]]:
		edges : List[Tuple[int, Any, Any]] = list()
		for from_ver, verts in self.vertices.items():
			for to_ver, weight in verts.items():
				
				alread_included = False
				for _, from_, to_ in edges:
					if ((from_ == from_ver and to_ == to_ver) or (from_ == to_ver and to_ == from_ver)):
						alread_included = True
						break

				if not alread_included:
					edges.append((weight, from_ver, to_ver))
		return edges
	
	def get_edge_count(self : 'Graph') -> int:
		edges : Set[Any] = set()

		for from_ver, verts in self.vertices.items():
			edges.add(from_ver)
			for to_ver, _ in verts.items():
				edges.add(to_ver)

		return len(edges)

	def is_cyclical(self : 'Graph') -> bool:
		visited_edges : List[Any] = list()

		def __cycl(vert : Any) -> None:
			if not self.vertices.get(vert) is None:
				for vert in list(self.vertices[vert]):
					visited_edges.append(vert)
					__cycl(vert)

		for vert in list(self.vertices):
			visited_edges = []
			visited_edges.append(vert)
			__cycl(vert)

			cond = False
			# if visit has more than two of the same element return True
			for visit in visited_edges:
				if visited_edges.count(visit) > 1:
					return True

		return False

	def min(self : 'Graph') -> 'Graph':
		# sorts edges by their weight
		edges = self.get_edges()
		edges.sort(key=lambda x: x[0])
		edges.reverse()

		min_gr : 'Graph' = Graph()

		ix = 0
		while ix < self.get_edge_count():

			try:
				edge = edges.pop()
			except:
				break
			
			test = min_gr.copy()
			test.add_edge(edge[1], edge[2], edge[0])
			t = test.is_cyclical()
			if not t:
				min_gr.add_edge(edge[1], edge[2], edge[0])

				ix += 1
		
		return min_gr

og = Graph()
og.parse(open('test1.txt', 'r').read(), False)
print(og)
print('MIN: ')
min = og.min()
print(min)

import matplotlib.pyplot as plt
import networkx as nx

viz = nx.Graph()
viz_min = nx.Graph()

for edge in og.get_edges():
	viz.add_edge(edge[1], edge[2])

nx.draw_networkx(viz)
plt.show()

for edge in min.get_edges():
	viz_min.add_edge(edge[1], edge[2])

nx.draw_networkx(viz_min)
plt.show()