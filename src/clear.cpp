#include "../headers/clear.h"
#include "../headers/const.h"
#include <iostream>

bool shouldClear(std::array<int, COLUMNS> row);

void clearRows(matrixType &matrix) {
  for (const auto &row : matrix) {
    if (shouldClear(row)) {
      return;
    }
    std::cout << '\n';
    std::cout << '\n';
  }
}

bool shouldClear(std::array<int, COLUMNS> row) {
  std::cout << '\n';
  for (int number : row) {
    std::cout << number;
    if (number != 2) {
      return false;
    }
  }
  std::cout << "yes";
  return true;
}
