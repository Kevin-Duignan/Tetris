#pragma once
#include <SFML/Graphics.hpp>
#include <map>

const sf::Color PASTEL_YELLOW_LIGHT = sf::Color(225, 196, 135);
const sf::Color PASTEL_YELLOW_DARK = sf::Color(153, 121, 80);
const sf::Color BROWN = sf::Color(75, 64, 53);

using RGB = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>;

// Piece colours (not initialized with sf::Color yet so can use constexpr)
constexpr RGB GREEN = std::make_tuple(76, 187, 23);
constexpr RGB BLUE = std::make_tuple(70, 130, 180);   // Darker pastel blue
constexpr RGB PURPLE = std::make_tuple(127, 92, 199); // Darker pastel purple
constexpr RGB RED = std::make_tuple(205, 92, 92);     // Darker pastel red
constexpr RGB ORANGE = std::make_tuple(255, 140, 0);  // Darker pastel orange
constexpr RGB PINK = std::make_tuple(255, 105, 180);  // Darker pastel pink
constexpr RGB CYAN = std::make_tuple(0, 139, 139);    // Darker pastel cyan