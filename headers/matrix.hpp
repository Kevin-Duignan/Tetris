#pragma once

#include "const.hpp"
#include "tetromino.hpp"
#include <array>
#include <cstdint>
#include <tuple>
#include <vector>

enum class cell_type : short { empty, active, sealed };

using cell_value = std::variant<cell_type, BaseTetromino::piece_tag_t>;

using matrixType = std::array<std::array<int, COLUMNS>, ROWS>;
using coords = std::tuple<std::uint8_t, std::uint8_t>; // (x, y)
using pieceCoords = std::vector<coords>;

void movePiece(matrixType &matrix, pieceCoords piece, char direction,
               coords &offset);

void printGrid(matrixType matrix);

bool shouldSeal(matrixType matrix, pieceCoords piece, coords offset);