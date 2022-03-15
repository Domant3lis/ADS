# Task: Put N queens in a MxM triangle board
# such as each queen cannot be insight of another queen
# 
# Original wording:
# "Rasti N valdovių išdėstymą M trikampėje lentoje, kad jos viena kitos nekirstų."

from array import array
import sys
import numpy as np

# Matrixes are initialized with zeroes 
# 1 indicates a placed queen
def brute(m, n):
    board = np.zeros((m, m))
    queens = n

    triangle_foo = 1;
    for row in range(len(board)):
        # print(row)
        for column in range(triangle_foo):
            if check(board, row, column) and queens != 0:
                board[row][column] = 1
                queens -= 1
        triangle_foo += 1
    
    return board, queens

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

# Matrixes are initialized with zeroes
# 1 indicates a placed queen
def smart(m, n):
    board = np.zeros((m, m))

    row = 0
    col = 0
    
    while row < len(board) and col < len(board) and col < n:
        board[row][col] = 1
        row += 2
        col += 1

    return board, col

if len(sys.argv) == 3:
    m = int(sys.argv[1])  # M
    n = int(sys.argv[2])  # N
    print("Dim: ", m, " N:", n)
else:
    print("Missing arguments")
    exit()

# board, queens = brute(m, n)
# print(board)

# if queens != n:
#     print("Not possible to place this many queens")


board, queens = smart(m, n)
print(board)

if queens != n:
    print("Not possible to place this many queens")

