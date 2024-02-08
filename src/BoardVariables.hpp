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
    const int TOP_PADDING = 150;
    const int SIDE_PADDING = 50;
    const int BOTTOM_PADDING = 50;
    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = WIN_WIDTH + TOP_PADDING - BOTTOM_PADDING;
    const int BOARD_DIM = WIN_WIDTH - (2 * SIDE_PADDING);
    const int SQUARE_DIM = BOARD_DIM / 3;

    // Vertical board line x values
    const int vertLineX1 = SIDE_PADDING;
    const int vertLineX2 = SIDE_PADDING + SQUARE_DIM;
    const int vertLineX3 = SIDE_PADDING + 2 * SQUARE_DIM;
    const int vertLineX4 = WIN_WIDTH - SIDE_PADDING;

    // Horizontal board line y values
    const int horLineY1 = TOP_PADDING;
    const int horLineY2 = TOP_PADDING + SQUARE_DIM;
    const int horLineY3 = TOP_PADDING + 2 * SQUARE_DIM;
    const int horLineY4 = WIN_HEIGHT - BOTTOM_PADDING;

    // Text
    const char* currText;
};