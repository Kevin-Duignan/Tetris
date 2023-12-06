#pragma once

#include "const.h"
#include <array>
#include <tuple>
#include <vector>

enum class cellType : short { empty, active, sealed };
using matrixType = std::array<std::array<int, COLUMNS>, ROWS>;
using coords = std::tuple<std::uint8_t, std::uint8_t>; // (x, y)
using pieceCoords = std::vector<coords>;

pieceCoords movePiece(matrixType &matrix, pieceCoords piece, char direction);

void printGrid(matrixType matrix);

bool shouldSeal(matrixType matrix, pieceCoords piece);