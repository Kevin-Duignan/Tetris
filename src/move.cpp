#include "../headers/move.h"
#include "../headers/const.h"

pieceType movePiece(matrixType &matrix, pieceType piece, char direction) {

  // Function to check if the new position is valid
  auto isValidPosition = [&](int x, int y) { // lambda!
    return (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS &&
            matrix[y][x] != std::to_underlying(cellType::active) &&
            matrix[y][x] != std::to_underlying(cellType::sealed));
  };

  // Move piece left
  if (direction == 'l') {
    for (coords &c : piece) {
      int newX = std::get<0>(c) - 1;
      int newY = std::get<1>(c);
      if (!isValidPosition(newX, newY)) {
        return piece; // Can't move left
      }
    }
    for (coords &c : piece) {
      std::get<0>(c)--; // Move each block left
    }
  }

  // Move piece down
  else if (direction == 'd') {
    for (coords &c : piece) {
      int newX = std::get<0>(c);
      int newY = std::get<1>(c) + 1;
      if (!isValidPosition(newX, newY)) {
        return piece; // Can't move down
      }
    }
    for (coords &c : piece) {
      std::get<1>(c)++; // Move each block down
    }
  }

  // Move piece right
  else if (direction == 'r') {
    for (coords &c : piece) {
      int newX = std::get<0>(c) + 1;
      int newY = std::get<1>(c);
      if (!isValidPosition(newX, newY)) {
        return piece; // Can't move right
      }
    }
    for (coords &c : piece) {
      std::get<0>(c)++; // Move each block right
    }
  }

  return piece; // Return the updated piece
}

bool shouldSeal(matrixType matrix, pieceType piece) {
  // Move piece down
  for (coords &c : piece) {
    int newX = std::get<0>(c);
    int newY = std::get<1>(c) + 1;
    if (!(newX >= 0 && newX < COLUMNS && newY >= 0 && newY < ROWS &&
          matrix[newY][newX] != std::to_underlying(cellType::sealed))) {
      return true; // Can't move down
    }
  }
  return false;
}