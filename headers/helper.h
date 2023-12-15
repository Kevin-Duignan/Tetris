#include "const.h"
#include "matrix.h"
#include "tetromino.h"
#include <SFML/Graphics.hpp>

void draw_cells(sf::RenderWindow &window, matrixType matrix);

void handle_key_presses(sf::Event &ev, TetrominoVariant &piece,
                        pieceCoords &start_piece, coords &offset,
                        matrixType &matrix);

void handle_game_tick(matrixType &matrix, TetrominoVariant &piece,
                      pieceCoords &start_piece, coords &offset,
                      sf::Clock &clock, sf::Time &gameTick);

void set_piece_cell_type(pieceCoords &start_piece, coords &offset,
                         matrixType &matrix, cellType type);

bool is_valid_position(int x, int y, matrixType &matrix);

// Rotate lambda object for std::visit
auto rotate = [](auto &arg) { arg.rotate(); };

// Revert rotate lambda when rotate is invalid
auto revert_rotate = [](auto &arg) { arg.revertRotate(); };

auto get_block_coords = [](auto &arg) -> pieceCoords {
  return arg.getBlockCoords();
};

TetrominoVariant choose_random(std::array<TetrominoVariant, 7> pieces);