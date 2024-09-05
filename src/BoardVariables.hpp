#pragma once

struct BoardVariables {

    // Game state variables
    int s_PRELIM = 0;
    int s_IN_PLAY = 1;
    int s_END = 2;

    // Information about the specific game shared between Game and GUI
    char EMPTY = ' ';
    char X = 'X';
    char O = 'O';
    char DRAW = 'D';

    // Space around the borders
    int TOP_PADDING = 150;
    int SIDE_PADDING = 50;
    int BOTTOM_PADDING = 50;
    int WIN_WIDTH = 500;
    int WIN_HEIGHT = WIN_WIDTH + TOP_PADDING - BOTTOM_PADDING;
    int BOARD_DIM = WIN_WIDTH - (2 * SIDE_PADDING);
    int SQUARE_DIM = BOARD_DIM / 3;

    // Vertical board line x values
    int vertLineX1 = SIDE_PADDING;
    int vertLineX2 = SIDE_PADDING + SQUARE_DIM;
    int vertLineX3 = SIDE_PADDING + 2 * SQUARE_DIM;
    int vertLineX4 = WIN_WIDTH - SIDE_PADDING;

    // Horizontal board line y values
    int horLineY1 = TOP_PADDING;
    int horLineY2 = TOP_PADDING + SQUARE_DIM;
    int horLineY3 = TOP_PADDING + 2 * SQUARE_DIM;
    int horLineY4 = WIN_HEIGHT - BOTTOM_PADDING;

    // Text
    const char* currText;

    // Structures
    struct Board {
        char b[3][3];
    };

    struct Coordinate {
        int x{};
        int y{};
    };

    Coordinate NO_COORD = {-1, -1};
};