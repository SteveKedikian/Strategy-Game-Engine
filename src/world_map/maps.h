#ifndef MAPS_H
#define MAPS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Map
{
public:
    Map(const std::string& map_name);
    ~Map() = default;
public:
    void mapMaker(); // Prepare data for the map
    void draw(sf::RenderWindow& window);
public:
    const std::vector<std::vector<bool>>& getObstacleMatrix() const;
private:
    void dataAssigning();
    void bottomLayerSetUp();
    void obstaclesLayerSetUp();
    void obstaclesMatrixSetUp();
    void setFalse32x32(int column, int row);
private:
    // CONSTANTS
    const int DEFAULT_HEIGHT = 10;
    const int DEFAULT_WIDTH = 10;
    const std::string DEFAULT_NAME = "default";
    const std::string DEFAULT_BOTTOM_LAYER_IMAGE_PATH = "../graphics/world_map/avarayr/land_tiles.png";
    const std::string DEFAULT_OBSTACLES_LAYER_IMAGE_PATH = "../graphics/world_map/avarayr/land_tiles.png";
    const std::string DEFAULT_BOTTOM_MATRIX_PATH = "../src/world_map/default_bottom_matrix.txt";
    const std::string DEFAULT_OBSTACLES_MATRIX_PATH = "../src/world_map/default_obstacles_matrix.txt";

    // OTHER MAPS
    const std::string AVARAYR_NAME = "avarayr";
    const std::string PELENOR_NAME = "pelenor";
    const std::string UDUN_NAME = "udun";

    const int AVAILABLE_MAPS_COUNT = 3;
    const std::string AVAILABLE_MAP_NAMES[3] = {"avarayr", "pelenor", "udun"};

// PARAMETERS
    int m_height;
    int m_width;
    std::string m_name;
    sf::Image m_bottom_layer_image;
    sf::Texture m_bottom_layer_texture;
    sf::Sprite m_bottom_layer_sprite;
    sf::Image m_obstacles_layer_image;
    sf::Texture m_obstacles_layer_texture;
    sf::Sprite m_obstacles_layer_sprite;
    std::vector<std::vector<int>> m_bottom_layer;
    std::vector<std::vector<int>> m_obstacles_layer;
    std::vector<std::vector<bool>> m_obstacles_matrix;
    bool m_map_was_made;
}; // class - Avarayr

#endif // MAPS_H