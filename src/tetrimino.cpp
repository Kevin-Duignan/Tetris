#include "const.h"
#include <array>
#include <bitset>
#include <memory>
#include <tuple>
#include <variant>

// Tags, coords and current orientation all initialised the same way
struct BaseTetrimino {
  enum class piece_tag_t : short { I, J, L, O, S, T, Z };

  constexpr explicit BaseTetrimino(piece_tag_t tag)
      : piece_tag(tag), current_orientation(0), coords(0, 0) {}

  piece_tag_t piece_tag;
  std::uint8_t current_orientation;
  std::tuple<std::uint8_t, std::uint8_t> coords;
};

// Used to construct array of orientations (size specific to each tetrimino)
template <std::uint8_t Orientations> struct Tetrimino : public BaseTetrimino {
  using piece_type = std::array<std::bitset<12>, Orientations>;

  constexpr Tetrimino() = delete;

  constexpr Tetrimino(const Tetrimino &other) = default;
  constexpr Tetrimino(Tetrimino &&other) = default;

  constexpr explicit Tetrimino(piece_tag_t tag, piece_type orientations)
      : BaseTetrimino{tag} {}

  // piece_mask[piece_orientation]
  auto rotate() -> void {
    current_orientation = (current_orientation + 1) % Orientations;
  }

  constexpr auto operator()(const std::uint8_t &x, const std::uint8_t &y) const
      -> std::bitset<12>::const_reference {
    return piece_mask.at(current_orientation)[(std::uint8_t(4) * y) + x];
  }

  piece_type piece_mask;
};

// A tetrimino can only have either 1, 2, or 4 possible orientations
using TetriminoVariant = std::variant<Tetrimino<1>, Tetrimino<2>, Tetrimino<4>>;

constexpr auto I_piece_t = Tetrimino<2>(
    BaseTetrimino::piece_tag_t::I,
    Tetrimino<2>::piece_type{0b0000111100000000, 0b01000100010001000});

constexpr auto J_piece_t = Tetrimino<4>(
    BaseTetrimino::piece_tag_t::J,
    Tetrimino<4>::piece_type{0b0100111000000000, 0b0010011001000000,
                             0b0000111001000000, 0b0100110001000000});

constexpr auto L_piece_t = Tetrimino<4>(
    BaseTetrimino::piece_tag_t::L,
    Tetrimino<4>::piece_type{0b0010111000000000, 0b0100110010000000,
                             0b0000111010000000, 0b0010011000100000});

constexpr auto O_piece_t =
    Tetrimino<1>(BaseTetrimino::piece_tag_t::O,
                 Tetrimino<1>::piece_type{0b0000011001100000});

constexpr auto S_piece_t = Tetrimino<2>(
    BaseTetrimino::piece_tag_t::S,
    Tetrimino<2>::piece_type{0b0000011011000000, 0b0100011000100000});

constexpr auto T_piece_t = Tetrimino<4>(
    BaseTetrimino::piece_tag_t::T,
    Tetrimino<4>::piece_type{0b0000011100100000, 0b0100011001000000,
                             0b0100011100000000, 0b0100110001000000});

constexpr auto Z_piece_t = Tetrimino<2>(
    BaseTetrimino::piece_tag_t::Z,
    Tetrimino<2>::piece_type{0b0000111000100000, 0b0100110000100000});

constexpr std::array<TetriminoVariant, 7> tetrimino_piece_types = {
    I_piece_t, J_piece_t, L_piece_t, O_piece_t,
    S_piece_t, T_piece_t, Z_piece_t};

auto fun() -> void {
  Tetrimino<2> piece(I_piece_t);

  piece.rotate();
  piece(1, 2);
}
