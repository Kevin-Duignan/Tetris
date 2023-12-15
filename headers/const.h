#pragma once

constexpr int GAP = 4;
constexpr int ROWS = 20;
constexpr int COLUMNS = 12;
constexpr int CELL_SIZE = 25;
constexpr int left_border = 30, right_border = 200, top_border = 60,
              bottom_border = 30;
constexpr float window_x =
    (CELL_SIZE + GAP) * COLUMNS + GAP + left_border + right_border;
constexpr float window_y =
    (CELL_SIZE + GAP) * ROWS + GAP + top_border + bottom_border;