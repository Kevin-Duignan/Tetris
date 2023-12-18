#pragma once

#include "const.hpp"
#include "matrix.hpp"
#include "score.hpp"
#include "tetromino.hpp"
#include <SFML/Graphics.hpp>

void draw_cells(sf::RenderWindow &window, matrixType &matrix,
                TetrominoVariant &piece);

void draw_gameover(sf::RenderWindow &window);

void handle_key_presses(sf::Event &ev, TetrominoVariant &piece,
                        pieceCoords &start_piece, coords &offset,
                        matrixType &matrix, Score &score);

void handle_game_tick(matrixType &matrix, TetrominoVariant &piece,
                      pieceCoords &start_piece, coords &offset,
                      sf::Clock &clock, sf::Time &gameTick, Score &score);

void set_piece_non_sealed(pieceCoords &start_piece, coords &offset,
                          matrixType &matrix, cell_type type);

bool is_valid_position(int x, int y, matrixType &matrix);

bool handle_game_over(matrixType &matrix);

void handle_event(sf::RenderWindow &window, sf::Event &ev,
                  TetrominoVariant &piece, pieceCoords &start_piece,
                  coords &offset, matrixType &matrix, Score &score);

void draw_game(sf::RenderWindow &window, matrixType &matrix,
               TetrominoVariant &piece, sf::Text &title, sf::Text &score_text,
               sf::Text &score_number, Score &score);

void draw_gameover(sf::RenderWindow &window, sf::Text &gameover_text,
                   sf::Text &restart_text);

TetrominoVariant choose_random(std::array<TetrominoVariant, 7> pieces);