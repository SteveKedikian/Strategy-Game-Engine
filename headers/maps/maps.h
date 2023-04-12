#ifndef MAPS_H
#define MAPS_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace nsm {

class Avarayr
{
public:
    Avarayr();

public:
    void draw(sf::RenderWindow& window);

private:
    int m_height;
    int m_width;
    std::vector<std::vector<int>> m_bottom_layer_matrix;
    std::vector<std::vector<int>> m_obstacles_layer_matrix;

public:
    std::vector<std::vector<int>> m_obstacle_path_find_matrix;

}; // class - Avarayr

}; // namespace - nsm

#endif // MAPS_H