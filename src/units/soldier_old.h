#ifndef SOLDIER_H
#define SOLDIER_H

#include "unit.h"

class Soldier : public Unit
{
public:
    Soldier() = default;
    ~Soldier() = default;
public:
    void select(bool select) override; // Set status 'm_selected' to given function argument
    void move(const sf::Vector2f& coordinates, const Map& map) override;
    void attack(Soldier* const attack_target);
    void update(const sf::Time& delta_time, const Map& map) override;
    void setWatchingDirection(Direction direction) override;
    void moveClear() override; // Clear move data
    void attackingTarget();
public:
    const sf::Sprite& getSprite() const override;
    const bool onUnit(const sf::Vector2f& mouse_position) const override;
    const bool isSelected() const override; // Return 'm_selected' value, shows if Soldier was selected or not
    const sf::Vector2f getFootPosition() const;
protected:
    void moveSetup() override;
protected:
// STATS
    Soldier* m_attack_target = nullptr;
    // float damage_;
    float m_attack_range;
    float m_attack_trigger_range;
    
// STATUSES
    bool m_attacking = false;
}; // Soldier

#endif // SOLDIER_H