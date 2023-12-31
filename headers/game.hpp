#pragma once

#include "const.hpp"
#include "matrix.hpp"
#include "score.hpp"
#include "tetromino.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
void draw_board(sf::RenderWindow &window);

void draw_cells(sf::RenderWindow &window, matrixType &matrix,
                TetrominoVariant &piece);

void draw_saved_piece(sf::RenderWindow &window,
                      std::optional<TetrominoVariant> &piece, float x, float y);

void draw_next_piece(sf::RenderWindow &window, TetrominoVariant &piece, float x,
                     float y);

void draw_gameover(sf::RenderWindow &window);

void handle_key_presses(sf::Event &ev, TetrominoVariant &piece,
                        TetrominoVariant &next_piece,
                        std::optional<TetrominoVariant> &saved_piece,
                        pieceCoords &start_piece, coords &offset,
                        matrixType &matrix, Score &score, sf::Time &gameTick,
                        sf::Clock &clock, bool &save_lock);

void handle_game_tick(matrixType &matrix, TetrominoVariant &piece,
                      TetrominoVariant &next_piece, pieceCoords &start_piece,
                      coords &offset, sf::Clock &clock, sf::Time &gameTick,
                      Score &score, bool &save_lock);

void seal_piece(TetrominoVariant &piece, TetrominoVariant &next_piece,
                pieceCoords &start_piece, coords &offset, matrixType &matrix,
                bool &save_lock);

void set_piece_non_sealed(pieceCoords &start_piece, coords &offset,
                          matrixType &matrix, cell_type type);

coords calculate_drop_position(matrixType &matrix, pieceCoords &start_piece,
                               coords &offset);

void clear_drop_shadow(matrixType &matrix);

bool is_valid_position(int x, int y, matrixType &matrix);

bool shouldSeal(matrixType matrix, pieceCoords piece, coords offset);

bool handle_game_over(matrixType &matrix);

void handle_event(sf::RenderWindow &window, sf::Event &ev,
                  TetrominoVariant &piece, TetrominoVariant &next_piece,
                  std::optional<TetrominoVariant> &saved_piece,
                  pieceCoords &start_piece, coords &offset, matrixType &matrix,
                  Score &score, sf::Time gameTick, sf::Clock clock,
                  bool &save_lock);

void draw_game(sf::RenderWindow &window, matrixType &matrix,
               TetrominoVariant &piece, TetrominoVariant &next_piece,
               std::optional<TetrominoVariant> &saved_piece, sf::Text &title,
               sf::Text &score_text, sf::Text &score_number, Score &score);

void draw_gameover(sf::RenderWindow &window, sf::Text &gameover_text,
                   sf::Text &restart_text);

TetrominoVariant choose_random(std::array<TetrominoVariant, 7> pieces);

TetrominoVariant assign_next_piece(TetrominoVariant &piece);