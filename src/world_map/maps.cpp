#include "maps.h"

#include <fstream>
#include <iostream>

Map::Map(const std::string& map_name) {
    bool exists = false;
    for (int i = 0; i < AVAILABLE_MAPS_COUNT; ++i) {
        if (map_name == AVAILABLE_MAP_NAMES[i]) {
            exists = true;
            break;
        }
    }

    if (exists) {
        m_name = map_name;
    } else {
        m_name = DEFAULT_NAME;
    }

    m_map_was_made = false;
}

void Map::mapMaker() {
    dataAssigning();
    bottomLayerSetUp();
    obstaclesLayerSetUp();
    obstaclesMatrixSetUp();

    // std::ofstream fout;
    // fout.open("test.txt");

    // for (int i = 0; i < m_height * 32; ++i) {
    //     for (int j = 0; j < m_width * 32; ++j) {
    //         fout << m_obstacles_matrix[i][j] << " ";
    //     }
    //     fout << "\n";
    // }
    // fout.close()
}

void Map::dataAssigning() {
    if (m_map_was_made) {
        return;
    }

    if (m_name == DEFAULT_NAME) {
        m_height = DEFAULT_HEIGHT;
        m_width = DEFAULT_WIDTH;
        m_bottom_layer_image.loadFromFile(DEFAULT_BOTTOM_LAYER_IMAGE_PATH);
        m_obstacles_layer_image.loadFromFile(DEFAULT_OBSTACLES_LAYER_IMAGE_PATH);
    } else if (m_name == AVARAYR_NAME) {
        //
    } else if (m_name == PELENOR_NAME) {
        //
    } else if (m_name == UDUN_NAME) {
        //
    }
    m_bottom_layer_texture.loadFromImage(m_bottom_layer_image);
    m_bottom_layer_sprite.setTexture(m_bottom_layer_texture);
    m_obstacles_layer_texture.loadFromImage(m_obstacles_layer_image);
    m_obstacles_layer_sprite.setTexture(m_obstacles_layer_texture);
    m_bottom_layer.resize(m_height, std::vector<int> (m_width));
    m_obstacles_layer.resize(m_height, std::vector<int> (m_width));
    m_obstacles_matrix.resize(m_height * 32, std::vector<bool> (m_width * 32, false));
}

void Map::bottomLayerSetUp() {
    std::ifstream fin;
    std::string path;
    std::string num = "";
    int i = 0;
    char c;

    if (m_name == DEFAULT_NAME) {
        path = DEFAULT_BOTTOM_MATRIX_PATH;
    } else if (m_name == AVARAYR_NAME) {
        //
    } else if (m_name == PELENOR_NAME) {
        //
    } else if (m_name == UDUN_NAME) {
        //
    }

    fin.open(path);
    if (fin.is_open()) {
        for (int i = 0; i < m_height; ++i) {
            int j = 0;
            while (fin.get(c) && j < m_width) {
                if (c == ',') {
                    m_bottom_layer[i][j] = std::stoi(num);
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
        std::cout << "PATH: src/world_map/maps.cpp\n";
        std::cout << "FILE: " + path + "\n";
        exit(1);
    }
    fin.close();
}

void Map::obstaclesLayerSetUp() {
    std::ifstream fin;
    std::string path;
    std::string num = "";
    int i = 0;
    char c;

    if (m_name == DEFAULT_NAME) {
        path = DEFAULT_OBSTACLES_MATRIX_PATH;
    } else if (m_name == AVARAYR_NAME) {
        //
    } else if (m_name == PELENOR_NAME) {
        //
    } else if (m_name == UDUN_NAME) {
        //
    }

    fin.open(path);
    if (fin.is_open()) {
        for (int i = 0; i < m_height; ++i) {
            int j = 0;
            while (fin.get(c) && j < m_width) {
                if (c == ',') {
                    m_obstacles_layer[i][j] = std::stoi(num);
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
        std::cout << "PATH: src/world_map/maps.cpp\n";
        std::cout << "FILE: " + path + "\n";
        exit(1);
    }
    fin.close();
}

void Map::obstaclesMatrixSetUp() {
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_obstacles_layer[i][j] - 1 == 60) { // rock
                setFalse32x32(i, j);
            }
        }
    }
}

void Map::setFalse32x32(int column, int row) {
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            m_obstacles_matrix[(column * 32) + i][(row * 32) + j] = true;
        }
    }
}

void Map::draw(sf::RenderWindow& window) {
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_bottom_layer[i][j] - 1 == 2) { // grass
                m_bottom_layer_sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
            }
            m_bottom_layer_sprite.setPosition(j * 32, i * 32);
            window.draw(m_bottom_layer_sprite);
        }
    }

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_obstacles_layer[i][j] - 1 == 60) { // rock
                m_obstacles_layer_sprite.setTextureRect(sf::IntRect(128, 64, 32, 32));
            }
            else {
                continue;
            }
            m_obstacles_layer_sprite.setPosition(j * 32, i * 32);
            window.draw(m_obstacles_layer_sprite);
        }
    }
}

