# Task: Put N queens in a MxM triangle board
# such as each queen cannot be insight of another queen
# 
# Original wording:
# "Rasti N valdovių išdėstymą M trikampėje lentoje, kad jos viena kitos nekirstų."

from cmath import pi
import sys
import numpy as np
# from itertools import product
import math

# NOTE: no checks are done to see if `row` and `col`
# are inside the dimensions of `board`
def check(board, row, col):
    triangle_foo = 1;

    # checks row
    for col_c in range(row):
        if board[row][col_c] != 0:
            return False
    
    # checks column
    for row_c in range(col, len(board)):
        if board[row_c][col] != 0:
            return False

    row_c = row
    col_c = col
    # checks the diagonal upper of the queen
    while row_c >= 0 and col_c >= 0:
        if board[row_c][col_c] != 0:
            return False        

        row_c -= 1
        col_c -= 1

    row_c = row
    col_c = col
    # checks the diagonal lower than the queen
    while row_c < len(board) and col_c < len(board):
        if board[row_c][col_c] != 0:
            return False

        row_c += 1
        col_c += 1

    return True

def n_choose_k(n, k):
    return math.factorial(n) / (math.factorial(k)*math.factorial(n-k))

# board is a list
def place(boards, board, poz, left):
    
    if left >= 0:
        ran = range(poz + 1, len(board) - left)
        for p in ran:
            board_copy = board.copy()
            board_copy[p] = 1
            
            if left == 0:
                boards.insert(len(boards), board_copy)
            elif left >= 1:
                place(boards, board_copy, p, left - 1)
                    
    return boards

# Matrixes are initialized with zeroes 
# 1 indicates a placed queen
# n is a number of queens
# m - m x m matrix dimension
def get_permutations(m, n):
    return place([], [0] * sum(range(0, m + 1)), -1, n - 1)

# __main__:
if len(sys.argv) == 3:
    m = int(sys.argv[1])  # M
    n = int(sys.argv[2])  # N
    print("Dim: ", m, " N:", n)
else:
    print("Missing arguments")
    exit()


def print_board(board, m):
    print("Board:")
    cell_count = sum(range(0, m + 1))
    if cell_count != len(board):
        raise Exception("This board is not a triangle", cell_count, len(board))

    ix = 0
    jx = 0
    print(board)
    for l in range(0, m):
        ix += l + 1
        print(board[jx:ix])
        jx += l + 1

    print("")

boards = get_permutations(m, n)
for board in boards:
    print_board(board, m)