#pragma once

#include <array>
#include <bitset>
#include <memory>
#include <tuple>
#include <variant>

// Tags, coords and current orientation all initialised the same way
struct BaseTetromino {
  enum class piece_tag_t : short { I, J, L, O, S, T, Z };

  constexpr explicit BaseTetromino(piece_tag_t tag)
      : piece_tag(tag), current_orientation(0), coords(0, 0) {}

  piece_tag_t piece_tag;
  std::uint8_t current_orientation;
  std::tuple<std::uint8_t, std::uint8_t> coords;
};

// Used to construct array of orientations (size specific to each tetromino)
template <std::uint8_t Orientations> struct Tetromino : public BaseTetromino {
  using piece_type = std::array<std::bitset<12>, Orientations>;

  constexpr Tetromino() = delete;
  constexpr Tetromino(const Tetromino &other) = default;
  constexpr Tetromino(Tetromino &&other) = default;

  constexpr explicit Tetromino(piece_tag_t tag, piece_type orientations)
      : BaseTetromino{tag} {}
  // piece_mask[piece_orientation]
  auto rotate() -> void {
    current_orientation = (current_orientation + 1) % Orientations;
  }

  constexpr auto operator()(const std::uint8_t &x, const std::uint8_t &y) const
      -> std::bitset<12>::const_reference {
    return piece_mask.at(current_orientation)[(std::uint8_t(4) * y) + x];
  }

  auto getBlockCoords() {
    std::vector<std::tuple<std::uint8_t, std::uint8_t>> blockCoords;

    // Get the top-left coordinate of the piece
    auto [topLeftX, topLeftY] = coords;

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

  piece_type piece_mask;
};

// A tetromino can only have either 1, 2, or 4 possible orientations
using TetrominoVariant = std::variant<Tetromino<1>, Tetromino<2>, Tetromino<4>>;

constexpr auto I_piece_t = Tetromino<2>(
    BaseTetromino::piece_tag_t::I,
    Tetromino<2>::piece_type{0b0000111100000000, 0b01000100010001000});

constexpr auto J_piece_t = Tetromino<4>(
    BaseTetromino::piece_tag_t::J,
    Tetromino<4>::piece_type{0b0100111000000000, 0b0010011001000000,
                             0b0000111001000000, 0b0100110001000000});

constexpr auto L_piece_t = Tetromino<4>(
    BaseTetromino::piece_tag_t::L,
    Tetromino<4>::piece_type{0b0010111000000000, 0b0100110010000000,
                             0b0000111010000000, 0b0010011000100000});

constexpr auto O_piece_t =
    Tetromino<1>(BaseTetromino::piece_tag_t::O,
                 Tetromino<1>::piece_type{0b0000011001100000});

constexpr auto S_piece_t = Tetromino<2>(
    BaseTetromino::piece_tag_t::S,
    Tetromino<2>::piece_type{0b0000011011000000, 0b0100011000100000});

constexpr auto T_piece_t = Tetromino<4>(
    BaseTetromino::piece_tag_t::T,
    Tetromino<4>::piece_type{0b0000011100100000, 0b0100011001000000,
                             0b0100011100000000, 0b0100110001000000});

constexpr auto Z_piece_t = Tetromino<2>(
    BaseTetromino::piece_tag_t::Z,
    Tetromino<2>::piece_type{0b0000111000100000, 0b0100110000100000});

constexpr std::array<TetrominoVariant, 7> tetromino_piece_types = {
    I_piece_t, J_piece_t, L_piece_t, O_piece_t,
    S_piece_t, T_piece_t, Z_piece_t};

auto fun() -> void {
  Tetromino<2> piece(I_piece_t);

  piece.rotate();
  piece(1, 2);
}