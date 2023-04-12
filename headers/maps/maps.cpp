#include "maps.h"

#include <fstream>
#include <iostream>
#include <string>

nsm::Avarayr::Avarayr() 
    : m_height{100}
    , m_width{100}
{   
    m_bottom_layer_matrix.resize(m_height, std::vector<int> (m_width));
    m_obstacles_layer_matrix.resize(m_height, std::vector<int> (m_width));
    m_obstacle_path_find_matrix.resize(m_height * 2, std::vector<int> (m_width * 2));

    std::ifstream fin;
    fin.open("../headers/maps/avarayr_bottom_layer_matrix.txt");

    std::string num = "";
    char c;

    int i = 0;
    if (fin.is_open()) {
        for (int i = 0; i < m_height; ++i) {
            int j = 0;
            while (fin.get(c) && j < m_width) {
                if (c == ',') {
                    m_bottom_layer_matrix[i][j] = std::stoi(num);
                    num = "";
                    ++j;
                    continue;
                }
                else if (c == '\n') {
                    continue;
                }

                num += c;
            }
        }
    }
    else {
        std::cout << "ERROR: COULD NOT OPEN THE FILE !\n";
        std::cout << "PATH: headers/map/maps.cpp\n";
        std::cout << "FILE: avarayr_bottom_layer_matrix.txt\n";
        exit(1);
    }
    fin.close();

    /////////////////////////////

    fin.open("../headers/maps/avarayr_obstacles_layer_matrix.txt");
    num = "";

    i = 0;
    if (fin.is_open()) {
        for (int i = 0; i < m_height; ++i) {
            int j = 0;
            while (fin.get(c) && j < m_width) {
                if (c == ',') {
                    m_obstacles_layer_matrix[i][j] = std::stoi(num);
                    num = "";
                    ++j;
                    continue;
                }
                else if (c == '\n') {
                    continue;
                }

                num += c;
            }
        }
    }
    else {
        std::cout << "ERROR: COULD NOT OPEN THE FILE !\n";
        std::cout << "PATH: headers/map/maps.cpp\n";
        std::cout << "FILE: avarayr_obstacles_layer_matrix.txt\n";
        exit(1);
    }
    fin.close();
}

