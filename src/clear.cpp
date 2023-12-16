#include "../headers/clear.h"
#include "../headers/const.h"
#include <iostream>

bool shouldClear(std::array<int, COLUMNS> row);
void moveRowsDown(matrixType &matrix, int movable);

int clear_rows(           // clears rows, and returns how many it cleared.
    matrixType &matrix) { // consider updating so it goes from the bottom first.
  int i = 0;
  int cleared = 0;
  for (auto &row : matrix) {
    if (shouldClear(row)) {
      std::fill(row.begin(), row.end(), 0);
      moveRowsDown(matrix, i);
      cleared++;
    }
    i++;
  }
  return cleared;
}

bool shouldClear(std::array<int, COLUMNS> row) {
  for (int number : row) {
    if (number != 2) {
      return false;
    }
  }
  return true;
}

void moveRowsDown(matrixType &matrix, int movable) {
  for (int i = movable; i > 0; i--) {
    matrix[i] = matrix[i - 1];
  }
}
