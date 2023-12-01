#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

int constexpr GAP = 4, ROWS = 12, COLUMNS = 20, CELL_SIZE = 25;

void drawCells(sf::RenderWindow &window) {

  sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  cell.setFillColor(sf::Color(180, 50, 20));

  float x = GAP, y = GAP;
  for (int i = 0; i < COLUMNS; i++) {
    for (int j = 0; j < ROWS; j++) {
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
      sf::RenderWindow(sf::VideoMode((CELL_SIZE + GAP + 1) * ROWS - GAP,
                                     (CELL_SIZE + GAP + 1) * COLUMNS - GAP),
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