const std::vector<std::vector<bool>>& Map::getObstacleMatrix() const {
    return m_obstacles_matrix;
}


/*
Avarayr::Avarayr() 
    : m_height{100}
    , m_width{100}
{   
    m_bottom_layer.resize(m_height, std::vector<int> (m_width));
    m_obstacles_layer.resize(m_height, std::vector<int> (m_width));
    m_obstacles_matrix.resize(m_height * 2, std::vector<bool> (m_width * 2, false));

    std::ifstream fin;
    fin.open("../src/world_map/avarayr_bottom_layer_matrix.txt");

    std::string num = "";
    char c;

    int i = 0;
    if (fin.is_open()) {
        for (int i = 0; i < m_height; ++i) {
            int j = 0;
            while (fin.get(c) && j < m_width) {
                if (c == ',') {
                    m_bottom_layer[i][j] = std::stoi(num);
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
        std::cout << "PATH: src/world_map/maps.cpp\n";
        std::cout << "FILE: avarayr_bottom_layer_matrix.txt\n";
        exit(1);
    }
    fin.close();

    /////////////////////////////

    fin.open("../src/world_map/avarayr_obstacles_layer_matrix.txt");
    num = "";

    i = 0;
    if (fin.is_open()) {
        for (int i = 0; i < m_height; ++i) {
            int j = 0;
            while (fin.get(c) && j < m_width) {
                if (c == ',') {
                    m_obstacles_layer[i][j] = std::stoi(num);
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
        std::cout << "PATH: src/world_map/maps.cpp\n";
        std::cout << "FILE: avarayr_obstacles_layer_matrix.txt\n";
        exit(1);
    }
    fin.close();
}

void Avarayr::draw(sf::RenderWindow& window) {
    sf::Image map_image;
    map_image.loadFromFile("../graphics/world_map/avarayr/land_tiles.png");
    sf::Texture map_texture;
    map_texture.loadFromImage(map_image);
    sf::Sprite map_sprite;
    map_sprite.setTexture(map_texture);
        
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_bottom_layer[i][j] - 1 == 2) { // grass 1
                map_sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 3) { // grass 2
                map_sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 30) { // grass 3
                map_sprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 31) { // grass 4
                map_sprite.setTextureRect(sf::IntRect(96, 32, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 58) { // dark_grass 1
                map_sprite.setTextureRect(sf::IntRect(64, 64, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 59) { // dark_grass 2
                map_sprite.setTextureRect(sf::IntRect(96, 64, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 86) { // dark_grass 3
                map_sprite.setTextureRect(sf::IntRect(64, 96, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 87) { // dark_grass 4
                map_sprite.setTextureRect(sf::IntRect(96, 96, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 4) { // mud 1
                map_sprite.setTextureRect(sf::IntRect(128, 0, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 5) { // mud 2
                map_sprite.setTextureRect(sf::IntRect(160, 0, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 32) { // mud 3
                map_sprite.setTextureRect(sf::IntRect(128, 32, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 33) { // mud 4
                map_sprite.setTextureRect(sf::IntRect(160, 32, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 62) { // sand 1
                map_sprite.setTextureRect(sf::IntRect(192, 64, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 63) { // sand 2
                map_sprite.setTextureRect(sf::IntRect(224, 64, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 90) { // sand 3
                map_sprite.setTextureRect(sf::IntRect(192, 96, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 91) { // sand 4
                map_sprite.setTextureRect(sf::IntRect(224, 96, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 112) { // water 1
                map_sprite.setTextureRect(sf::IntRect(0, 128, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 113) { // water 2
                map_sprite.setTextureRect(sf::IntRect(32, 128, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 140) { // water 3
                map_sprite.setTextureRect(sf::IntRect(0, 160, 32, 32));
            }
            else if (m_bottom_layer[i][j] - 1 == 141) { // water 4
                map_sprite.setTextureRect(sf::IntRect(32, 160, 32, 32));
            }

            map_sprite.setPosition(j * 32, i * 32);
            window.draw(map_sprite);
        }            
    }

    map_image.loadFromFile("../graphics/world_map/avarayr/obstacle_tiles.png");
    map_texture.loadFromImage(map_image);
    map_sprite.setTexture(map_texture);

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            if (m_obstacles_layer[i][j] - 1 == 97) { // tree_1 1
                map_sprite.setTextureRect(sf::IntRect(32, 192, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 98) { // tree_1 2
                map_sprite.setTextureRect(sf::IntRect(64, 192, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 112) { // tree_1 3
                map_sprite.setTextureRect(sf::IntRect(0, 224, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 113) { // tree_1 4
                map_sprite.setTextureRect(sf::IntRect(32, 224, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 114) { // tree_1 5
                map_sprite.setTextureRect(sf::IntRect(64, 224, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 128) { // tree_1 6
                map_sprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 129) { // tree_1 7
                map_sprite.setTextureRect(sf::IntRect(32, 256, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 130) { // tree_1 8
                map_sprite.setTextureRect(sf::IntRect(64, 256, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 131) { // tree_1 9
                map_sprite.setTextureRect(sf::IntRect(96, 256, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 144) { // tree_1 10
                map_sprite.setTextureRect(sf::IntRect(0, 288, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 145) { // tree_1 11
                map_sprite.setTextureRect(sf::IntRect(32, 288, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 146) { // tree_1 12
                map_sprite.setTextureRect(sf::IntRect(64, 288, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 147) { // tree_1 13
                map_sprite.setTextureRect(sf::IntRect(96, 288, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 160) { // tree_1 14
                map_sprite.setTextureRect(sf::IntRect(0, 320, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 161) { // tree_1 15
                map_sprite.setTextureRect(sf::IntRect(32, 320, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 162) { // tree_1 16
                map_sprite.setTextureRect(sf::IntRect(64, 320, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 163) { // tree_1 17
                map_sprite.setTextureRect(sf::IntRect(96, 320, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 176) { // tree_1 18
                map_sprite.setTextureRect(sf::IntRect(0, 352, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 177) { // tree_1 19
                m_obstacles_matrix[i * 2][j * 2] = true;
                m_obstacles_matrix[i * 2][j * 2 + 1] = true;
                // m_obstacles[i * 2 + 1][j * 2 + 1] = -1;
                // m_obstacles[i * 2 + 1][j * 2] = -1;   
                map_sprite.setTextureRect(sf::IntRect(32, 352, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 178) { // tree_1 20
                m_obstacles_matrix[i * 2][j * 2] = true;
                m_obstacles_matrix[i * 2][j * 2 + 1] = true;
                // m_obstacles[i * 2 + 1][j * 2 + 1] = -1;
                // m_obstacles[i * 2 + 1][j * 2] = -1;
                map_sprite.setTextureRect(sf::IntRect(64, 352, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
            else if (m_obstacles_layer[i][j] - 1 == 179) { // tree_1 21
                map_sprite.setTextureRect(sf::IntRect(96, 352, 32, 32));
                map_sprite.setPosition(j * 32, i * 32);
                window.draw(map_sprite);
            }
        }
    }

    // for (int i = 0; i < m_height * 2; ++i) {
    //     for (int j = 0; j < m_width * 2; ++j) {
    //         if (m_obstacles[i][j] == 1) {
    //             map_sprite.setTextureRect(sf::IntRect(96, 32, 16, 16));
    //             map_sprite.setPosition(j * 16, i * 16);
    //             window.draw(map_sprite);
    //         }
    //         std::cout << m_obstacles[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }

}

const std::vector<std::vector<bool>>& Avarayr::getObstacleMatrix() const {
    return m_obstacles_matrix;
}
*/