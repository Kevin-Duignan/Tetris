
#include "../headers/clear.hpp"
#include "../headers/game.hpp"
#include "../headers/score.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

#include <iostream>
#include <string>

using namespace std::literals;
int main() {
  Score score;
  matrixType matrix;
  for (auto &row : matrix) {
    std::fill(row.begin(), row.end(), non_sealed::empty);
  }
  sf::Text title, score_text, score_number, gameover_text, restart_text;
  sf::Font junegull;
  if (!junegull.loadFromFile("media/junegull.ttf")) {
    // error...
  }
  sf::Font arial;
  if (!arial.loadFromFile("media/arial.ttf")) {
    // error...
  }

  title.setFont(junegull);
  title.setString("Tetris");
  title.setCharacterSize((WINDOW_X + WINDOW_Y) / 20); // in pixels, not points!
  title.setFillColor(sf::Color::Black);
  title.setPosition(WINDOW_X / 2 - 90, -10);

  score_text.setFont(junegull);
  score_text.setString("Score:");
  score_text.setCharacterSize((WINDOW_X + WINDOW_Y) / 30);
  score_text.setFillColor(sf::Color::Black);
  score_text.setPosition(WINDOW_X - 160, WINDOW_Y * 0.1);

  score_number.setFont(junegull);
  score_number.setString(std::to_string(score.get_total_score()));
  score_number.setCharacterSize((WINDOW_X + WINDOW_Y) / 40);
  score_number.setFillColor(sf::Color::Black);
  score_number.setPosition(WINDOW_X - 160, WINDOW_Y * 0.1 + 40);

  gameover_text.setFont(junegull);
  gameover_text.setString("Game\nOver");
  gameover_text.setCharacterSize((WINDOW_X + WINDOW_Y) / 15);
  gameover_text.setFillColor(sf::Color::Black);
  gameover_text.setPosition(LEFT_BORDER - GAP + 65, TOP_BORDER + 80);

  restart_text.setFont(junegull);
  restart_text.setString("Press r to restart");
  restart_text.setCharacterSize((WINDOW_X + WINDOW_Y) / 40);
  restart_text.setFillColor(sf::Color::Black);
  restart_text.setPosition(LEFT_BORDER - GAP + 31, TOP_BORDER + 320);

  //  std::variant<Tetromino<1>, Tetromino<2>, Tetromino<4>>;
  TetrominoVariant piece = choose_random(tetromino_piece_types);
  TetrominoVariant next_piece = assign_next_piece(piece);

  auto start_piece_coords = std::visit(
      [](auto &arg) -> pieceCoords { return arg.getBlockCoords(); }, piece);

  auto window = sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Tetris");
  window.setFramerateLimit(144);

  sf::Clock clock;                      // starts the clock
  sf::Time gameTick = sf::seconds(0.7); // game tick every 0.7 seconds
  sf::Clock score_clock;

  coords offset = std::make_tuple(COLUMNS / 2 - 2, 0); // (x, y)

  while (window.isOpen()) {
    sf::Event ev;

    if (handle_game_over(matrix)) { // can be optimised, only needs to check
                                    // gameover condition after every seal.

      while (window.pollEvent(ev)) {
        handle_event(window, ev, piece, next_piece, start_piece_coords, offset,
                     matrix, score, gameTick, clock);
      }
      window.clear();
      draw_game(window, matrix, piece, next_piece, title, score_text,
                score_number, score);
      draw_gameover(window, gameover_text, restart_text);
      window.display();

      continue;
    }

    set_piece_non_sealed(start_piece_coords, offset, matrix, non_sealed::empty);

    while (window.pollEvent(ev)) {
      handle_event(window, ev, piece, next_piece, start_piece_coords, offset,
                   matrix, score, gameTick, clock);
    }

    handle_game_tick(matrix, piece, next_piece, start_piece_coords, offset,
                     clock, gameTick, score);

    int cleared = clear_rows(matrix);
    if (cleared > 0) {
      score.clear(cleared);
    }
    if (cleared == 4) {
      score.tetris();
    }

    // Fill it back with new offset
    set_piece_non_sealed(start_piece_coords, offset, matrix,
                         non_sealed::active);

    window.clear();
    draw_game(window, matrix, piece, next_piece, title, score_text,
              score_number, score);
    window.display();
  }
}

void printGrid(matrixType matrix) {
  constexpr auto guide =
      "a b c d e f g h i j k l m n o p q r s t u v w x y z"sv;
  std::cout << "  " << guide.substr(0, matrix[0].size() * 2) << "\n";
  auto guideIter = guide.begin();
  for (const auto &row : matrix) { // Debugging only!
    std::cout << *guideIter << ' ';
    guideIter += 2;
    for (const auto &cell : row) {
      std::visit(
          [](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, non_sealed>) {
              std::cout << static_cast<int>(arg);
            } else if constexpr (std::is_same_v<T,
                                                BaseTetromino::piece_tag_t>) {
              std::cout << static_cast<int>(arg);
            }
          },
          cell);
      std::cout << ' ';
    }
    std::cout << '\n';
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
      floor((WINDOW_X + WINDOW_Y) / 20)); // in pixels, not points!
  title.setFillColor(sf::Color::Black);
  title.setPosition(WINDOW_X / 2 - 90, -15);

  score_text.setFont(junegull);
  score_text.setString("Score:");
  score_text.setCharacterSize(floor((WINDOW_X + WINDOW_Y) / 20));

  score_number.setFont(junegull);
  score_number.setString("0");
  score_text.setCharacterSize(floor((WINDOW_X + WINDOW_Y) / 20));
}
*/