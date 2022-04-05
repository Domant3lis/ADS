# Task: Put N queens in a MxM triangle board
# such as each queen cannot be insight of another queen
# 
# Original wording:
# "Rasti N valdovių išdėstymą M trikampėje lentoje, kad jos viena kitos nekirstų."

import sys

def triangular_numbers(n):
    i, t = 1, 0
    while i <= n:
        yield t
        t += i
        i += 1
    
# Checks if a board is valid
def check_board(board, m):
    
    # checks rows
    # Works by counting 1s in a sublists
    ix = 0
    jx = 0
    for row in range(0, m):
        ix += row + 1
        if board[jx:ix].count(1) > 1:
            return False
        jx += row + 1
    
    # checks columns
    
    # builds a list of all possitions in that column
    possitions = list(triangular_numbers(m))
    for col in range(0, m):
        count = 0
        for pos in possitions:
            if board[pos]:
                count += 1
            if count > 1:
                return False
        
        possitions = list(map(lambda x: x + 1, possitions[1:]))

    # Checks diagonals
    possitions = list(triangular_numbers(m))
    for diag in range(0, m):
        
        count = 0
        for ix, pos in enumerate(possitions):
            if board[ix + pos]:
                count += 1
            
        if count > 1:
            return False
        
        possitions = possitions[1:]
    
    return True

# Checks if a queen doesn't collide with other
# True => is valid i.e. doesn't collide
# False => is NOT valid i.e. does collide
def check_cell(board, m, poz):
    # cell_count = sum(range(0, m + 1))

    # checks row
    # ix = 0
    # jx = 0
    # for l in range(0, m):
    #     ix += l + 1
    #     print(board[jx:ix])
    #     for ci, cell in enumerate(board[jx:ix]):
    #         # print(type(cell))
    #         if cell == 1 and ((ci + jx) != poz):
    #             # print(board[jx:ix])
    #             print(jx, ix, ci + jx, poz)
    #             return False
    #     jx += l + 1
        
        
    # checks column
    
    # checks the diagonal upper of the queen
    # checks the diagonal lower than the queen

    return True

# board is a list
def place(boards, board, poz, left):
    
    if left >= 0:
        ran = range(poz + 1, len(board) - left)
        for p in ran:
            board_copy = board.copy()
            board_copy[p] = 1
            
            #                                           this part: len(boards) == 0,
            #                                           can be commented out
            #                                           if one wishes to find all valid
            #                                           boards
            if left == 0 and check_board(board_copy, m) and len(boards) == 0:
                boards.insert(len(boards), board_copy)
            elif left >= 1:
                place(boards, board_copy, p, left - 1)
    
    return boards

# Matrixes are initialized with zeroes 
# 1 indicates a placed queen
# n is a number of queens
# m - m x m matrix dimension
def get_valid(m, n):
    return place([], [0] * sum(range(0, m + 1)), -1, n - 1)


def print_board(board, m):
    cell_count = sum(range(0, m + 1))
    if cell_count != len(board):
        raise Exception("This board is not a triangle", cell_count, len(board))

    ix = 0
    jx = 0
    for l in range(0, m):
        ix += l + 1
        print(board[jx:ix])
        jx += l + 1


if __name__ == '__main__':
    # Command line option parsing
    if len(sys.argv) == 3:
        m = int(sys.argv[1])  # M
        n = int(sys.argv[2])  # N
        print("Dim: ", m, " N:", n)
    else:
        print("Missing arguments")
        exit()
        
    # The interesting part
    boards = get_valid(m, n)
    
    # prints valid boards
    if len(boards) > 0:
        print("VALID BOARD FOUND: ")
        for board in boards:
            print_board(board, m)
            