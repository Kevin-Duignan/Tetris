#include "const.h"
#include "tetromino.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <iostream>

using namespace std::literals;

// Types
using matrixType = std::array<std::array<int, COLUMNS>, ROWS>;
using coords = std::tuple<int, int>; // (x, y)
// NOT PERMANENT. TO be replaced with piece struct.
using pieceType = std::vector<coords>;

// Prototypes
pieceType movePiece(matrixType &matrix, pieceType piece, char direction);
void printGrid(matrixType matrix); // debugging only
bool shouldSeal(matrixType matrix, pieceType piece);

void drawCells(sf::RenderWindow &window, matrixType matrix) {

  sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  cell.setFillColor(sf::Color(180, 50, 20));

  sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  block.setFillColor(sf::Color(0, 255, 0));

  float x = GAP, y = GAP;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (matrix[i][j] == std::to_underlying(cellType::empty)) {
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

  std::cout << __cplusplus << '\n';
  matrixType matrix;
  for (auto &row : matrix) {
    std::fill(row.begin(), row.end(), 0);
  }

  auto window =
      sf::RenderWindow(sf::VideoMode((CELL_SIZE + GAP) * COLUMNS + GAP,
                                     (CELL_SIZE + GAP) * ROWS + GAP),
                       "CMake SFML Project");
  window.setFramerateLimit(144);

  sf::Clock clock;                      // starts the clock
  sf::Time gameTick = sf::seconds(0.5); // game tick every 1 second

  sf::Clock keyClock;                  // starts the clock
  sf::Time keyTick = sf::seconds(0.1); // game tick every 1 second
  pieceType startPiece = {
      std::make_tuple(0, 0), std::make_tuple(1, 0),
      std::make_tuple(1, 1)}; // Temp implementation, don't keep!

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    printGrid(matrix);
    window.clear();
    drawCells(window, matrix);
    window.display();

    // remove the old piece that is active
    for (coords c : startPiece) {
      matrix[std::get<1>(c)][std::get<0>(c)] =
          std::to_underlying(cellType::empty);
    }
    if (keyClock.getElapsedTime() > keyTick) { // game tick
      if (shouldSeal(matrix, startPiece)) {
        for (coords c : startPiece) {
          matrix[std::get<1>(c)][std::get<0>(c)] =
              std::to_underlying(cellType::sealed);
        }
        startPiece = {std::make_tuple(5, 0), std::make_tuple(5, 1),
                      std::make_tuple(6, 1), std::make_tuple(6, 0)};
        continue;
      } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          // left key is pressed: move our character
          startPiece = movePiece(matrix, startPiece, 'r');
          keyClock.restart();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          // left key is pressed: move our character
          startPiece = movePiece(matrix, startPiece, 'd');
          keyClock.restart();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          // left key is pressed: move our character
          startPiece = movePiece(matrix, startPiece, 'l');
          keyClock.restart();
        }
      }
    }

    if (clock.getElapsedTime() > gameTick) { // game tick
      clock.restart();                       // Reset the clock

      startPiece = movePiece(matrix, startPiece, 'd');
    }

    // replace the moved (or not) active piece.
    for (coords c : startPiece) {
      matrix[std::get<1>(c)][std::get<0>(c)] =
          std::to_underlying(cellType::active);
    }
  }

  // if move button clicked, try that move
}
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
void printGrid(matrixType matrix) {
  constexpr auto guide =
      "a b c d e f g h i j k l m n o p q r s t u v w x y z"sv;
  std::cout << "  " << guide.substr(0, matrix[0].size() * 2) << "\n";
  for (auto i{0UL}; const auto &row : matrix) { // Debugging only!
    std::cout << guide[i] << ' ';
    for (const auto &cell : row) {
      std::cout << cell << ' ';
    }
    std::cout << '\n';
    i += 2;
  }
  std::cout << '\n';
  std::cout << '\n';
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