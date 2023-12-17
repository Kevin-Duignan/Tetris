#include "../headers/clear.hpp"
#include "../headers/score.hpp"
#include <iostream>

bool shouldClear(std::array<cell_type, COLUMNS> row);
void moveRowsDown(matrixType &matrix, int movable);

// clears rows, and returns how many it cleared.
int clear_rows(matrixType &matrix) {
  int i = 0;
  int cleared = 0;
  for (auto &row : matrix) {
    if (shouldClear(row)) {
      std::fill(row.begin(), row.end(), non_sealed::empty);
      moveRowsDown(matrix, i);
      cleared++;
    }
    i++;
  }
  return cleared;
}

bool shouldClear(std::array<cell_type, COLUMNS> row) {
  for (cell_type val : row) {
    if (std::holds_alternative<non_sealed>(val)) {
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
