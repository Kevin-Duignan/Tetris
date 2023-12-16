#pragma once

#include "const.hpp"
#include "matrix.hpp"
#include "tetromino.hpp"
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


TetrominoVariant choose_random(std::array<TetrominoVariant, 7> pieces);