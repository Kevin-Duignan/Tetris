#include "../headers/matrix.hpp"

bool movePiece(matrixType &matrix, pieceCoords piece, char direction,
               coords &offset) {

  // Function to check if the new position is valid
  auto isValidPosition = [&](int x, int y) { // lambda!
    bool is_within_board = x >= 0 && x < COLUMNS && y >= 0 && y < ROWS;
    bool is_empty = std::holds_alternative<non_sealed>(matrix[y][x]) &&
                    std::get<non_sealed>(matrix[y][x]) == non_sealed::empty;
    return is_within_board && is_empty;
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

bool shouldSeal(matrixType matrix, pieceCoords piece, coords offset) {
  // Move piece down
  for (coords &c : piece) {
    int newX = std::get<0>(c) + std::get<0>(offset);
    int newY = std::get<1>(c) + std::get<1>(offset) + 1;
    bool is_within_board =
        newX >= 0 && newX < COLUMNS && newY >= 0 && newY < ROWS;
    bool empty_or_active =
        std::holds_alternative<non_sealed>(matrix[newY][newX]) &&
        (std::get<non_sealed>(matrix[newY][newX]) == non_sealed::active ||
         std::get<non_sealed>(matrix[newY][newX]) == non_sealed::empty);

    if (!is_within_board || !empty_or_active) {
      return true; // Can't move down
    }
  }
  return false;
}