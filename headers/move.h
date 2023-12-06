#pragma once

#include <algorithm>
#include <array>

using matrixType = std::array<std::array<int, COLUMNS>, ROWS>;
using coords = std::tuple<std::uint8_t, std::uint8_t>; // (x, y)
using pieceType = std::vector<coords>;

pieceType movePiece(matrixType &matrix, pieceType piece, char direction);

void printGrid(matrixType matrix);

bool shouldSeal(matrixType matrix, pieceType piece);