#ifndef HUMAN_H
#define HUMAN_H

#include "unit.h"
#include "../utility.h"

#include <queue>
#include <cmath>

class Human : public Unit {
public:
    Human() = default;
    virtual ~Human() = default;
public:
    const bool isActive() const {return m_active;}
    void move(const sf::Vector2f& move_to_location);
    void moveClear();
protected:
    virtual void moveUpdate(const sf::Time& delta_time) = 0;
    void moveSetup();
protected:
// CONSTANTS
    const float MOVE_ANIMATION_TIMER_LIMIT = 0.2f;
// STATS
    HumanType m_human_type;
    float m_speed;
// STATUSES
    bool m_active = false;
    bool m_moving = false;

// ANIMATION
// !!!!!!!!!!! THIS WILL BE UPDATED
//  WILL BE ADDED ANIMATION CLASS
    sf::IntRect m_frame_rectangle; // Frame cut with rectangle shape from the picture
    bool m_picture_row_end; // For animation, to change frame cutting of the picture from left to right, or right to left
    float m_move_animation_timer{}; // Animation delay time
// ACTION
    sf::Vector2f m_move_to_location{}; // Current moving coordinates
    sf::Vector2f m_move_vector_speed{}; // After calculating distance of (x1, y1, x2, y2)
                                        // Calculate diagonal's straight moving medium of x and y
    std::queue<sf::Vector2f> m_moving_trajectory{}; // Multiple moving coordinates 

    Direction m_watching_direction; // After mouse action, moving attacking or something else, Unit has 4 directions to watch: left, right, up, down
                                    // After knowing the direction, the suitable frame from picture sheet is choosed
                                    // Also can be used for other things, like vision from from back and front
};

#endif // HUMAN_H