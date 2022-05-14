from typing import List, Optional, Any, Dict, Tuple
import re

# This graph implementation is non-oriented
class Graph:
	def __init__(self : 'Graph') -> None:
		self.connections : Dict[Any, List[Tuple[Any, int]]] = {}

	def add_connection(self, from_node : Any, to_node : Any, weight: int) -> None:
		is_already_connected = False
		if self.connections.get(from_node):
			for ix in range(0, len(self.connections[from_node])):
				if self.connections[from_node][ix][0] == to_node:
					is_already_connected = True
					break
			
			# If element path to a node already exits update it
			if is_already_connected:
				self.connections[from_node][ix] = (to_node, weight)
			else:
				self.connections[from_node].append((to_node, weight))
		
		else:
			self.connections[from_node] = [(to_node, weight)]
		
		if is_already_connected:
				self.connections[to_node][ix] = (from_node, weight)
		else:
			if self.connections.get(to_node):
				self.connections[to_node].append((from_node, weight))
			else:
				self.connections[to_node] = [(from_node, weight)]

	def __str__(self) -> str:
		return str(self.connections)

	def parse(self, input : str) -> None:
		for line in input.split("\n"):
			data_str = re.split(' *-> *', line)
			assert len(data_str) == 2

			from_ = data_str[0]

			for s in re.split(' *; *', data_str[1]):
				to_ = re.split(' *, *', s)[0][1:]
				weight = re.split(' *, *', s)[1][:-1]

				self.add_connection(from_, to_, int(weight))

gr = Graph()
gr.parse(open('test.txt', 'r').read())
print(gr)

# read('')