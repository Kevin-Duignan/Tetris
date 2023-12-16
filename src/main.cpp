
#include "../headers/clear.hpp"
#include "../headers/game.hpp"
#include "../headers/score.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std::literals;

int main() {
  Score score;
  matrixType matrix;
  for (auto &row : matrix) {
    std::fill(row.begin(), row.end(), 0);
  }

  //  std::variant<Tetromino<1>, Tetromino<2>, Tetromino<4>>;
  TetrominoVariant piece = choose_random(tetromino_piece_types);
  auto start_piece = std::visit(get_block_coords, piece);

  auto window = sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Tetris");
  window.setFramerateLimit(144);

  sf::Clock clock;                      // starts the clock
  sf::Time gameTick = sf::seconds(0.3); // game tick every 1 second

  coords offset = std::make_tuple(0, 0); // (x, y)

  while (window.isOpen()) {
    set_piece_cell_type(start_piece, offset, matrix, cellType::empty);

    sf::Event ev;
    while (window.pollEvent(ev)) {
      if (ev.type == sf::Event::Closed) {
        window.close();
      }
      if (ev.type == sf::Event::KeyPressed) {
        std::cout << "Key pressed event triggered\n";
        handle_key_presses(ev, piece, start_piece, offset, matrix);
      }
    }
    handle_game_tick(matrix, piece, start_piece, offset, clock, gameTick);
    clear_rows(matrix);
    // Fill it back with new offset
    set_piece_cell_type(start_piece, offset, matrix, cellType::active);

    window.clear();
    draw_cells(window, matrix);
    window.display();
  }
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
