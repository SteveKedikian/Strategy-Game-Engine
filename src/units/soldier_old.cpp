#include "soldier_old.h"
#include "../utility.h"

#include <cmath>

#include <iostream>
// #include <fstream>
// #include <typeinfo>

void Soldier::update(const sf::Time& delta_time, const Map& map) {
    if (m_selected) {
        if (m_controller == Control::Player) {
            m_sprite.setColor(sf::Color::Blue);
        } else if (m_controller == Control::AIBot) {
            m_sprite.setColor(sf::Color::Red);
        }            
    }
    else {
        m_sprite.setColor(sf::Color::White);
    }

    if (m_moving) {
        if (!m_moving_trajectory.empty()) {
            // std::cout << "\nhere";
            m_move_to_coordinates = m_moving_trajectory.front();
            moveSetup();
        }
        // std::cout << "move_to:: " << m_move_to_coordinates.x << " : " << m_move_to_coordinates.y << "\n";
        // std::cout << "vectorsp:: " << m_vector_speed.x << " : " << m_vector_speed.y << "\n";
        // This part is all about the picture, for example first row is moving up animation, so the row we need of the picture is 0 row
        // But if moving animation was at third row, we would need number 2
        int row = 0; // For DarkLegioner picture, this is the moving up animation row
        if (m_watching_direction == Direction::Left) { 
            row = 3;
        }
        else if (m_watching_direction == Direction::Right) {
            row = 1;
        }
        else if (m_watching_direction == Direction::Down) {
            row = 2;
        }

        // 0 48 96
        if (m_timer > 0.2f) {
            if (m_picture_row_end) {
                m_frame_rectangle.left -= 48;
                if (m_frame_rectangle.left <= 0) {
                    m_picture_row_end = false;
                }
            }
            else {
                m_frame_rectangle.left += 48;
                if (m_frame_rectangle.left >= 96) {
                    m_picture_row_end = true;
                }
            }
            m_frame_rectangle.top = 65 * row;
            m_sprite.setTextureRect(m_frame_rectangle);
            m_timer = 0.0f;
        }
        else {
            m_timer += delta_time.asSeconds();
        }

        m_sprite.setPosition(m_sprite.getPosition().x + m_vector_speed.x * delta_time.asSeconds(),
                             m_sprite.getPosition().y + m_vector_speed.y * delta_time.asSeconds());
        
        if ((m_move_to_coordinates.x + 2 > m_sprite.getPosition().x + m_frame_rectangle.width / 2 &&
             m_move_to_coordinates.x - 2 <= m_sprite.getPosition().x + m_frame_rectangle.width / 2) &&
            (m_move_to_coordinates.y + 2 > m_sprite.getPosition().y + m_frame_rectangle.height  &&
             m_move_to_coordinates.y - 2 <= m_sprite.getPosition().y + m_frame_rectangle.height ))
        {
            m_moving_trajectory.pop();
            if (m_moving_trajectory.empty()) {
                m_moving = false;
                // m_move_to_coordinates.x = MOVE_TO_COORDINATES_X;
                // m_move_to_coordinates.y = MOVE_TO_COORDINATES_Y;
                m_frame_rectangle.left = m_sprite.getTexture()->getSize().x / 3 ; // MAGIC
                m_frame_rectangle.top = 65 * row; // MAGIC
                m_sprite.setTextureRect(m_frame_rectangle);
            }
        }
    }

    if (m_attacking) {
        if ((abs(getFootPosition().x - m_attack_target->getFootPosition().x) <= m_attack_range) &&
        (abs(getFootPosition().y - m_attack_target->getFootPosition().y) <= m_attack_range)) {
            std::cout << " -5hp  " << std::endl;
            strike();
        } else if ((m_attack_target->getFootPosition() != m_moving_trajectory.back()) && m_timer > 2.0f) {
            moveClear();
            move(m_attack_target->getFootPosition(), map);
            m_timer = 0.0f;
        }
        m_timer += delta_time.asSeconds();
    }
}

