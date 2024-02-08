"""
Tic Tac Toe Player
"""

import math
from copy import deepcopy

X = "X"
O = "O"
EMPTY = None

def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    # X gets the first move (9 empties), then alternates
    empty_count = sum([i.count(EMPTY) for i in board])
    if empty_count % 2 == 0: return O
    else: return X


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    act = set()

    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                act.add((i, j))
    return act


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    # Deep copy of the board, leaving the original board unchanged
    board_cpy = deepcopy(board)
    if board_cpy[action[0]][action[1]] != EMPTY: raise Exception("This square is already taken")
    else: board_cpy[action[0]][action[1]] = player(board)
    return board_cpy


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    if terminal(board): 
        win = utility(board)
        if win == 1: return X 
        elif win == -1: return O 
        else: return None
    else: return None
    

def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    # If all squares are full (draw)
    if sum([i.count(EMPTY) for i in board]) == 0: return True

    # If there are 3 in a row (someone wins):
    for i in range(3):
        # Row
        if (board[i][0] == board[i][1] == board[i][2]) and board[i][0] != EMPTY: return True
        # Column
        elif (board[0][i] == board[1][i] == board[2][i]) and board[0][i] != EMPTY: return True
    
    # Diagonals
    if (board[0][0] == board[1][1] == board[2][2]) and board[0][0] != EMPTY: return True
    elif board[0][2] == board[1][1] == board[2][0] and board[1][1] != EMPTY: return True

    else: return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    winner = None

    for i in range(3):
        if (board[i][0] == board[i][1] == board[i][2]) and board[i][0] != EMPTY: winner = board[i][0] 
        elif (board[0][i] == board[1][i] == board[2][i]) and board[0][i] != EMPTY: winner = board[0][i]

    if (board[0][0] == board[1][1] == board[2][2]) and board[0][0] != EMPTY: winner = board[0][0]
    elif board[0][2] == board[1][1] == board[2][0] and board[1][1] != EMPTY: winner = board[0][2] 
    
    if winner == X: return 1
    elif winner == O: return -1
    else: return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if player(board) == X: v, best_action = vmax(board)
    elif player(board) == O: v, best_action = vmin(board)
    
    return best_action


def vmax(board):

    v, best_action = -100, None

    if terminal(board): return utility(board), best_action

    v = -100
    for action in actions(board):
        v_new, _ = vmin(result(board, action))
        if v_new > v:
            v = v_new
            best_action = action
    
    return v, best_action

        
def vmin(board):
    
    v, best_action = 100, None

    if terminal(board): return utility(board), best_action

    for action in actions(board):
        v_new, _ = vmax(result(board, action))
        if v_new < v:
            v = v_new
            best_action = action
    
    return v, best_action
