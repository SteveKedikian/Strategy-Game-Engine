#include "soldier.h"

void Soldier::select(bool select) {
    m_selected = select;
}

void Soldier::move() {
    m_moving = true;
}

void Soldier::update(sf::Time dt) {
    if (m_selected) {
        // CHANGE COLOR OR MARK HERE
    }
    else {
        // SET DEFAULT TEXTURE
    }

    if (m_moving) {
        // This section must be changed to ANIMTION CLASS, but we don't know what pictures will be used
        // So created Animation class right now that will be changed anyway, no needed yet
        m_sprite.setPosition(m_sprite.getPosition().x + m_diagonal_speed_coordinates.x * dt.asSeconds(),
                             m_sprite.getPosition().y + m_diagonal_speed_coordinates.y * dt.asSeconds());
        
        if ((m_move_to_coordinates.x + 2 > m_sprite.getPosition().x + m_frame_rectangle.width / 2 &&
             m_move_to_coordinates.x - 2 <= m_sprite.getPosition().x + m_frame_rectangle.width / 2) &&
            (m_move_to_coordinates.y + 2 > m_sprite.getPosition().y + m_frame_rectangle.height  &&
             m_move_to_coordinates.y - 2 <= m_sprite.getPosition().y + m_frame_rectangle.height ))
        {
            m_moving = false;
            m_frame_rectangle.left = m_sprite.getTexture()->getSize().x / 3 ;

            int row = 0; // For DarkLegioner's picture, this is the moving up animation row
            if (m_watching_direction == Direction::Left) { 
                row = 3;
            }
            else if (m_watching_direction == Direction::Right) {
                row = 1;
            }
            else if (m_watching_direction == Direction::Down) {
                row = 2;
            }

            m_frame_rectangle.top = 65 * row;
            m_sprite.setTextureRect(m_frame_rectangle);
        }

        
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
            m_timer += dt.asSeconds();
        }
    }
}

sf::Sprite Soldier::getSprite() {
    return m_sprite;
}

bool Soldier::isSelected() {
    return m_selected;
}

void Soldier::setMoveToCoordinates(float x, float y) {
    m_move_to_coordinates.x = x;
    m_move_to_coordinates.y = y;
}

void Soldier::setDiagonalSpeedCoordinates(float x, float y) {
    m_diagonal_speed_coordinates.x = x;
    m_diagonal_speed_coordinates.y = y;
}

float Soldier::getSpeed() {
    return m_speed;
}

void Soldier::setWatchingDirection(Direction direction) {
    m_watching_direction = direction;
}