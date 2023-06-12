#include "soldier.h"

#include <iostream>

void Soldier::update(const sf::Time& delta_time) {
    if (m_hp <= 0.0f && m_alive) {
        // do animation for dying
        m_alive = false;
    }

    if (!m_alive) {
        return;
    }

    if (m_selected) {
        if (m_controller == Control::Player) {
            m_sprite.setColor(sf::Color::Blue);
        } else if (m_controller == Control::AIBot) {
            m_sprite.setColor(sf::Color::Red);
        }            
    } else {
        m_sprite.setColor(sf::Color::White);
    }

    if (m_moving) {
        moveUpdate(delta_time);
    } else if (m_following_target) {
        followTargetUpdate(delta_time);
    } else if (m_striking) {
        strikeUpdate(delta_time);
    }
}

const bool Soldier::onUnit(const sf::Vector2f& mouse_position) const {
    return (mouse_position.x > m_sprite.getPosition().x && mouse_position.x < m_sprite.getPosition().x + m_frame_rectangle.width) && 
           (mouse_position.y > m_sprite.getPosition().y && mouse_position.y < m_sprite.getPosition().y + m_frame_rectangle.height);
}

const sf::Vector2f Soldier::getStandingPosition() const {
    return sf::Vector2f(m_sprite.getPosition().x + m_frame_rectangle.width / 2, m_sprite.getPosition().y + m_frame_rectangle.height);;
}

void Soldier::moveUpdate(const sf::Time& delta_time) {
    // This part is all about the picture, for example first row is moving up animation, so the row we need of the picture is 0 row
    // But if moving animation was at third row, we would need number 2
    int row = 0; // For DarkLegioner picture, this is the moving up animation row
    if (m_watching_direction == Direction::Left) { 
        row = 3;
    } else if (m_watching_direction == Direction::Right) {
        row = 1;
    } else if (m_watching_direction == Direction::Down) {
        row = 2;
    }

    // 0 48 96
    if (m_move_animation_timer > MOVE_ANIMATION_TIMER_LIMIT) {
        if (m_picture_row_end) {
            m_frame_rectangle.left -= 48;
            if (m_frame_rectangle.left <= 0) {
                m_picture_row_end = false;
            }
        } else {
            m_frame_rectangle.left += 48;
            if (m_frame_rectangle.left >= 96) {
                m_picture_row_end = true;
            }
        }
        m_frame_rectangle.top = 65 * row;
        m_sprite.setTextureRect(m_frame_rectangle);
        m_move_animation_timer = 0.0f;
    } else {
        m_move_animation_timer += delta_time.asSeconds();
    }

    if (!m_moving_trajectory.empty()) {
        m_move_to_location = m_moving_trajectory.front();
        moveSetup();
    }

    m_sprite.setPosition(m_sprite.getPosition().x + m_move_vector_speed.x * delta_time.asSeconds(),
                            m_sprite.getPosition().y + m_move_vector_speed.y * delta_time.asSeconds());
    
    if ((m_move_to_location.x + 2 > m_sprite.getPosition().x + m_frame_rectangle.width / 2 &&
         m_move_to_location.x - 2 <= m_sprite.getPosition().x + m_frame_rectangle.width / 2) &&
        (m_move_to_location.y + 2 > m_sprite.getPosition().y + m_frame_rectangle.height  &&
         m_move_to_location.y - 2 <= m_sprite.getPosition().y + m_frame_rectangle.height ))
    {
        m_moving_trajectory.pop();
        if (m_moving_trajectory.empty()) {
            m_active = false;
            m_moving = false;
            m_frame_rectangle.left = m_sprite.getTexture()->getSize().x / 3 ; // MAGIC
            m_frame_rectangle.top = 65 * row; // MAGIC
            m_sprite.setTextureRect(m_frame_rectangle);
        }
    }
}

void Soldier::strikeUpdate(const sf::Time& delta_time) {
    // This part is all about the picture, for example first row is moving up animation, so the row we need of the picture is 0 row
    // But if moving animation was at third row, we would need number 2
    int row = 0; // For DarkLegioner picture, this is the moving up animation row
    if (m_watching_direction == Direction::Left) { 
        row = 3;
    } else if (m_watching_direction == Direction::Right) {
        row = 1;
    } else if (m_watching_direction == Direction::Down) {
        row = 2;
    }

    if (!m_enemy_target->isAlive()) {
        m_active = false;
        attackClear();
        m_frame_rectangle.left = m_sprite.getTexture()->getSize().x / 3 ; // MAGIC
        m_frame_rectangle.top = 65 * row; // MAGIC
        m_sprite.setTextureRect(m_frame_rectangle);
        return;
    } else if (!((abs(getStandingPosition().x - m_enemy_target->getStandingPosition().x) <= m_attack_range) &&
                 (abs(getStandingPosition().y - m_enemy_target->getStandingPosition().y) <= m_attack_range))) 
    {
        m_striking = false;
        followTarget();
        m_follow_target_refresh_timer = 0.0f;
    } else {
        strike(delta_time);
    }
}

