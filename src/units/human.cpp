#include "human.h"

void Human::move(const sf::Vector2f& location) {
    Utility utility_function;
    m_active = true;
    m_moving = true;

    sf::Vector2f start(m_sprite.getPosition().x + m_frame_rectangle.width / 2, m_sprite.getPosition().y + m_frame_rectangle.height);

    utility_function.pathFinder(m_map->getObstacleMatrix(), m_moving_trajectory, start, location);
}

void Human::moveClear() {
    m_moving = false;
    std::queue<sf::Vector2f> empty;
    std::swap(m_moving_trajectory, empty);
    m_move_vector_speed.x = 0.0f;
    m_move_vector_speed.y = 0.0f;
}

void Human::moveSetup() {
    Utility utility_function;
    
    float delta_x = (float)m_move_to_location.x - (float)m_sprite.getPosition().x - (float)m_sprite.getTextureRect().width / 2; 
    float delta_y = (float)m_sprite.getPosition().y - (float)m_move_to_location.y + (float)m_sprite.getTextureRect().height;
    float distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    m_move_vector_speed.x = (delta_x / distance) * m_speed;
    m_move_vector_speed.y = (-delta_y / distance) * m_speed;
    
    m_watching_direction = utility_function.mouseDirectionFromObject(delta_x, delta_y);
}