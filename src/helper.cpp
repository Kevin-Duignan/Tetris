#include "../headers/helper.h"

void draw_cells(sf::RenderWindow &window, matrixType matrix) {

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

void handle_key_presses(TetrominoVariant &piece, pieceCoords &start_piece,
                        coords &offset, matrixType &matrix) {
  sf::Event ev;
  switch (ev.key.code) {
  case sf::Keyboard::D:
  case sf::Keyboard::Right:
    offset = movePiece(matrix, start_piece, 'r', offset);
    break;
  case sf::Keyboard::S:
  case sf::Keyboard::Down:
    offset = movePiece(matrix, start_piece, 'd', offset);
    break;
  case sf::Keyboard::A:
  case sf::Keyboard::Left:
    offset = movePiece(matrix, start_piece, 'l', offset);
    break;
  case (sf::Keyboard::Q):
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

void handle_game_tick(pieceCoords &start_piece, coords &offset,
                      sf::Clock &clock, matrixType &matrix);

void replace_piece(pieceCoords &start_piece, coords &offset, matrixType &matrix,
                   bool clear) {
  for (auto [c_x, c_y] : start_piece) {
    auto [offset_x, offset_y] = offset;
    if (clear) {
      matrix[c_y + offset_y][c_x + offset_x] =
          std::to_underlying(cellType::empty);
    } else {
      matrix[c_y + offset_y][c_x + offset_x] =
          std::to_underlying(cellType::active);
    }
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