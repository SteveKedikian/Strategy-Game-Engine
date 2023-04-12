#ifndef SOLDIER_H
#define SOLDIER_H

#include "unit.h"

class Soldier : public Unit
{
public:
    virtual ~Soldier() {}

public:
    virtual void select(bool select) override; // Set status 'm_selected' to given function argument
    virtual void move() override; // Set status 'm_moving' to true
    virtual void update(sf::Time dt) override; // Update Soldier's atributes, by given time and statuses that were changed before update.
    virtual void setMoveToCoordinates(float x, float y) override; // Coordinates of mouse will be calculated and set for 'm_move_to_coordinates'
    virtual void setDiagonalSpeedCoordinates(float x, float y) override; // Set 'm_diagonal_speed_coordinates' value
    virtual void setWatchingDirection(Direction direction) override;

public:
    virtual sf::Sprite getSprite() override;
    virtual bool isSelected() override; // Return 'm_selected' value, shows if Soldier was selected or not
    virtual float getSpeed() override;

protected:
/* STATS*/
    // float damage_;

/* STATUSES */
    // bool attacking_;

}; // class - Soldier

#endif // SOLDIER_H