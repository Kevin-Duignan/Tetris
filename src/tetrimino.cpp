#include "const.h"
#include <array>
#include <bitset>
#include <memory>

template <std::uint8_t Orientations> struct Tetrimino {
  using piece_type = std::array<std::bitset<12>, Orientations>;
  enum class piece_tag_t : short { I, J, L, O, S, T, Z };

  constexpr Tetrimino() = delete;

  constexpr Tetrimino(const Tetrimino &other) = default;
  constexpr Tetrimino(Tetrimino &&other) = default;

  constexpr explicit Tetrimino(piece_tag_t tag, std::uint8_t default_orientaion,
                               piece_type orientations)
      : piece_tag(tag), piece_orientation(default_orientaion),
        piece_mask(orientations) {}

  auto rotate() -> void {
    piece_orientation = (piece_orientation + 1) % Orientations;
  }

  constexpr auto operator()(const std::uint8_t &x, const std::uint8_t &y) const
      -> std::bitset<12>::const_reference {
    return piece_mask.at(piece_orientation)[(std::uint8_t(4) * y) + x];
  }

  piece_tag_t piece_tag;
  std::uint8_t piece_orientation = 0;
  piece_type piece_mask;
};

// piece_mask[piece_orientation]
constexpr auto I_piece_t = Tetrimino<2>(
    Tetrimino<2>::piece_tag_t::I, std::uint8_t(0),
    Tetrimino<2>::piece_type{0b0000111100000000, 0b01000100010001000});

auto fun() -> void {
  Tetrimino<2> piece(I_piece_t);

  piece.rotate();
  piece(1, 2);
}
