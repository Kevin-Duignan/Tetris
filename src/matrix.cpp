#include "../headers/matrix.hpp"

bool movePiece(matrixType &matrix, pieceCoords piece, char direction,
               coords &offset) {

  // Function to check if the new position is valid
  auto isValidPosition = [&](int x, int y) { // lambda!
    bool is_within_board = x >= 0 && x < COLUMNS && y >= 0 && y < ROWS;
    bool is_non_sealed = std::holds_alternative<non_sealed>(matrix[y][x]);
    return is_within_board && is_non_sealed;
  };

  auto [offset_x, offset_y] = offset;

  // Move piece left
  if (direction == 'l') {
    for (auto &[c_x, c_y] : piece) {
      int newX = c_x + offset_x - 1;
      int newY = c_y + offset_y;
      if (!isValidPosition(newX, newY)) {
        return false; // Can't move left
      }
    }
    offset = std::make_tuple(offset_x - 1, offset_y);
    return true;
  }

  // Move piece down
  else if (direction == 'd') {
    for (auto &[c_x, c_y] : piece) {
      int newX = c_x + offset_x;
      int newY = c_y + offset_y + 1;
      if (!isValidPosition(newX, newY)) {
        return false; // Can't move down
      }
    }
    offset = std::make_tuple(offset_x, offset_y + 1);
    return true;
  }

  // Move piece right
  else if (direction == 'r') {
    for (auto &[c_x, c_y] : piece) {
      int newX = c_x + offset_x + 1;
      int newY = c_y + offset_y;
      if (!isValidPosition(newX, newY)) {
        return false; // Can't move right
      }
    }
    offset = std::make_tuple(offset_x + 1, offset_y);
    return true;
  }
  // Otherwise
  return false;
}
