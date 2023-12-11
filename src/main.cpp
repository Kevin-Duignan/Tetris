#include "../headers/const.h"
#include "../headers/move.h"
#include "../headers/tetromino.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std::literals;

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
  // EXAMPLE ONLY. Should not matter size of template int since
  // we will be choosing blocks randomly.
  Tetromino<2> i_piece(I_piece_t);
  pieceCoords startPiece = i_piece.getBlockCoords();

  matrixType matrix;
  for (auto &row : matrix) {
    std::fill(row.begin(), row.end(), 0);
  }

  auto isValidPosition = [&](int x, int y) {
    return (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS &&
            matrix[y][x] != std::to_underlying(cellType::active) &&
            matrix[y][x] != std::to_underlying(cellType::sealed));
  };

  auto assign_piece = [](auto &&arg) -> TetrominoVariant {
    using T = std::decay_t<decltype(arg)>;
    return T(arg);
  };

  auto rotate = [](auto &&arg) { arg.rotate(); };

  auto get_block_coords = [](auto &&arg) -> pieceCoords {
    return arg.getBlockCoords();
  };

  //  std::variant<Tetromino<1>, Tetromino<2>, Tetromino<4>>;
  TetrominoVariant piece_t = choose_random(tetromino_piece_types);
  // Create a copy without knowing underlying type
  TetrominoVariant piece = std::visit(assign_piece, piece_t);
  auto start_piece = std::visit(get_block_coords, piece);

  auto window =
      sf::RenderWindow(sf::VideoMode((CELL_SIZE + GAP) * COLUMNS + GAP,
                                     (CELL_SIZE + GAP) * ROWS + GAP),
                       "CMake SFML Project");
  window.setFramerateLimit(144);

  sf::Clock clock;                      // starts the clock
  sf::Time gameTick = sf::seconds(0.5); // game tick every 1 second

  sf::Clock keyClock;                  // starts the clock
  sf::Time keyTick = sf::seconds(0.1); // game tick every 1 second

  coords offset = std::make_tuple(0, 0); // (x, y)

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    // printGrid(matrix);
    window.clear();
    drawCells(window, matrix);
    window.display();

    // remove the old piece that is active
    for (auto [x, y] : startPiece) {
      matrix[std::get<1>(c) + std::get<1>(offset)]
            [std::get<0>(c) + std::get<0>(offset)] =
                std::to_underlying(cellType::empty);
    }
    if (keyClock.getElapsedTime() > keyTick) { // game tick
      if (shouldSeal(matrix, startPiece, offset)) {
        for (coords c : startPiece) {
          matrix[std::get<1>(c) + std::get<1>(offset)]
                [std::get<0>(c) + std::get<0>(offset)] =
                    std::to_underlying(cellType::sealed);
        }
        startPiece = i_piece.getBlockCoords();
        offset = std::make_tuple(0, 0);
        continue;
      } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          // left key is pressed: move our character
          offset = movePiece(matrix, startPiece, 'r', offset);
          keyClock.restart();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          // left key is pressed: move our character
          offset = movePiece(matrix, startPiece, 'd', offset);
          keyClock.restart();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          // left key is pressed: move our character
          offset = movePiece(matrix, startPiece, 'l', offset);
          keyClock.restart();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
          i_piece.rotate();
          bool valid = true;
          for (coords &c : i_piece.getBlockCoords()) {
            int newX = std::get<0>(c) + std::get<0>(offset);
            int newY = std::get<1>(c) + std::get<1>(offset);
            if (!isValidPosition(newX, newY)) {
              valid = false;
            }
          }
          if (valid) {
            startPiece = i_piece.getBlockCoords();
          }
          keyClock.restart();
        }
      }
    }

    if (clock.getElapsedTime() > gameTick) { // game tick
      clock.restart();                       // Reset the clock
      offset = movePiece(matrix, startPiece, 'd', offset);
    }

    // replace the moved (or not) active piece.
    for (coords c : startPiece) {
      matrix[std::get<1>(c) + std::get<1>(offset)]
            [std::get<0>(c) + std::get<0>(offset)] =
                std::to_underlying(cellType::active);
    }
  }

  // if move button clicked, try that move
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