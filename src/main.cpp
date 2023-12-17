
#include "../headers/clear.hpp"
#include "../headers/game.hpp"
#include "../headers/score.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>

using namespace std::literals;

int main() {
  Score score;
  matrixType matrix;
  for (auto &row : matrix) {
    std::fill(row.begin(), row.end(), 0);
  }
  sf::Text title, score_text, score_number;
  sf::Font junegull;
  if (!junegull.loadFromFile("media/junegull.ttf")) {
    // error...
  }

  title.setFont(junegull);
  title.setString("Tetris");
  title.setCharacterSize((WINDOW_X + WINDOW_Y) / 20); // in pixels, not points!
  title.setFillColor(sf::Color::Black);
  title.setPosition(WINDOW_X / 2 - 90, -15);
  score_text.setFont(junegull);
  score_text.setString("Score:");
  score_text.setCharacterSize((WINDOW_X + WINDOW_Y) / 30);
  score_text.setFillColor(sf::Color::Black);
  score_text.setPosition(WINDOW_X - 190, WINDOW_Y * 0.1);

  score_number.setFont(junegull);
  score_number.setString(std::to_string(score.get_total_score()));
  score_number.setCharacterSize((WINDOW_X + WINDOW_Y) / 40);
  score_number.setFillColor(sf::Color::Black);
  score_number.setPosition(WINDOW_X - 190, WINDOW_Y * 0.1 + 40);

  //  std::variant<Tetromino<1>, Tetromino<2>, Tetromino<4>>;
  TetrominoVariant piece = choose_random(tetromino_piece_types);
  auto start_piece = std::visit(
      [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); }, piece);

  auto window = sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Tetris");
  window.setFramerateLimit(144);

  sf::Clock clock;                      // starts the clock
  sf::Time gameTick = sf::seconds(0.7); // game tick every 0.7 seconds

  coords offset = std::make_tuple(floor(COLUMNS / 2) - 2, 0); // (x, y)

  while (window.isOpen()) {
    set_piece_cell_type(start_piece, offset, matrix, cellType::empty);

    sf::Event ev;
    while (window.pollEvent(ev)) {
      if (ev.type == sf::Event::Closed) {
        window.close();
      }
      if (ev.type == sf::Event::KeyPressed) {
        handle_key_presses(ev, piece, start_piece, offset, matrix, score);
      }
    }
    handle_game_tick(matrix, piece, start_piece, offset, clock, gameTick,
                     score);
    int cleared = clear_rows(matrix);
    if (cleared > 0) {
      score.clear(cleared);
    }
    if (cleared == 4) {
      score.tetris();
    }
    // Fill it back with new offset
    set_piece_cell_type(start_piece, offset, matrix, cellType::active);

    window.clear();

    // Drawing components
    auto [r, g, b] =
        std::visit([](auto &arg) -> auto { return arg.piece_colour; }, piece);
    draw_cells(window, matrix, sf::Color(r, g, b));
    window.draw(title);
    window.draw(score_text);
    score_number.setString(std::to_string(score.get_total_score()));
    window.draw(score_number);

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

/* This doesn't work yet, but it would be nice.
void initialise_texts(sf::Text &title, sf::Text &score_text,
                      sf::Text &score_number) {
  sf::Font junegull;
  if (!junegull.loadFromFile("media/junegull.ttf")) {
    // error...
  }
  // select the font
  title.setFont(junegull);
  title.setString("Tetris");
  title.setCharacterSize(
      floor((window_x + window_y) / 20)); // in pixels, not points!
  title.setFillColor(sf::Color::Black);
  title.setPosition(window_x / 2 - 90, -15);

  score_text.setFont(junegull);
  score_text.setString("Score:");
  score_text.setCharacterSize(floor((window_x + window_y) / 20));

  score_number.setFont(junegull);
  score_number.setString("0");
  score_text.setCharacterSize(floor((window_x + window_y) / 20));
}
*/