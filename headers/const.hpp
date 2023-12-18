#pragma once

constexpr int GAP = 4;
constexpr int ROWS = 30;
constexpr int COLUMNS = 15;
constexpr int CELL_SIZE = 25;
constexpr int LEFT_BORDER = 30, RIGHT_BORDER = 200, TOP_BORDER = 60,
              BOTTOM_BORDER = 30;
constexpr float WINDOW_X =
    (CELL_SIZE + GAP) * COLUMNS + GAP + LEFT_BORDER + RIGHT_BORDER;
constexpr float WINDOW_Y =
    (CELL_SIZE + GAP) * ROWS + GAP + TOP_BORDER + BOTTOM_BORDER;