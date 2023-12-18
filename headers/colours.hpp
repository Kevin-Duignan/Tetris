#pragma once
#include <SFML/Graphics.hpp>
#include <map>

// Screen colour
const sf::Color LIGHT_GRAY = sf::Color(119, 136, 153);  // Light Slate Gray
const sf::Color DARK_GRAY = sf::Color(47, 79, 79);      // Dark Slate Gray
const sf::Color MIDNIGHT_BLUE = sf::Color(25, 25, 112); // Midnight Blue

using RGB = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>;

// Piece colours (not initialized with sf::Color yet so can use constexpr)
constexpr RGB GREEN = std::make_tuple(152, 251, 152);  // Pale Green
constexpr RGB BLUE = std::make_tuple(135, 206, 235);   // Sky Blue
constexpr RGB PURPLE = std::make_tuple(221, 160, 221); // Plum
constexpr RGB RED = std::make_tuple(250, 128, 114);    // Salmon
constexpr RGB ORANGE = std::make_tuple(255, 165, 0);   // Orange
constexpr RGB PINK = std::make_tuple(255, 182, 193);   // Light Pink
constexpr RGB CYAN = std::make_tuple(224, 255, 255);   // Light Cyan