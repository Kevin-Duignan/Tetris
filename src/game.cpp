#include "../headers/game.hpp"
#include "../headers/colours.hpp"

// Debug
void print_coords(const coords &c) {
  std::cout << "(" << static_cast<int>(std::get<0>(c)) << ", "
            << static_cast<int>(std::get<1>(c)) << ")";
}

void draw_gameover(sf::RenderWindow &window) {
  sf::RectangleShape box(sf::Vector2f(250, 200));
  box.setFillColor(sf::Color(LIGHT_GRAY));
  box.setPosition(LEFT_BORDER - GAP + 30, TOP_BORDER + 80);
  window.draw(box);

  sf::RectangleShape restart_box(sf::Vector2f(250, 60));
  restart_box.setFillColor(sf::Color(LIGHT_GRAY));
  restart_box.setPosition(LEFT_BORDER - GAP + 30, TOP_BORDER + 310);
  window.draw(restart_box);
}

void draw_board(sf::RenderWindow &window) {

  sf::RectangleShape background(sf::Vector2f(WINDOW_X, WINDOW_Y));
  background.setFillColor(sf::Color(LIGHT_GRAY));
  window.draw(background);

  sf::RectangleShape matrix_border(
      sf::Vector2f((CELL_SIZE + GAP) * COLUMNS + GAP * 3 + 3,
                   (CELL_SIZE + GAP) * (ROWS - 2) + GAP * 3 + 3));
  matrix_border.setPosition(LEFT_BORDER - GAP, TOP_BORDER - GAP);
  matrix_border.setFillColor(sf::Color(MIDNIGHT_BLUE));
  window.draw(matrix_border);

  sf::RectangleShape matrix_background(sf::Vector2f(
      (CELL_SIZE + GAP) * COLUMNS, (CELL_SIZE + GAP) * (ROWS - 2)));
  matrix_background.setPosition(LEFT_BORDER + GAP, TOP_BORDER + GAP);
  matrix_background.setFillColor(sf::Color(DARK_GRAY));
  window.draw(matrix_background);
}

