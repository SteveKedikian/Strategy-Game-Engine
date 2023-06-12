#include "dark_legioner.h"

#include <iostream>

DarkLegioner::DarkLegioner(const sf::Vector2f start, Map* const map, Control controller)
{
// STATS
    m_controller = controller;
    m_name = "dark_legioner";
    // m_faction TO DO !
    // m_human_type TO DO !
    m_map = map;
    m_hp = 300.0f;
    m_collision_radius = 10.0f;
    m_price = 500;
    m_speed = 130.0f;
    m_attack_damage = 70.0f;
    m_attack_range = 40.0f;
    m_aggression_trigger_radius = 100.0f;
// TEXTURE AND SPRITE
    m_texture.loadFromFile("../graphics/units/melee_infantry/dark_legioner/dark_legioner_moving.png");
    m_sprite.setTexture(m_texture);
// ANIMATION
    m_frame_rectangle.left = 48; // Picture position X
    m_frame_rectangle.top = 128; // Picture Position Y
    m_frame_rectangle.width = 41; // Size of FRAME CUT width
    m_frame_rectangle.height = 64; // Size of FRAME CUT height
    m_sprite.setTextureRect(m_frame_rectangle);
    m_sprite.setPosition(start);
    m_picture_row_end = false;
// ACTION
    m_watching_direction = Direction::Down;
}