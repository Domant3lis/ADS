from multiprocessing import connection
from tabnanny import check
from typing import List, Optional, Any, Dict, Tuple, Set
import re, itertools

# This graph implementation is non-oriented
class Graph:
	def __init__(self : 'Graph') -> None:
		self.connections : Dict[Any, Dict[Any, int]] = dict()
		self.n : int = 0

	def add_con(self : 'Graph', from_node : Any, to_node : Any, weight: int, both_ways : bool = False) -> None:
		# Vertex doesn't exist => update the number of them
		if self.connections.get(from_node) is None or self.connections.get(to_node) is None:
			self.n += 1
		elif self.connections[from_node].get(to_node) is None and self.connections[to_node].get(from_node) is None:
			self.n += 1
		
		# Node doesn't exist => initialize it
		if self.connections.get(from_node) is None:
			new = dict(); new[to_node] = weight
			self.connections[from_node] = new
		# Else update it
		else:
			self.connections[from_node][to_node] = weight

		# Set vertex both ways
		# ditto
		if both_ways:
			if self.connections.get(to_node) == None:
				new = dict(); new[from_node] = weight
				self.connections[to_node] = new
			else:
				self.connections[to_node][from_node] = weight

	def __str__(self : 'Graph') -> str:
		return str(self.connections) + "  No. of cons.: " + str(self.n)

	def parse(self : 'Graph', input : str, log : bool = False) -> None:
		for line in input.split("\n"):
			data_str = re.split(' *-> *', line)
			if log: print(data_str)
			assert len(data_str) == 2, "Parsing failed: probably an incorrect or empty line"

			from_ = data_str[0]

			for s in re.split(' *; *', data_str[1]):
				to_ = re.split(' *, *', s)[0][1:]
				weight = re.split(' *, *', s)[1][:-1]

				self.add_con(from_, to_, int(weight), True)
	
	def min(self) -> 'Graph':

		min_gr : 'Graph' = Graph()

		# Iterates through each
		for from_node, cons in self.connections.items():
			# print(from_node, cons)
			
			cons_ = list(cons.items())

			min : Optional[Tuple[Any, int]] = None

			# Searches for first valid vertex to compare to
			ix = 0
			while ix < len(cons_):
				if not min_gr.check_path_any_dir(from_node, cons_[ix][0]):
					min = cons_[ix]
					break
				# print(from_node, cons_[ix])
				ix += 1

			# If valid vertex is found then search for the 
			if not min is None:
				while ix < len(cons_):
					if (min[1] > cons_[ix][1]) and (not min_gr.check_path_any_dir(from_node, cons_[ix][0])):
						min = (cons_[ix][0], cons_[ix][1])
					ix += 1

				min_gr.add_con(from_node, min[0], min[1], True)
		
		return min_gr

	def check_node(self, node : Any) -> bool:
		if self.connections.get(node) is None:
			return False
		else:
			return True

	def check_path(self, from_node : Any, to_node : Any) -> bool:
		print('----')
		print(self.connections)
		print(from_node, to_node)

		cond : bool = False

		if not self.check_node(from_node):
			cond = False
			# return False
		
		if cond:
			for con in self.connections[from_node]:
				print('I: ', con, to_node)
				if con[0] == to_node:
					cond = True
					# return True
		print(cond)
		return cond

	def check_path_any_dir(self : 'Graph', node0 : Any, node1 : Any) -> bool:
		return self.check_path(node0, node1) or self.check_path(node1, node0)

og = Graph()
og.parse(open('test1.txt', 'r').read(), False)
print(og)
print('MIN: ')
print(og.min())
# print(og.check_path('I', 'J'))

# read('')