#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

int constexpr GAP = 7, ROW_COUNT = 12, COL_COUNT = 20, CELL_SIZE = 50;

void drawCells(sf::RenderWindow &window) {
  float length = 100, gap = 10;
  sf::RectangleShape squareCell(sf::Vector2f(10.f, 10.f));
  squareCell.setFillColor(sf::Color(180, 50, 20));
  squareCell.setSize(sf::Vector2f(length, length));

  float x = 10, y = 10;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 7; j++) {
      squareCell.setPosition(x, y);
      window.draw(squareCell);
      x += length + gap;
    }
    y += length + gap;
    x = gap;
  }
}

int main() {
  auto window = sf::RenderWindow({670u, 1000u}, "CMake SFML Project");
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