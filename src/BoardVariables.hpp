#pragma once

struct BoardVariables {

    // Information about the specific game shared between Game and GUI
    const char* EMPTY = " ";
    const char* X = "X";
    const char* O = "O";
    const char* DRAW = "D";
    static const char* playerTurn;
    bool isOver {};
 
    static const char* gameBoard[3][3];

    // Space around the borders
    static const int TOP_GAP = 150;
    static const int SIDE_GAP = 50;
    static const int BOTTOM_GAP = 50;
    static const int WIN_WIDTH = 500;
    static const int WIN_HEIGHT = WIN_WIDTH + TOP_GAP - BOTTOM_GAP;
    static const int BOARD_DIM = WIN_WIDTH - (2 * SIDE_GAP);
    static const int SQUARE_DIM = BOARD_DIM / 3;

    // Vertical board line x values
    static const int vertLineX1 = SIDE_GAP;
    static const int vertLineX2 = SIDE_GAP + SQUARE_DIM;
    static const int vertLineX3 = SIDE_GAP + 2 * SQUARE_DIM;
    static const int vertLineX4 = WIN_WIDTH - SIDE_GAP;

    // Horizontal board line y values
    static const int horLineY1 = TOP_GAP;
    static const int horLineY2 = TOP_GAP + SQUARE_DIM;
    static const int horLineY3 = TOP_GAP + 2 * SQUARE_DIM;
    static const int horLineY4 = WIN_HEIGHT - BOTTOM_GAP;

    // Text
    const char* currText;
};