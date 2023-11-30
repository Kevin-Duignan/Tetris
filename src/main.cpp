#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

int constexpr GAP = 7, ROW_COUNT = 12, COL_COUNT = 20, CELL_SIZE = 50;

void drawCells(sf::RenderWindow &window) {
  // Set size dynamically to ensure all cells are drawn
  window.setSize(sf::Vector2u((CELL_SIZE + GAP + 1) * ROW_COUNT,
                              (CELL_SIZE + GAP + 1) * COL_COUNT));

  sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  cell.setFillColor(sf::Color(180, 50, 20));

  float x = GAP, y = GAP;
  for (int i = 0; i < COL_COUNT; i++) {
    for (int j = 0; j < ROW_COUNT; j++) {
      cell.setPosition(x, y);
      window.draw(cell);
      x += CELL_SIZE + GAP;
    }
    y += CELL_SIZE + GAP;
    x = GAP;
  }
}

int main() {
  auto window =
      sf::RenderWindow(sf::VideoMode((CELL_SIZE + GAP + 1) * ROW_COUNT - GAP,
                                     (CELL_SIZE + GAP + 1) * COL_COUNT - GAP),
                       "CMake SFML Project");
  window.setFramerateLimit(144);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    drawCells(window);
    window.display();
  }
}