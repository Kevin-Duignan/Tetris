#include "../headers/helper.h"
#include "../headers/colours.hpp"

void draw_cells(sf::RenderWindow &window, matrixType matrix) {

  sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  cell.setFillColor(sf::Color(180, 50, 20));

  sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  block.setFillColor(sf::Color(0, 255, 0));

  sf::RectangleShape background(sf::Vector2f(window_x, window_y));
  background.setFillColor(sf::Color(pastel_yellow_light));
  window.draw(background);

  sf::RectangleShape matrix_background(sf::Vector2f(
      (CELL_SIZE + GAP) * COLUMNS + GAP, (CELL_SIZE + GAP) * ROWS + GAP));
  matrix_background.setPosition(left_border, top_border);
  matrix_background.setFillColor(sf::Color(pastel_yellow_dark));
  window.draw(matrix_background);

  float x = GAP + left_border, y = GAP + top_border;

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
    x = GAP + left_border;
  }
}

void handle_key_presses(sf::Event &ev, TetrominoVariant &piece,
                        pieceCoords &start_piece, coords &offset,
                        matrixType &matrix) {
  std::cout << "Handling key press\n";
  switch (ev.key.code) {
  case sf::Keyboard::D:
  case sf::Keyboard::Right:
    std::cout << "Right key pressed\n";
    offset = movePiece(matrix, start_piece, 'r', offset);
    break;
  case sf::Keyboard::S:
  case sf::Keyboard::Down:
    std::cout << "Down key pressed\n";
    offset = movePiece(matrix, start_piece, 'd', offset);
    break;
  case sf::Keyboard::A:
  case sf::Keyboard::Left:
    std::cout << "Left key pressed\n";
    offset = movePiece(matrix, start_piece, 'l', offset);
    break;
  case (sf::Keyboard::Q):
    std::cout << "Q key pressed\n";
    std::visit(rotate, piece);
    for (auto &[c_x, c_y] : std::visit(get_block_coords, piece)) {
      auto [offset_x, offset_y] = offset;
      int newX = c_x + offset_x;
      int newY = c_y + offset_y;
      if (!is_valid_position(newX, newY, matrix)) {
        std::visit(revert_rotate, piece);
      }
    }
    start_piece = std::visit(get_block_coords, piece);
  default:
    break;
  }
}

void handle_game_tick(matrixType &matrix, TetrominoVariant &piece,
                      pieceCoords &start_piece, coords &offset,
                      sf::Clock &clock, sf::Clock &keyClock, sf::Time &keyTick,
                      sf::Time &gameTick) {

  if (shouldSeal(matrix, start_piece, offset) &&
      keyClock.getElapsedTime() > keyTick) {
    set_piece_cell_type(start_piece, offset, matrix, cellType::sealed);
    piece = std::move(choose_random(tetromino_piece_types));
    start_piece = std::visit(get_block_coords, piece);
    offset = std::make_tuple(0, 0);
  }
  if (clock.getElapsedTime() > gameTick) { // game tick
    clock.restart();                       // Reset the clock
    offset = movePiece(matrix, start_piece, 'd', offset);
  }
}

void set_piece_cell_type(pieceCoords &start_piece, coords &offset,
                         matrixType &matrix, cellType type) {
  for (auto [c_x, c_y] : start_piece) {
    auto [offset_x, offset_y] = offset;
    matrix[c_y + offset_y][c_x + offset_x] = std::to_underlying(type);
  }
}

bool is_valid_position(int x, int y, matrixType &matrix) {
  return (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS &&
          matrix[y][x] != std::to_underlying(cellType::active) &&
          matrix[y][x] != std::to_underlying(cellType::sealed));
}

// Choosing the random tetrimino
TetrominoVariant choose_random(std::array<TetrominoVariant, 7> pieces) {
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, pieces.size() - 1);

  int random_index = distrib(gen);
  TetrominoVariant random_piece_t = pieces.at(random_index);
  // Create a copy without knowing underlying type
  TetrominoVariant random_piece = std::visit(
      [](auto &&arg) -> TetrominoVariant {
        using T = std::decay_t<decltype(arg)>;
        return T(arg);
      },
      random_piece_t);
  return random_piece;
}