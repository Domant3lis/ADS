# Graph
Nodes:
1
2
3
4
5
6
7
8
9

Edges (directional):
1 -> 2
1 -> 3
1 -> 5
2 -> 3
2 -> 4
3 -> 2
3 -> 4
3 -> 5
4 -> 5
4 -> 7
4 -> 8
5 -> 1
5 -> 4
5 -> 6
5 -> 9
6 -> 7
6 -> 9
7 -> 5
7 -> 8
8 -> 9
9 -> 7

## Task
* Draw a visual graph (`Graph.svg`)
* Find node 6 then starting node is 1 using DFS (Depth First Search) and BFS (Breadth First Search)

### BFS
1 -> 2 3
Visited: 1
Stack: 2 3

2 -> 3 4
Visited: 1 2
Stack: 3 4

3 -> 2 4 5
Visited: 1 2 3
Stack: 4 5

4 -> 5 7 8
Visited: 1 2 3 4
Stack: 5 7 8

5 -> 4 6 9
Visited: 1 2 3 4 5
Stack: 7 8 6 9

7 -> 5 8
Visited: 1 2 3 4 5 7
Stack: 8 6 9

8 -> 9
Visited: 1 2 3 4 5 7 8
Stack: 6 9

6 -> 7 9
Visited: 1 2 3 4 5 7 8 6
Stack: 9

Final path: 1 2 3 4 5 7 8 6

### DFS
1 -> 2 3
Visited: 1
Stack: 2 3

2 -> 3 4
Visited: 1 2
Stack: 3 4

3 -> 2 4 5
Visited: 1 2 3
Stack: 4 5

4 -> 5 7 8
Visited: 1 2 3 4
Stack: 5 7 8

5 -> 4 6 9
Visited: 1 2 3 4 5
Stack: 6 9 7 8

6 -> 7 9
Visited: 1 2 3 4 5 6
Stack: 7 9 8

Final path: 1 2 3 4 5 6

