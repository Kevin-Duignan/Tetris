#pragma once

#include "const.hpp"
#include "tetromino.hpp"
#include <array>
#include <cstdint>
#include <tuple>
#include <vector>

enum class non_sealed : short { empty, active, drop_shadow };
using sealed_piece = BaseTetromino::piece_tag_t;
using cell_type = std::variant<non_sealed, sealed_piece>;

using matrixType = std::array<std::array<cell_type, COLUMNS>, ROWS>;
using coords = std::tuple<std::uint8_t, std::uint8_t>; // (x, y)
using pieceCoords = std::vector<coords>;

bool movePiece(matrixType &matrix, pieceCoords piece, char direction,
               coords &offset);

void printGrid(matrixType matrix);

bool shouldSeal(matrixType matrix, pieceCoords piece, coords offset);