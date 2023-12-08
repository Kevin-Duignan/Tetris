#pragma once

#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <variant>
#include <vector>

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
  constexpr Tetromino(Tetromino &&other) = default;

  constexpr explicit Tetromino(piece_tag_t tag, piece_type orientations)
      : BaseTetromino{tag}, piece_mask(orientations) {}

  auto rotate() -> void {
    current_orientation = (current_orientation + 1) % Orientations;
  }

  std::vector<std::tuple<std::uint8_t, std::uint8_t>> getBlockCoords() const {
    std::vector<std::tuple<std::uint8_t, std::uint8_t>> block_coords;
    for (int y = 0; y < 4; ++y) {
      for (int x = 0; x < 4; ++x) {
        std::cout << piece_mask.at(current_orientation)
                         .test((std::uint8_t(4) * y) + x);
        std::cout << x << " " << y << " "
                  << "\n";
        if ((*this)(std::uint8_t(x), std::uint8_t(y))) {
          std::cout << "yes";
          block_coords.push_back(std::make_tuple(x, y));
        }
      }
    }
    for (const auto &coord : block_coords) {
      auto [x, y] = coord;
      std::cout << x << " " << y << std::endl;
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
