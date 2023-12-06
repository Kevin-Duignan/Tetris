#include "../headers/tetromino.h"

template <std::uint8_t Orientations>
auto Tetromino<Orientations>::rotate() -> void {
  current_orientation = (current_orientation + 1) % Orientations;
}

template <std::uint8_t Orientations>
constexpr auto Tetromino<Orientations>::operator()(const std::uint8_t &x,
                                                   const std::uint8_t &y) const
    -> std::bitset<12>::const_reference {
  return piece_mask.at(current_orientation)[(std::uint8_t(4) * y) + x];
}

template <std::uint8_t Orientations>
auto Tetromino<Orientations>::getBlockCoords() {
  std::vector<std::tuple<std::uint8_t, std::uint8_t>> blockCoords;

  auto [topLeftX, topLeftY] = coords;

  for (std::uint8_t y = 0; y < 4; ++y) {
    for (std::uint8_t x = 0; x < 4; ++x) {
      if ((*this)(x, y)) {
        blockCoords.push_back(std::make_tuple(topLeftX + x, topLeftY + y));
      }
    }
  }

  return blockCoords;
}

constexpr std::array<TetrominoVariant, 7> tetromino_piece_types = {
    Tetromino<2>(
        BaseTetromino::piece_tag_t::I,
        Tetromino<2>::piece_type{0b0000111100000000, 0b01000100010001000}),
    Tetromino<4>(
        BaseTetromino::piece_tag_t::J,
        Tetromino<4>::piece_type{0b0100111000000000, 0b0010011001000000,
                                 0b0000111001000000, 0b0100110001000000}),
    Tetromino<4>(
        BaseTetromino::piece_tag_t::L,
        Tetromino<4>::piece_type{0b0010111000000000, 0b0100110010000000,
                                 0b0000111010000000, 0b0010011000100000}),
    Tetromino<1>(BaseTetromino::piece_tag_t::O,
                 Tetromino<1>::piece_type{0b0000011001100000}),
    Tetromino<2>(
        BaseTetromino::piece_tag_t::S,
        Tetromino<2>::piece_type{0b0000011011000000, 0b0100011000100000}),
    Tetromino<4>(
        BaseTetromino::piece_tag_t::T,
        Tetromino<4>::piece_type{0b0000011100100000, 0b0100011001000000,
                                 0b0100011100000000, 0b010011001000000}),
    Tetromino<2>(
        BaseTetromino::piece_tag_t::Z,
        Tetromino<2>::piece_type{0b0000111000100000, 0b0100110000100000})};

auto fun() -> void {
  Tetromino<2> piece(Tetromino<2>(
      BaseTetromino::piece_tag_t::I,
      Tetromino<2>::piece_type{0b0000111100000000, 0b01000100010001000}));

  piece.rotate();
  piece(1, 2);
}