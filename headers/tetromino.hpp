#pragma once

#include <algorithm>
#include <bitset>
#include <iostream>
#include <memory>
#include <random>
#include <tuple>
#include <variant>

struct BaseTetromino {
  enum class piece_tag_t : short { I, J, L, O, S, T, Z };

  constexpr explicit BaseTetromino(piece_tag_t tag) : piece_tag(tag) {}

  piece_tag_t piece_tag;
  std::uint8_t current_orientation = 0;
  std::tuple<std::uint8_t, std::uint8_t> coords = std::make_tuple(0, 0);
};

template <std::uint8_t Orientations> struct Tetromino : public BaseTetromino {
  using piece_type = std::array<std::bitset<16>, Orientations>;

  constexpr Tetromino() = delete;
  constexpr Tetromino(const Tetromino &other) = default;
  constexpr Tetromino(Tetromino &&other) noexcept = default;
  constexpr Tetromino &operator=(const Tetromino &other) = default;

  constexpr explicit Tetromino(piece_tag_t tag, piece_type orientations)
      : BaseTetromino{tag}, piece_mask(orientations) {}

  auto rotate() -> void {
    current_orientation = (current_orientation + 1) % Orientations;
  }

  auto revertRotate() -> void {
    if (current_orientation == 0) {
      current_orientation = Orientations - 1;
    } else {
      current_orientation--;
    }
  }

  std::vector<std::tuple<std::uint8_t, std::uint8_t>> getBlockCoords() const {
    std::vector<std::tuple<std::uint8_t, std::uint8_t>> block_coords;
    for (int y = 0; y < 4; ++y) {
      for (int x = 0; x < 4; ++x) {
        if ((*this)(std::uint8_t(x), std::uint8_t(y))) {
          block_coords.push_back(std::make_tuple(x, y));
        }
      }
    }

    return block_coords;
  }

  constexpr auto get_orientations() { return Orientations; }

  constexpr bool operator()(const std::uint8_t &x,
                            const std::uint8_t &y) const {
    return piece_mask.at(current_orientation).test((std::uint8_t(4) * y) + x);
  }

  piece_type piece_mask;
};

using TetrominoVariant = std::variant<Tetromino<1>, Tetromino<2>, Tetromino<4>>;
constexpr auto I_piece_t = Tetromino<2>(
    BaseTetromino::piece_tag_t::I,
    Tetromino<2>::piece_type{0b0000000000001111, 0b0001000100010001});

constexpr auto J_piece_t = Tetromino<4>(
    BaseTetromino::piece_tag_t::J,
    Tetromino<4>::piece_type{0b0000000001110001, 0b0000000100010011,
                             0b0000000001000111, 0b0000001100100010});

constexpr auto L_piece_t = Tetromino<4>(
    BaseTetromino::piece_tag_t::L,
    Tetromino<4>::piece_type{0b0000000000010111, 0b0000001000100011,
                             0b0000000001110100, 0b0000001100010001});

constexpr auto O_piece_t =
    Tetromino<1>(BaseTetromino::piece_tag_t::O,
                 Tetromino<1>::piece_type{0b0000000000110011});

constexpr auto S_piece_t = Tetromino<2>(
    BaseTetromino::piece_tag_t::S,
    Tetromino<2>::piece_type{0b0000000000110110, 0b0000001000110001});

constexpr auto T_piece_t = Tetromino<4>(
    BaseTetromino::piece_tag_t::T,
    Tetromino<4>::piece_type{0b0000000000100111, 0b0000010001100100,
                             0b0000011100100000, 0b0000000100110001});

constexpr auto Z_piece_t = Tetromino<2>(
    BaseTetromino::piece_tag_t::Z,
    Tetromino<2>::piece_type{0b0000000001100011, 0b0000000100110010});
// clang-format on

constexpr std::array<TetrominoVariant, 7> tetromino_piece_types = {
    I_piece_t, J_piece_t, L_piece_t, O_piece_t,
    S_piece_t, T_piece_t, Z_piece_t};