void draw_cells(sf::RenderWindow &window, matrixType &matrix,
                TetrominoVariant &piece) {

  sf::RectangleShape empty_cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  empty_cell.setFillColor(sf::Color(180, 50, 20));

  // Draw the piece with assigned colour
  sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  auto piece_tag = std::visit([](auto &arg) { return arg.piece_tag; }, piece);

  float x = GAP + LEFT_BORDER, y = GAP + TOP_BORDER;

  // Pieces slowly reveal themselves
  for (int i = 2; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {

      auto cell = matrix[i][j];
      if (std::holds_alternative<non_sealed>(cell) &&
          std::get<non_sealed>(cell) == non_sealed::active) {
        auto [r, g, b] = PIECE_COLOURS_MAP.at(piece_tag);
        block.setFillColor(sf::Color(r, g, b));
        block.setPosition(x, y);
        window.draw(block);
      }

      else if (std::holds_alternative<non_sealed>(cell) &&
               std::get<non_sealed>(cell) == non_sealed::drop_shadow) {
        block.setFillColor(sf::Color(200, 200, 200, 50)); // Translucent
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
void draw_save_piece(sf::RenderWindow &window, TetrominoVariant &piece, float x,
                     float y) {
  // Draw the border
  sf::RectangleShape border(sf::Vector2f(160, 110)); // Adjust size as needed
  border.setFillColor(sf::Color::White);             // Adjust color as needed
  border.setPosition(x - 5, y - 5); // Adjust position as needed
  window.draw(border);

  // Draw the background
  sf::RectangleShape background(
      sf::Vector2f(150, 100));               // Adjust size as needed
  background.setFillColor(sf::Color::Black); // Adjust color as needed
  background.setPosition(x, y);
  window.draw(background);

  // Calculate the center of the background
  float startX = x + background.getSize().x / 6;
  float startY = y + background.getSize().y / 7;

  sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  auto piece_tag = std::visit([](auto &arg) { return arg.piece_tag; }, piece);

  for (auto [c_x, c_y] :
       std::visit([](auto &arg) -> pieceCoords { return arg.getBlockCoords(); },
                  piece)) {
    auto [r, g, b] = PIECE_COLOURS_MAP.at(piece_tag);
    block.setFillColor(sf::Color(r, g, b));
    // Adjust the position to center the piece
    block.setPosition(startX + (c_x * (CELL_SIZE + GAP)),
                      startY + (c_y * (CELL_SIZE + GAP)));
    window.draw(block);
  }
}
void draw_next_piece(sf::RenderWindow &window, TetrominoVariant &piece, float x,
                     float y) {
  // Draw the border
  sf::RectangleShape border(sf::Vector2f(160, 110)); // Adjust size as needed
  border.setFillColor(sf::Color::White);             // Adjust color as needed
  border.setPosition(x - 5, y - 5); // Adjust position as needed
  window.draw(border);

  // Draw the background
  sf::RectangleShape background(
      sf::Vector2f(150, 100));               // Adjust size as needed
  background.setFillColor(sf::Color::Black); // Adjust color as needed
  background.setPosition(x, y);
  window.draw(background);

  // Calculate the center of the background
  float startX = x + background.getSize().x / 6;
  float startY = y + background.getSize().y / 7;

  // Draw the piece
  sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  auto piece_tag = std::visit([](auto &arg) { return arg.piece_tag; }, piece);

  for (auto [c_x, c_y] :
       std::visit([](auto &arg) -> pieceCoords { return arg.getBlockCoords(); },
                  piece)) {
    auto [r, g, b] = PIECE_COLOURS_MAP.at(piece_tag);
    block.setFillColor(sf::Color(r, g, b));
    // Adjust the position to center the piece
    block.setPosition(startX + (c_x * (CELL_SIZE + GAP)),
                      startY + (c_y * (CELL_SIZE + GAP)));
    window.draw(block);
  }
}

void handle_key_presses(sf::Event &ev, TetrominoVariant &piece,
                        TetrominoVariant &next_piece,
                        std::optional<TetrominoVariant> &saved_piece,
                        pieceCoords &start_piece, coords &offset,
                        matrixType &matrix, Score &score, sf::Time &gameTick,
                        sf::Clock &clock, bool &save_lock) {
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
    if (movePiece(matrix, start_piece, 'd', offset)) {
      score.tick();
    }
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
      if (prev_offset != curr_offset) {
        score.drop();
      }
    } while (prev_offset != curr_offset);
    seal_piece(piece, next_piece, start_piece, offset, matrix, save_lock);
    break;
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
  case (sf::Keyboard::R):
    for (auto &row : matrix) {
      std::fill(row.begin(), row.end(), non_sealed::empty);
    }
    offset = std::make_tuple(COLUMNS / 2 - 2, 0);
    score.reset();
  case (sf::Keyboard::E):
    if (save_lock) { // we can't save when save_lock is on.
      break;
    }
    save_lock = true;
    if (saved_piece.has_value()) {
      auto temp = piece;
      piece = *saved_piece;
      saved_piece = temp;
      offset = std::make_tuple(COLUMNS / 2 - 2, 0);
      start_piece = std::visit(
          [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); }, piece);
      break;
    }
    // if there is no saved piece:
    saved_piece = piece;
    piece = next_piece;
    next_piece = assign_next_piece(piece);
    start_piece = std::visit(
        [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); }, piece);
    offset = std::make_tuple(COLUMNS / 2 - 2, 0);
    break;

  default:
    break;
  }
}

void handle_game_tick(matrixType &matrix, TetrominoVariant &piece,
                      TetrominoVariant &next_piece, pieceCoords &start_piece,
                      coords &offset, sf::Clock &clock, sf::Time &gameTick,
                      Score &score, bool &save_lock) {

  if (clock.getElapsedTime() > gameTick) { // game tick
    if (shouldSeal(matrix, start_piece, offset)) {
      seal_piece(piece, next_piece, start_piece, offset, matrix, save_lock);
    }
    clock.restart(); // Reset the clock
    movePiece(matrix, start_piece, 'd', offset);
    score.tick();
  }
}

void seal_piece(TetrominoVariant &piece, TetrominoVariant &next_piece,
                pieceCoords &start_piece, coords &offset, matrixType &matrix,
                bool &save_lock) {
  auto piece_type = std::visit([](auto &arg) { return arg.piece_tag; }, piece);
  set_piece_non_sealed(start_piece, offset, matrix, piece_type);
  piece = next_piece;
  next_piece = assign_next_piece(piece);
  start_piece = std::visit(
      [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); }, piece);
  offset = std::make_tuple(COLUMNS / 2 - 2, 0);
  save_lock = false;
}

