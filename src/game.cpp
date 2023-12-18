#include "../headers/game.hpp"
#include "../headers/colours.hpp"

// Debug
void print_coords(const coords &c) {
  std::cout << "(" << static_cast<int>(std::get<0>(c)) << ", "
            << static_cast<int>(std::get<1>(c)) << ")";
}

void draw_board(sf::RenderWindow &window) {

  sf::RectangleShape background(sf::Vector2f(WINDOW_X, WINDOW_Y));
  background.setFillColor(sf::Color(LIGHT_GRAY));
  window.draw(background);

  sf::RectangleShape matrix_border(
      sf::Vector2f((CELL_SIZE + GAP) * COLUMNS + GAP * 3,
                   (CELL_SIZE + GAP) * ROWS + GAP * 3));
  matrix_border.setPosition(LEFT_BORDER - GAP, TOP_BORDER - GAP);
  matrix_border.setFillColor(sf::Color(MIDNIGHT_BLUE));
  window.draw(matrix_border);

  sf::RectangleShape matrix_background(sf::Vector2f(
      (CELL_SIZE + GAP) * COLUMNS - GAP, (CELL_SIZE + GAP) * ROWS - GAP));
  matrix_background.setPosition(LEFT_BORDER + GAP, TOP_BORDER + GAP);
  matrix_background.setFillColor(sf::Color(DARK_GRAY));
  window.draw(matrix_background);
}

void draw_cells(sf::RenderWindow &window, matrixType &matrix,
                TetrominoVariant &piece) {

  sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  cell.setFillColor(sf::Color(180, 50, 20));

  // Draw the piece with assigned colour
  sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  auto piece_tag = std::visit([](auto &arg) { return arg.piece_tag; }, piece);

  sf::RectangleShape background(sf::Vector2f(WINDOW_X, WINDOW_Y));
  background.setFillColor(sf::Color(LIGHT_GRAY));
  window.draw(background);

  sf::RectangleShape matrix_background(sf::Vector2f(
      (CELL_SIZE + GAP) * COLUMNS + GAP, (CELL_SIZE + GAP) * ROWS + GAP));
  matrix_background.setPosition(LEFT_BORDER, TOP_BORDER);
  matrix_background.setFillColor(sf::Color(DARK_GRAY));
  window.draw(matrix_background);

  float x = GAP + LEFT_BORDER, y = GAP + TOP_BORDER;

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {

      auto cell = matrix[i][j];
      if (std::holds_alternative<non_sealed>(cell) &&
          std::get<non_sealed>(cell) == non_sealed::active) {
        auto [r, g, b] = PIECE_COLOURS_MAP.at(piece_tag);
        block.setFillColor(sf::Color(r, g, b));
        block.setPosition(x, y);
        window.draw(block);
      }

      else if (std::holds_alternative<sealed_piece>(cell)) {
        // Draw the colour of previous sealed pieces
        auto piece_tag = std::get<sealed_piece>(matrix[i][j]);
        auto [r, g, b] = PIECE_COLOURS_MAP.at(piece_tag);
        block.setFillColor(sf::Color(r, g, b));
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
                        matrixType &matrix, Score &score) {
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
    score.tick();
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
    } while (prev_offset != curr_offset);
    score.drop();
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
                      sf::Clock &clock, sf::Time &gameTick, Score &score) {

  if (clock.getElapsedTime() > gameTick) { // game tick
    if (shouldSeal(matrix, start_piece, offset)) {
      auto piece_type =
          std::visit([](auto &arg) { return arg.piece_tag; }, piece);
      set_piece_non_sealed(start_piece, offset, matrix, piece_type);
      piece = std::move(choose_random(tetromino_piece_types));
      start_piece = std::visit(
          [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); }, piece);
      offset = std::make_tuple(COLUMNS / 2 - 2, 0);
    }
    clock.restart(); // Reset the clock
    movePiece(matrix, start_piece, 'd', offset);
    score.tick();
  }
}

void set_piece_non_sealed(pieceCoords &start_piece, coords &offset,
                          matrixType &matrix, cell_type type) {
  for (auto [c_x, c_y] : start_piece) {
    auto [offset_x, offset_y] = offset;
    matrix[c_y + offset_y][c_x + offset_x] = type;
  }
}

bool is_valid_position(int x, int y, matrixType &matrix) {
  bool is_within_board = x >= 0 && x < COLUMNS && y >= 0 && y < ROWS;
  bool is_empty = std::holds_alternative<non_sealed>(matrix[y][x]) &&
                  std::get<non_sealed>(matrix[y][x]) == non_sealed::empty;
  return is_within_board && is_empty;
}

bool handle_game_over(matrixType &matrix) {
  auto first_row = matrix[0];
  for (auto &cell : first_row) {
    if (std::holds_alternative<sealed_piece>(cell)) {
      std::cout << "Game Over" << std::endl;
      return true;
    }
  }
  return false;
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
