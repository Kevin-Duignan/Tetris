#pragma once

#include <array>
#include <bitset>
#include <memory>
#include <tuple>
#include <variant>
#include <vector>

struct BaseTetromino {
  enum class piece_tag_t : short { I, J, L, O, S, T, Z };

  constexpr explicit BaseTetromino(piece_tag_t tag)
      : piece_tag(tag), current_orientation(0), coords(0, 0) {}

  piece_tag_t piece_tag;
  std::uint8_t current_orientation;
  std::tuple<std::uint8_t, std::uint8_t> coords;
};

template <std::uint8_t Orientations> struct Tetromino : public BaseTetromino {
  using piece_type = std::array<std::bitset<12>, Orientations>;

  constexpr Tetromino() = delete;
  constexpr Tetromino(const Tetromino &other) = default;
  constexpr Tetromino(Tetromino &&other) = default;

  constexpr explicit Tetromino(piece_tag_t tag, piece_type orientations)
      : BaseTetromino{tag} {}

  auto rotate() -> void;
  constexpr auto operator()(const std::uint8_t &x, const std::uint8_t &y) const
      -> std::bitset<12>::const_reference;
  auto getBlockCoords();

  piece_type piece_mask;
};

using TetrominoVariant = std::variant<Tetromino<1>, Tetromino<2>, Tetromino<4>>;

extern std::array<TetrominoVariant, 7> tetromino_piece_types;

auto fun() -> void;