void set_piece_non_sealed(pieceCoords &start_piece, coords &offset,
                          matrixType &matrix, cell_type type) {
  for (auto [c_x, c_y] : start_piece) {
    auto [offset_x, offset_y] = offset;
    matrix[c_y + offset_y][c_x + offset_x] = type;
  }
}

coords calculate_drop_position(matrixType &matrix, pieceCoords &start_piece,
                               coords &offset) {
  coords drop_offset = offset;
  while (movePiece(matrix, start_piece, 'd', drop_offset)) {
    // Keep moving the piece down until it can't move any further
  }
  return drop_offset;
}

void clear_drop_shadow(matrixType &matrix) {
  for (auto &row : matrix)
    for (auto &cell : row) {
      if (std::holds_alternative<non_sealed>(cell) &&
          std::get<non_sealed>(cell) == non_sealed::drop_shadow) {
        cell = non_sealed::empty;
      }
    }
}

bool shouldSeal(matrixType matrix, pieceCoords piece, coords offset) {
  // Move piece down
  for (coords &c : piece) {
    int newX = std::get<0>(c) + std::get<0>(offset);
    int newY = std::get<1>(c) + std::get<1>(offset) + 1;
    if (!is_valid_position(newX, newY, matrix)) {
      return true;
    }
  }
  return false;
}

bool is_valid_position(int x, int y, matrixType &matrix) {
  bool is_within_board = x >= 0 && x < COLUMNS && y >= 0 && y < ROWS;
  bool is_empty = std::holds_alternative<non_sealed>(matrix[y][x]);

  return is_within_board && is_empty;
}

bool handle_game_over(matrixType &matrix) { // If any out of bounds row has a
                                            // sealed piece, you lose.
  std::array<cell_type, COLUMNS> ceiling_rows[2] = {
      matrix[0], matrix[1]}; // rows that are out of bounds
  for (auto &row : ceiling_rows) {
    for (auto &cell : row) {
      if (std::holds_alternative<sealed_piece>(cell)) {
        return true;
      }
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

TetrominoVariant assign_next_piece(TetrominoVariant &piece) {
  // Choose the next piece (not same as curr piece)
  BaseTetromino::piece_tag_t curr_piece_tag;
  BaseTetromino::piece_tag_t next_piece_tag;
  TetrominoVariant next_piece = choose_random(tetromino_piece_types);
  do {
    next_piece = choose_random(tetromino_piece_types);
    curr_piece_tag = std::visit([](auto &arg) { return arg.piece_tag; }, piece);
    next_piece_tag =
        std::visit([](auto &arg) { return arg.piece_tag; }, next_piece);
  } while (curr_piece_tag == next_piece_tag);
  return next_piece;
}

void handle_event(sf::RenderWindow &window, sf::Event &ev,
                  TetrominoVariant &piece, TetrominoVariant &next_piece,
                  std::optional<TetrominoVariant> &saved_piece,
                  pieceCoords &start_piece, coords &offset, matrixType &matrix,
                  Score &score, sf::Time gameTick, sf::Clock clock,
                  bool &save_lock) {
  if (ev.type == sf::Event::Closed) {
    window.close();
  }
  if (ev.type == sf::Event::KeyPressed) {
    handle_key_presses(ev, piece, next_piece, saved_piece, start_piece, offset,
                       matrix, score, gameTick, clock, save_lock);
  }
}

void draw_game(sf::RenderWindow &window, matrixType &matrix,
               TetrominoVariant &piece, TetrominoVariant &next_piece,
               std::optional<TetrominoVariant> &saved_piece, sf::Text &title,
               sf::Text &score_text, sf::Text &score_number, Score &score) {
  draw_board(window);
  draw_cells(window, matrix, piece);
  draw_next_piece(window, next_piece, WINDOW_X - 170, 200);
  if (saved_piece.has_value()) {
    draw_save_piece(window, *saved_piece, WINDOW_X - 170, 300);
  }
  window.draw(title);
  window.draw(score_text);
  score_number.setString(std::to_string(score.get_total_score()));
  window.draw(score_number);
}

void draw_gameover(sf::RenderWindow &window, sf::Text &gameover_text,
                   sf::Text &restart_text) {
  draw_gameover(window);
  window.draw(gameover_text);
  window.draw(restart_text);
}
