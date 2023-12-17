#pragma once
#include <SFML/Graphics.hpp>
#include <map>

const sf::Color PASTEL_YELLOW_LIGHT = sf::Color(255, 216, 165);
const sf::Color PASTEL_YELLOW_DARK = sf::Color(183, 151, 110);
const sf::Color BROWN = sf::Color(65, 54, 43);

using RGB = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>;

// Piece colours (not initialized with sf::Color yet so can use constexpr)
constexpr RGB GREEN = std::make_tuple(168, 228, 160);
constexpr RGB BLUE = std::make_tuple(159, 223, 232);
constexpr RGB PURPLE = std::make_tuple(221, 160, 221);
constexpr RGB RED = std::make_tuple(255, 105, 97);
constexpr RGB ORANGE = std::make_tuple(255, 179, 71);
constexpr RGB PINK = std::make_tuple(255, 105, 180);
constexpr RGB CYAN = std::make_tuple(87, 199, 208);
