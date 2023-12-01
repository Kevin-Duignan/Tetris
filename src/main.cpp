#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <iostream>

int constexpr GAP = 4, ROWS = 12, COLUMNS = 20, CELL_SIZE = 25;

// Types
typedef std::array<std::array<int, COLUMNS>, ROWS> matrixType;

void drawCells(sf::RenderWindow &window, matrixType matrix) {
  // Set size dynamically to ensure all cells are drawn
  window.setSize(sf::Vector2u((CELL_SIZE + GAP + 1) * ROWS,
                              (CELL_SIZE + GAP + 1) * COLUMNS));

  sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  cell.setFillColor(sf::Color(180, 50, 20));

  sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  block.setFillColor(sf::Color(255, 0, 0));
  float x = GAP, y = GAP;
  for (int i = 0; i < COLUMNS; i++) {
    for (int j = 0; j < ROWS; j++) {
      if (matrix[j][i] == 0) {
        cell.setPosition(x, y);
        window.draw(cell);
      } else { // there is a block in that spot
        block.setPosition(x, y);
        window.draw(block);
      }
      x += CELL_SIZE + GAP;
    }
    y += CELL_SIZE + GAP;
    x = GAP;
  }
}

int main() {
  matrixType matrix;
  for (auto &row : matrix) {
    std::fill(row.begin(), row.end(), 0);
  }
  matrix[1][2] = 1;

  for (const auto &row : matrix) {
    for (const auto &cell : row) {
      std::cout << cell << ' ';
    }
    std::cout << '\n';
  }

  auto window =
      sf::RenderWindow(sf::VideoMode((CELL_SIZE + GAP) * ROWS + GAP,
                                     (CELL_SIZE + GAP) * COLUMNS + GAP),
                       "CMake SFML Project");
  window.setFramerateLimit(144);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    drawCells(window, matrix);
    window.display();
  }
}