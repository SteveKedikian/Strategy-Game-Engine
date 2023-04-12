#include "auxiliary_functions.h"

#include <cmath>

Direction mouseRightClickDirectionFromObject(float delta_x, float delta_y) {
    if (delta_x < -abs(delta_y)) {
        return Direction::Left;
    } else if (delta_x > abs(delta_y)) {
        return Direction::Right;
    } else if (delta_y > abs(delta_x)) {
        return Direction::Up;
    }
    return Direction::Down; // delta_y < -abs(delta_x)
}