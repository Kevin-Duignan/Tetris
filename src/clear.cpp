#include "../headers/clear.h"
#include "../headers/const.h"
#include <iostream>

bool shouldClear(std::array<int, COLUMNS> row);
void moveRowsDown(matrixType &matrix, int movable);

void clearRows(
    matrixType &matrix) { // consider updating so it goes from the bottom first.
  int i = 0;
  for (auto &row : matrix) {
    if (shouldClear(row)) {
      std::fill(row.begin(), row.end(), 0);
      moveRowsDown(matrix, i);
    }
    i++;
  }
}

bool shouldClear(std::array<int, COLUMNS> row) {
  for (int number : row) {
    if (number != 2) {
      return false;
    }
  }
  std::cout << "yes";
  return true;
}

void moveRowsDown(matrixType &matrix, int movable) {
  for (int i = movable; i > 0; i--) {
    matrix[i] = matrix[i - 1];
  }
}
