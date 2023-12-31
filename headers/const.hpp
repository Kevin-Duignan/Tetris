#pragma once

constexpr int GAP = 4;
constexpr int ROWS =
    22; // 20 and 10 is regulation tetris. 22 because 2 ceiling rows.
constexpr int COLUMNS = 10;
constexpr int CELL_SIZE = 25;
constexpr int LEFT_BORDER = 30, RIGHT_BORDER = 200, TOP_BORDER = 80,
              BOTTOM_BORDER = 30;
constexpr float WINDOW_X =
    (CELL_SIZE + GAP) * COLUMNS + GAP + LEFT_BORDER + RIGHT_BORDER;
constexpr float WINDOW_Y =
    (CELL_SIZE + GAP) * (ROWS - 2) + GAP + TOP_BORDER + BOTTOM_BORDER;