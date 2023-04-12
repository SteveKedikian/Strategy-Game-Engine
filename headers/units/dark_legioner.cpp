#include "dark_legioner.h"

nsm::DarkLegioner::DarkLegioner(float start_pos_x, float start_pos_y) {
    /* STATS */
    m_speed = 130.0f;

    /* STATUSES */
    m_selected = false;
    m_moving = false;

    /* TEXTURE AND SPRITE */
    m_texture.loadFromFile("../graphics/units/melee_infantry/dark_legioner/dark_legioner_moving.png");
    m_sprite.setTexture(m_texture);

    /* ANIMATION */
    m_frame_rectangle.left = 48; // Picture position X
    m_frame_rectangle.top = 128; // Picture Position Y
    m_frame_rectangle.width = 41; // Size of FRAME CUT width
    m_frame_rectangle.height = 64; // Size of FRAME CUT height
    m_sprite.setTextureRect(m_frame_rectangle);
    m_sprite.setPosition(start_pos_x, start_pos_y);
    m_picture_row_end = false;

    /* ACTION COORDINATES */
    m_move_to_coordinates = {};
    m_diagonal_speed_coordinates= {};
    m_watching_direction = Direction::Down;
}