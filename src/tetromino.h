#ifndef TETROMINO_H
#define TETROMINO_H

#include "const.h"
#include <array>
#include <bitset>
#include <memory>
#include <tuple>
#include <vector>

template <std::uint8_t Orientations> struct Tetromino {
  using piece_type = std::array<std::bitset<12>, Orientations>;
  enum class piece_tag_t : short { I, J, L, O, S, T, Z };

  constexpr Tetromino() = delete;

  constexpr Tetromino(const Tetromino &other) = default;
  constexpr Tetromino(Tetromino &&other) = default;

  constexpr explicit Tetromino(piece_tag_t tag, std::uint8_t default_orientaion,
                               piece_type orientations)
      : piece_tag(tag), piece_orientation(default_orientaion),
        piece_mask(orientations), coords(std::make_tuple(COLUMNS / 2, 0)) {}

  auto rotate() -> void {
    piece_orientation = (piece_orientation + 1) % Orientations;
  }

  constexpr auto operator()(const std::uint8_t &x, const std::uint8_t &y) const
      -> bool {
    return piece_mask.at(piece_orientation)[(std::uint8_t(4) * y) + x];
  }

  piece_tag_t piece_tag;
  std::uint8_t piece_orientation = 0;
  piece_type piece_mask;
  std::tuple<std::uint8_t, std::uint8_t> coords;
};

// piece_mask[piece_orientation]
constexpr auto I_piece_t = Tetromino<2>(
    Tetromino<2>::piece_tag_t::I, std::uint8_t(0),
    Tetromino<2>::piece_type{0b0000111100000000, 0b01000100010001000});

auto fun() -> void {
  Tetromino<2> piece(I_piece_t);

  piece.rotate();
  piece(1, 2);
}

std::vector<std::tuple<std::uint8_t, std::uint8_t>>
getBlockCoords(const Tetromino<2> &piece) {
  std::vector<std::tuple<std::uint8_t, std::uint8_t>> blockCoords;

  // Get the top-left coordinate of the piece
  auto [topLeftX, topLeftY] = piece.coords;

  // Iterate over the shape of the piece
  for (std::uint8_t y = 0; y < 4; ++y) {
    for (std::uint8_t x = 0; x < 4; ++x) {
      // If the block is part of the piece
      if (piece(x, y)) {
        // Add the block's absolute position to the vector
        blockCoords.push_back(std::make_tuple(topLeftX + x, topLeftY + y));
      }
    }
  }

  return blockCoords;
}

#endif