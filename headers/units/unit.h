#ifndef UNIT_H
#define UNIT_H

#include "../constants_and_enums/direction_enum.h"

#include <SFML/Graphics.hpp>

class Unit
{
public:
    virtual ~Unit() {}

public:
    virtual void select(bool select) = 0; // Set status 'm_selected' to given function argument
    virtual void move() = 0; // Set status 'm_moving' to true
    virtual void update(sf::Time dt) = 0; // Update Unit's atributes, by given time and statuses that were changed before update.
    virtual void setMoveToCoordinates(float x, float y) = 0; // Coordinates of mouse will be calculated and set for 'm_move_to_coordinates'
    virtual void setDiagonalSpeedCoordinates(float x, float y) = 0; // Set 'm_diagonal_speed_coordinates' value
    virtual void setWatchingDirection(Direction direction) = 0;

public:
    virtual sf::Sprite getSprite() = 0;
    virtual bool isSelected() = 0; // Return 'm_selected' value, shows if Unit was selected or not
    virtual float getSpeed() = 0;

protected:
/* STATS */
    float m_speed;
    // float m_hp;

/* STATUSES */
    bool m_selected;
    bool m_moving;
    // bool m_alive;

/* TEXTURE AND SPRITE */
    sf::Texture m_texture;
    sf::Sprite m_sprite;

/* FOR ANIMATION */
// !!!!!!!!!!! THIS WILL BE UPDATED
//  WILL BE ADDED ANIMATION CLASS
    sf::IntRect m_frame_rectangle; // Frame cut with rectangle shape from the picture
    bool m_picture_row_end; // For animation, to change frame cutting of the picture from left to right, or right to left
    float m_timer = 0.05f; // Animation delay time

/* ACTION COORDINATES */
    sf::Vector2f m_move_to_coordinates; // Last moving direction coordinates

    sf::Vector2f m_diagonal_speed_coordinates; // After calculating distance of (x1, y1, x2, y2)
                                               // Calculate diagonal's straight moving medium of x and y

    Direction m_watching_direction; // After mouse action, moving attacking or something else, Unit has 4 directions to watch: left, right, up, down
                                    // After knowing the direction, the suitable frame from picture sheet is choosed
                                    // Also can be used for other things, like vision from from back and front
}; // class - Unit

#endif // UNIT_H