void Soldier::followTargetUpdate(const sf::Time& delta_time) {
    // This part is all about the picture, for example first row is moving up animation, so the row we need of the picture is 0 row
    // But if moving animation was at third row, we would need number 2
    int row = 0; // For DarkLegioner picture, this is the moving up animation row
    if (m_watching_direction == Direction::Left) { 
        row = 3;
    } else if (m_watching_direction == Direction::Right) {
        row = 1;
    } else if (m_watching_direction == Direction::Down) {
        row = 2;
    }

    // 0 48 96
    if (m_move_animation_timer > MOVE_ANIMATION_TIMER_LIMIT) {
        if (m_picture_row_end) {
            m_frame_rectangle.left -= 48;
            if (m_frame_rectangle.left <= 0) {
                m_picture_row_end = false;
            }
        } else {
            m_frame_rectangle.left += 48;
            if (m_frame_rectangle.left >= 96) {
                m_picture_row_end = true;
            }
        }
        m_frame_rectangle.top = 65 * row;
        m_sprite.setTextureRect(m_frame_rectangle);
        m_move_animation_timer = 0.0f;
    } else {
        m_move_animation_timer += delta_time.asSeconds();
    }

    if (!m_enemy_target->isAlive()) {
        attackClear();
        m_frame_rectangle.left = m_sprite.getTexture()->getSize().x / 3 ; // MAGIC
        m_frame_rectangle.top = 65 * row; // MAGIC
        m_sprite.setTextureRect(m_frame_rectangle);
        return;
    }

    // std::cout << getStandingPosition().x << " : " << getStandingPosition().y << "P\n";
    // std::cout << m_enemy_target->getStandingPosition().x << " : " << m_enemy_target->getStandingPosition().y << "E\n";
    if ((abs(getStandingPosition().x - m_enemy_target->getStandingPosition().x) <= m_attack_range) &&
        (abs(getStandingPosition().y - m_enemy_target->getStandingPosition().y) <= m_attack_range)) 
    {
        std::cout << " attacking  " << std::endl;
        followTargetClear();
        m_striking = true;
    }

    if (m_follow_target_refresh_timer > FOLLOW_TARGET_REFRESH_TIMER_LIMIT) {
        followTargetClear();
        followTarget();
        m_follow_target_refresh_timer = 0.0f;
    }
    else {
        m_follow_target_refresh_timer += delta_time.asSeconds();
    }

    if (!m_moving_trajectory.empty()) {
        m_move_to_location = m_moving_trajectory.front();
        moveSetup();
    }

    m_sprite.setPosition(m_sprite.getPosition().x + m_move_vector_speed.x * delta_time.asSeconds(),
                         m_sprite.getPosition().y + m_move_vector_speed.y * delta_time.asSeconds());
    
    if ((m_move_to_location.x + 2 > m_sprite.getPosition().x + m_frame_rectangle.width / 2 &&
         m_move_to_location.x - 2 <= m_sprite.getPosition().x + m_frame_rectangle.width / 2) &&
        (m_move_to_location.y + 2 > m_sprite.getPosition().y + m_frame_rectangle.height  &&
         m_move_to_location.y - 2 <= m_sprite.getPosition().y + m_frame_rectangle.height ))
    {
        m_moving_trajectory.pop();
        if (m_moving_trajectory.empty()) {
            if (m_enemy_target->isAlive()) {
                followTarget();
                m_follow_target_refresh_timer = 0.0f;
            }
        }
    }
}

void Soldier::attack(Unit* const enemy) {
    m_active = true;
    m_enemy_target = enemy;
    followTarget();
}

void Soldier::followTarget() {
    if (m_enemy_target) {
        Utility utility_function;
        m_following_target = true;

        sf::Vector2f start(m_sprite.getPosition().x + m_frame_rectangle.width / 2, m_sprite.getPosition().y + m_frame_rectangle.height);

        utility_function.pathFinder(m_map->getObstacleMatrix(), m_moving_trajectory, start, m_enemy_target->getStandingPosition());
    }
}

void Soldier::attackClear() {
    m_enemy_target = nullptr;
    m_striking = false;
    followTargetClear();
}

void Soldier::followTargetClear() {
    m_following_target = false;
    std::queue<sf::Vector2f> empty;
    std::swap(m_moving_trajectory, empty);
    m_move_vector_speed.x = 0.0f;
    m_move_vector_speed.y = 0.0f;
}

void Soldier::strike(const sf::Time& delta_time) {
    if (m_attack_target_refresh_timer > ATTACK_TARGET_REFRESH_TIMER_LIMIT) {
        m_enemy_target->takeDamage(m_attack_damage);
        m_attack_target_refresh_timer = 0.0f;
    } else {
        m_attack_target_refresh_timer += delta_time.asSeconds();
    }
}