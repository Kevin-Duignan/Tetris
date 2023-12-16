#include "../headers/matrix.hpp"

coords movePiece(matrixType &matrix, pieceCoords piece, char direction,
                 coords offset) {

  // Function to check if the new position is valid
  auto isValidPosition = [&](int x, int y) { // lambda!
    return (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS &&
            matrix[y][x] != std::to_underlying(cellType::active) &&
            matrix[y][x] != std::to_underlying(cellType::sealed));
  };

  auto [offset_x, offset_y] = offset;

  // Move piece left
  if (direction == 'l') {
    for (auto &[c_x, c_y] : piece) {
      int newX = c_x + offset_x - 1;
      int newY = c_y + offset_y;
      if (!isValidPosition(newX, newY)) {
        return offset; // Can't move left
      }
    }
    return std::make_tuple(offset_x - 1, offset_y);
  }

  // Move piece down
  else if (direction == 'd') {
    for (auto &[c_x, c_y] : piece) {
      int newX = c_x + offset_x;
      int newY = c_y + offset_y + 1;
      if (!isValidPosition(newX, newY)) {
        return offset; // Can't move down
      }
    }
    return std::make_tuple(offset_x, offset_y + 1);
  }

  // Move piece right
  else if (direction == 'r') {
    for (auto &[c_x, c_y] : piece) {
      int newX = c_x + offset_x + 1;
      int newY = c_y + offset_y;
      if (!isValidPosition(newX, newY)) {
        return offset; // Can't move right
      }
    }
    return std::make_tuple(offset_x + 1, offset_y);
  }
  return offset;
}

bool shouldSeal(matrixType matrix, pieceCoords piece, coords offset) {
  // Move piece down
  for (coords &c : piece) {
    int newX = std::get<0>(c) + std::get<0>(offset);
    int newY = std::get<1>(c) + std::get<1>(offset) + 1;
    if (!(newX >= 0 && newX < COLUMNS && newY >= 0 && newY < ROWS &&
          matrix[newY][newX] != std::to_underlying(cellType::sealed))) {
      return true; // Can't move down
    }
  }
  return false;
}