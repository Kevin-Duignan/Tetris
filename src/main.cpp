#include <SFML/Graphics.hpp>
#include <vector>

struct Tetromino {
    sf::Color color;
    std::vector<sf::Vector2i> blocks;

    Tetromino(sf::Color c, std::vector<sf::Vector2i> b) : color(c), blocks(b) {}

    void draw(sf::RenderWindow& window, int cellSize) const {
        sf::RectangleShape blockShape(sf::Vector2f(cellSize, cellSize));
        blockShape.setFillColor(color);

        for (const auto& block : blocks) {
            blockShape.setPosition(block.x * cellSize, block.y * cellSize);
            window.draw(blockShape);
        }
    }
};