void nsm::Avarayr::draw(sf::RenderWindow& window) {
    sf::Image map_image;
    map_image.loadFromFile("../graphics/maps/avarayr/land_tiles.png");
    sf::Texture map_texture;
    map_texture.loadFromImage(map_image);
    sf::Sprite map_sprite;
    map_sprite.setTexture(map_texture);
        
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_bottom_layer_matrix[i][j] - 1 == 2) { // grass 1
                map_sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 3) { // grass 2
                map_sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 30) { // grass 3
                map_sprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 31) { // grass 4
                map_sprite.setTextureRect(sf::IntRect(96, 32, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 58) { // dark_grass 1
                map_sprite.setTextureRect(sf::IntRect(64, 64, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 59) { // dark_grass 2
                map_sprite.setTextureRect(sf::IntRect(96, 64, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 86) { // dark_grass 3
                map_sprite.setTextureRect(sf::IntRect(64, 96, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 87) { // dark_grass 4
                map_sprite.setTextureRect(sf::IntRect(96, 96, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 4) { // mud 1
                map_sprite.setTextureRect(sf::IntRect(128, 0, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 5) { // mud 2
                map_sprite.setTextureRect(sf::IntRect(160, 0, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 32) { // mud 3
                map_sprite.setTextureRect(sf::IntRect(128, 32, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 33) { // mud 4
                map_sprite.setTextureRect(sf::IntRect(160, 32, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 62) { // sand 1
                map_sprite.setTextureRect(sf::IntRect(192, 64, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 63) { // sand 2
                map_sprite.setTextureRect(sf::IntRect(224, 64, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 90) { // sand 3
                map_sprite.setTextureRect(sf::IntRect(192, 96, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 91) { // sand 4
                map_sprite.setTextureRect(sf::IntRect(224, 96, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 112) { // water 1
                map_sprite.setTextureRect(sf::IntRect(0, 128, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 113) { // water 2
                map_sprite.setTextureRect(sf::IntRect(32, 128, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 140) { // water 3
                map_sprite.setTextureRect(sf::IntRect(0, 160, 32, 32));
            }
            else if (m_bottom_layer_matrix[i][j] - 1 == 141) { // water 4
                map_sprite.setTextureRect(sf::IntRect(32, 160, 32, 32));
            }

            map_sprite.setPosition(j * 32, i * 32);
            window.draw(map_sprite);
        }            
    }

    map_image.loadFromFile("../graphics/maps/avarayr/obstacle_tiles.png");
    map_texture.loadFromImage(map_image);
    map_sprite.setTexture(map_texture);

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_obstacles_layer_matrix[i][j] - 1 == 97) { // tree_1 1
                map_sprite.setTextureRect(sf::IntRect(32, 192, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 98) { // tree_1 2
                map_sprite.setTextureRect(sf::IntRect(64, 192, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 112) { // tree_1 3
                map_sprite.setTextureRect(sf::IntRect(0, 224, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 113) { // tree_1 4
                map_sprite.setTextureRect(sf::IntRect(32, 224, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 114) { // tree_1 5
                map_sprite.setTextureRect(sf::IntRect(64, 224, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 128) { // tree_1 6
                map_sprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 129) { // tree_1 7
                map_sprite.setTextureRect(sf::IntRect(32, 256, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 130) { // tree_1 8
                map_sprite.setTextureRect(sf::IntRect(64, 256, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 131) { // tree_1 9
                map_sprite.setTextureRect(sf::IntRect(96, 256, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 144) { // tree_1 10
                map_sprite.setTextureRect(sf::IntRect(0, 288, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 145) { // tree_1 11
                map_sprite.setTextureRect(sf::IntRect(32, 288, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 146) { // tree_1 12
                map_sprite.setTextureRect(sf::IntRect(64, 288, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 147) { // tree_1 13
                map_sprite.setTextureRect(sf::IntRect(96, 288, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 160) { // tree_1 14
                map_sprite.setTextureRect(sf::IntRect(0, 320, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 161) { // tree_1 15
                map_sprite.setTextureRect(sf::IntRect(32, 320, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 162) { // tree_1 16
                map_sprite.setTextureRect(sf::IntRect(64, 320, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 163) { // tree_1 17
                map_sprite.setTextureRect(sf::IntRect(96, 320, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 176) { // tree_1 18
                map_sprite.setTextureRect(sf::IntRect(0, 352, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 177) { // tree_1 19
                m_obstacle_path_find_matrix[i * 2][j * 2] = 1;
                m_obstacle_path_find_matrix[i * 2][j * 2 + 1] = 1;
                // m_obstacle_path_find_matrix[i * 2 + 1][j * 2 + 1] = -1;
                // m_obstacle_path_find_matrix[i * 2 + 1][j * 2] = -1;   
                map_sprite.setTextureRect(sf::IntRect(32, 352, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 178) { // tree_1 20
                m_obstacle_path_find_matrix[i * 2][j * 2] = 1;
                m_obstacle_path_find_matrix[i * 2][j * 2 + 1] = 1;
                // m_obstacle_path_find_matrix[i * 2 + 1][j * 2 + 1] = -1;
                // m_obstacle_path_find_matrix[i * 2 + 1][j * 2] = -1;
                map_sprite.setTextureRect(sf::IntRect(64, 352, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer_matrix[i][j] - 1 == 179) { // tree_1 21
                map_sprite.setTextureRect(sf::IntRect(96, 352, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
        }
    }

    // for (int i = 0; i < m_height * 2; ++i) {
    //     for (int j = 0; j < m_width * 2; ++j) {
    //         if (m_obstacle_path_find_matrix[i][j] == 1) {
    //             map_sprite.setTextureRect(sf::IntRect(96, 32, 16, 16));
    //             map_sprite.setPosition(j * 16, i * 16);
    //             window.draw(map_sprite);
    //         }
    //         std::cout << m_obstacle_path_find_matrix[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }

}