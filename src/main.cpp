#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <iostream>

int constexpr GAP = 4, ROWS = 12, COLUMNS = 20, CELL_SIZE = 25;

// Types
typedef std::array<std::array<int, COLUMNS>, ROWS> matrixType;
typedef std::tuple<int, int> coords; // (x, y)
typedef std::vector<coords>
    pieceType; // NOT PERMANENT. TO be replaced with piece struct.

// Enums
enum blockType {
  empty,
  active,
  sealed
}; // empty means there is no block, acive means there is a block that can move,
   // sealed means there is a block that can't move.

// Prototypes
pieceType movePiece(matrixType &matrix, pieceType piece, char direction);

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
      if (matrix[j][i] == empty) {
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

  for (const auto &row : matrix) { // Debugging only!
    for (const auto &cell : row) {
      std::cout << cell << ' ';
    }
    std::cout << '\n';
  }

  auto window =
      sf::RenderWindow(sf::VideoMode((CELL_SIZE + GAP + 1) * ROWS - GAP,
                                     (CELL_SIZE + GAP + 1) * COLUMNS - GAP),
                       "CMake SFML Project");
  window.setFramerateLimit(144);

  sf::Clock clock;                      // starts the clock
  sf::Time gameTick = sf::seconds(0.2); // game tick every 1 second

  pieceType startPiece = {
      std::make_tuple(0, 0),
      std::make_tuple(1, 0)}; // Temp implementation, don't keep!

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    drawCells(window, matrix);
    window.display();

    // remove the old piece that is active
    for (coords c : startPiece) {
      matrix[std::get<0>(c)][std::get<1>(c)] = empty;
    }

    if (clock.getElapsedTime() > gameTick) { // game tick
      clock.restart();                       // Reset the clock

      startPiece = movePiece(matrix, startPiece, 'd');
    }

    // replace the moved (or not) active piece.
    for (coords c : startPiece) {
      matrix[std::get<0>(c)][std::get<1>(c)] = active;
    }

    // if move button clicked, try that move
  }
}
pieceType movePiece(matrixType &matrix, pieceType piece, char direction) {

  // Function to check if the new position is valid
  auto isValidPosition = [&](int x, int y) { // lambda!
    return (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS &&
            matrix[y][x] != sealed);
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