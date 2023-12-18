#pragma once

#include "const.hpp"
#include "matrix.hpp"
#include "score.hpp"
#include "tetromino.hpp"
#include <SFML/Graphics.hpp>

void draw_cells(sf::RenderWindow &window, matrixType &matrix,
                TetrominoVariant &piece);

void handle_key_presses(sf::Event &ev, TetrominoVariant &piece,
                        pieceCoords &start_piece, coords &offset,
                        matrixType &matrix, Score &score, sf::Time &gameTick,
                        sf::Clock &clock);

void handle_game_tick(matrixType &matrix, TetrominoVariant &piece,
                      pieceCoords &start_piece, coords &offset,
                      sf::Clock &clock, sf::Time &gameTick, Score &score);

void seal_piece(TetrominoVariant &piece, pieceCoords &start_piece,
                coords &offset, matrixType &matrix);

void set_piece_non_sealed(pieceCoords &start_piece, coords &offset,
                          matrixType &matrix, cell_type type);

bool is_valid_position(int x, int y, matrixType &matrix);

bool handle_game_over(matrixType &matrix);

TetrominoVariant choose_random(std::array<TetrominoVariant, 7> pieces);