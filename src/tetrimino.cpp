#include "const.h"
#include <array>
#include <bitset>
#include <memory>
#include <tuple>

template <std::uint8_t Orientations> struct Tetrimino {
  using piece_type = std::array<std::bitset<12>, Orientations>;
  enum class piece_tag_t : short { I, J, L, O, S, T, Z };

  constexpr Tetrimino() = delete;

  constexpr Tetrimino(const Tetrimino &other) = default;
  constexpr Tetrimino(Tetrimino &&other) = default;

  constexpr explicit Tetrimino(piece_tag_t tag, piece_type orientations)
      : piece_tag(tag), piece_mask(orientations), current_orientation(0),
        coords(std::make_tuple(0, 0)) {}

  auto rotate() -> void {
    current_orientation = (current_orientation + 1) % Orientations;
  }

  constexpr auto operator()(const std::uint8_t &x, const std::uint8_t &y) const
      -> std::bitset<12>::const_reference {
    return piece_mask.at(current_orientation)[(std::uint8_t(4) * y) + x];
  }

  piece_tag_t piece_tag;
  piece_type piece_mask;
  std::uint8_t current_orientation;
  std::tuple<std::uint8_t, std::uint8_t> coords;
};

// piece_mask[piece_orientation]
constexpr auto I_piece_t = Tetrimino<2>(
    Tetrimino<2>::piece_tag_t::I,
    Tetrimino<2>::piece_type{0b0000111100000000, 0b01000100010001000});

constexpr auto O_piece_t = Tetrimino<1>(
    Tetrimino<1>::piece_tag_t::O, Tetrimino<1>::piece_type{0b0000011001100000});

auto fun() -> void {
  Tetrimino<2> piece(I_piece_t);

  piece.rotate();
  piece(1, 2);
}
