#ifndef UTILITY_H
#define UTILITY_H

#include "enum_classes.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

// Utility functions for calculations or other actions
class Utility {
public:
    Utility() = default;
    ~Utility() = default;
public:
    /*
        Returns the direction of the mouse from the object
        Telling that click was from Object's left, right, up, or down
    */
    Direction mouseDirectionFromObject(float delta_x, float delta_y);

    void pathFinder(const std::vector<std::vector<bool>> &map, std::queue<sf::Vector2f> &trajectory,sf::Vector2f start, sf::Vector2f end);
private:
    std::vector<sf::Vector2i> getNeighbours(sf::Vector2i pair, int map_size);
}; // Utility

#endif // UTILITY_H