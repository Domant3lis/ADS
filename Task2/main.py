from array import array
import sys
import numpy as np

# Matrixes are initialized with zeroes 
# 1 means a queen is placed there
# 2 means this place is seen by some queen

def brute(m, n):
    board = np.zeros((m, m))
    # board = np.array([[1, 0, 0, 0], [2, 3, 0, 0], [4, 5, 6, 0], [7, 8, 9, 10]])

    triangle_foo = 1;
    for row in range(len(board)):
        # print(row)
        for column in range(triangle_foo):
            board[row][column] = 1;
        triangle_foo += 1
    
    return board

# NOTE: no checks are done to see if `row` and `col`
# are inside the dimensions of `board`
def check(board, row, col):
    triangle_foo = 1;
    for row in range(len(board)):
        # print(row)
        for column in range(triangle_foo):
            no_op()
        triangle_foo += 1

    return 

def no_op():
    return 0;

if len(sys.argv) > 2:
    dim = int(sys.argv[1])  # M
    queen_num = int(sys.argv[2])  # N
    print("Dim: ", dim, " N:", queen_num)
else:
    exit

print(brute(dim, queen_num))
