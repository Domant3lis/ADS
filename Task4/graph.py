from typing import List, Optional, Any, Dict, Tuple, Set
import re, itertools

# This graph implementation is non-oriented
class Graph:
	def __init__(self : 'Graph') -> None:
		self.connections : Dict[Any, List[Tuple[Any, int]]] = {}
		self.n : int = 0

	# def add_con_one_way(self, from_node : Any, to_node : Any, weight: int) -> None:
	# 	is_already_connected = False
	# 	if self.connections.get(from_node):
	# 		for ix in range(0, len(self.connections[from_node])):
	# 			if self.connections[from_node][ix][0] == to_node:
	# 				is_already_connected = True
	# 				break
			
	# 		# If element path to a node already exits update it
	# 		if is_already_connected:
	# 			self.connections[from_node][ix] = (to_node, weight)
	# 		else:
	# 			self.connections[from_node].append((to_node, weight))
		
	# 	else:
	# 		self.connections[from_node] = [(to_node, weight)]

	def add_connection(self, from_node : Any, to_node : Any, weight: int) -> None:
		is_already_connected = False
		# Branch when a node already exists
		if self.connections.get(from_node):
			# Checks if two nodes are already connected
			for ix in range(0, len(self.connections[from_node])):
				if self.connections[from_node][ix][0] == to_node:
					is_already_connected = True
					break
			
			# If element path to a node already exits update it
			# else add a connection
			if is_already_connected:
				self.connections[from_node][ix] = (to_node, weight)
			else:
				self.n += 1
				self.connections[from_node].append((to_node, weight))
		
		# Node doesn't exist; it is created
		else:
			self.n += 1
			self.connections[from_node] = [(to_node, weight)]
		
		# Updates the other to_node
		if is_already_connected:
				self.connections[to_node][ix] = (from_node, weight)
		else:
			if self.connections.get(to_node):
				self.connections[to_node].append((from_node, weight))
			else:
				self.connections[to_node] = [(from_node, weight)]

	def __str__(self) -> str:
		return str(self.connections) + "  No. of cons.: " + str(self.n)

	def parse(self, input : str, log = False) -> None:
		for line in input.split("\n"):
			data_str = re.split(' *-> *', line)
			if log: print(data_str)
			assert len(data_str) == 2, "Probably an incorrect or empty line"

			from_ = data_str[0]

			for s in re.split(' *; *', data_str[1]):
				to_ = re.split(' *, *', s)[0][1:]
				weight = re.split(' *, *', s)[1][:-1]

				self.add_connection(from_, to_, int(weight))
				# self.add_con_one_way(from_, to_, int(weight))
	
	def min(self) -> 'Graph':

		verts : Set = set()
		for p in self.connections:
			for vert in p:
				# 
				print('TODO')
				
		return self

	def check(self, from_node : Any, to_node : Any) -> bool:
		for con in self.connections[from_node]:
			if con[0] == to_node:
				return True
		return False


og = Graph()
og.parse(open('test1.txt', 'r').read(), False)
print(og)
print(og.check('A', 'F'))

# read('')