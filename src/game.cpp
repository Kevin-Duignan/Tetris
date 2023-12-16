#include "../headers/game.hpp"
#include "../headers/colours.hpp"
#

void print_coords(const coords &c) {
  std::cout << "(" << static_cast<int>(std::get<0>(c)) << ", "
            << static_cast<int>(std::get<1>(c)) << ")";
}

void draw_cells(sf::RenderWindow &window, matrixType matrix) {

  sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  cell.setFillColor(sf::Color(180, 50, 20));

  sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  block.setFillColor(sf::Color(0, 255, 0));

  sf::RectangleShape background(sf::Vector2f(WINDOW_X, WINDOW_Y));
  background.setFillColor(sf::Color(pastel_yellow_light));
  window.draw(background);

  sf::RectangleShape matrix_background(sf::Vector2f(
      (CELL_SIZE + GAP) * COLUMNS + GAP, (CELL_SIZE + GAP) * ROWS + GAP));
  matrix_background.setPosition(LEFT_BORDER, TOP_BORDER);
  matrix_background.setFillColor(sf::Color(pastel_yellow_dark));
  window.draw(matrix_background);

  float x = GAP + LEFT_BORDER, y = GAP + TOP_BORDER;

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
    x = GAP + LEFT_BORDER;
  }
}

void handle_key_presses(sf::Event &ev, TetrominoVariant &piece,
                        pieceCoords &start_piece, coords &offset,
                        matrixType &matrix) {
  // Declaration here to prevent "jump bypasses variable initialisation" error
  bool valid_rotation = true;
  coords prev_offset;
  coords curr_offset;
  switch (ev.key.code) {
  case sf::Keyboard::D:
  case sf::Keyboard::Right:
    movePiece(matrix, start_piece, 'r', offset);
    break;
  case sf::Keyboard::S:
  case sf::Keyboard::Down:
    movePiece(matrix, start_piece, 'd', offset);
    std::cout << "prev_offset: ";
    print_coords(offset);
    break;
  case sf::Keyboard::A:
  case sf::Keyboard::Left:
    movePiece(matrix, start_piece, 'l', offset);
    break;
  case sf::Keyboard::Space:
    do {
      movePiece(matrix, start_piece, 'd', offset);
      prev_offset = offset;
      movePiece(matrix, start_piece, 'd', offset);
      curr_offset = offset;
      std::cout << "prev_offset: ";
      print_coords(prev_offset);
      std::cout << "\n";
      std::cout << "curr_offset: ";
      print_coords(curr_offset);
      std::cout << "\n";
    } while (prev_offset != curr_offset);
    break;
    offset = curr_offset;
  case (sf::Keyboard::Q):
    std::visit([](auto &arg) { arg.rotate(); }, piece);
    for (auto &[c_x, c_y] : std::visit(
             [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); },
             piece)) {
      auto [offset_x, offset_y] = offset;
      int newX = c_x + offset_x;
      int newY = c_y + offset_y;
      if (!is_valid_position(newX, newY, matrix)) {
        valid_rotation = false;
        break;
      }
    }
    if (!valid_rotation) {
      std::visit([](auto &arg) { arg.revertRotate(); }, piece);
    } else {
      start_piece = std::visit(
          [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); }, piece);
    }
    break;
  default:
    break;
  }
}

void handle_game_tick(matrixType &matrix, TetrominoVariant &piece,
                      pieceCoords &start_piece, coords &offset,
                      sf::Clock &clock, sf::Time &gameTick) {

  if (shouldSeal(matrix, start_piece, offset)) {
    set_piece_cell_type(start_piece, offset, matrix, cellType::sealed);
    piece = std::move(choose_random(tetromino_piece_types));
    start_piece = std::visit(
        [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); }, piece);
    offset = std::make_tuple(0, 0);
  }
  // if (clock.getElapsedTime() > gameTick) { // game tick
  //   clock.restart();                       // Reset the clock
  //   offset = movePiece(matrix, start_piece, 'd', offset);
  // }
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