void Soldier::select(bool select) {
    m_selected = select;
}

void Soldier::move(const sf::Vector2f& coordinates, const Map& map) {
    Utility utility_function;
    // m_moving_trajectory.push(coordinates);
    // moveSetup();
    m_moving = true;

    // float x = m_sprite.getPosition().x + m_frame_rectangle.width / 2;
    // float y = m_sprite.getPosition().y + m_frame_rectangle.height;

    sf::Vector2f start(m_sprite.getPosition().x + m_frame_rectangle.width / 2, m_sprite.getPosition().y + m_frame_rectangle.height);
    // Utility utility_function;
    
    // std::ofstream fout;
    // fout.open("text.txt");

    // for (int i = 0; i < 200; ++i) {
    //     for (int j = 0; j < 200; ++j) {
    //         fout << map.getObstacleMatrix()[i][j] << " ";
    //     }
    //     fout << "\n";
    // }

    utility_function.pathFinder(map.getObstacleMatrix(), m_moving_trajectory, start, coordinates);
}

void Soldier::attack(Soldier* const attack_target) {
    m_attack_target = attack_target;
}

void Soldier::moveSetup() {
    Utility utility_function;
    // if (m_move_to_coordinates.x <= 0 && m_move_to_coordinates.y <= 0) {
    //     m_move_to_coordinates = m_moving_trajectory.front();
    // }

    // std::cout << m_move_to_coordinates.x << " : " << m_move_to_coordinates.y << "\n";
    // distance between (x1, y1) and (x2, y2)
    // distance = square_root(delta_x^2 + delta_y^2)
    // count delta_y = y1 - y2 (The reason that we did y2 - y1, because we need that information for choosing Unit's watching direction)
    float delta_x = (float)m_move_to_coordinates.x - (float)m_sprite.getPosition().x - (float)m_sprite.getTextureRect().width / 2; 
    float delta_y = (float)m_sprite.getPosition().y - (float)m_move_to_coordinates.y + (float)m_sprite.getTextureRect().height;
    float distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    // std::cout << "dis: " << distance << "\n";
    // std::cout << "delta: " << delta_x << " : " << delta_y << "\n";

    // The distance we calculated, is showing diagonal from Unit to Mouse click coordinates
    // By using (delta_x / distance) * Unit_Speed, we count X coordinate raising rate, so we can start moving our Unit diagonaly
    // Same logic for delta_y but with minus, because of change we did before (y2 - y1)
    m_vector_speed.x = (delta_x / distance) * m_speed;
    m_vector_speed.y = (-delta_y / distance) * m_speed;
    
    m_watching_direction = utility_function.mouseDirectionFromObject(delta_x, delta_y);
}

void Soldier::attackingTarget() {
    std::cout << "slash\n";
    m_moving = false;
}

void Soldier::setWatchingDirection(Direction direction) {
    m_watching_direction = direction;
}

void Soldier::moveClear() {
    std::queue<sf::Vector2f> empty;
    std::swap(m_moving_trajectory, empty);
    m_vector_speed.x = 0.0f;
    m_vector_speed.y = 0.0f;
}

const sf::Vector2f Soldier::getFootPosition() const {
    sf::Vector2f foot_position(m_sprite.getPosition().x + m_frame_rectangle.width / 2, m_sprite.getPosition().y + m_frame_rectangle.height);
    return foot_position;
}

const bool Soldier::onUnit(const sf::Vector2f& mouse_position) const {
    return ((mouse_position.x > m_sprite.getPosition().x && mouse_position.x < m_sprite.getPosition().x + m_frame_rectangle.width) && 
            (mouse_position.y > m_sprite.getPosition().y && mouse_position.y < m_sprite.getPosition().y + m_frame_rectangle.height));
}

const sf::Sprite& Soldier::getSprite() const {
    return m_sprite;
}

const bool Soldier::isSelected() const {
    return m_selected;
}