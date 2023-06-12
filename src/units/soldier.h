#ifndef SOLDIER_H
#define SOLDIER_H

#include "human.h"

class Soldier : public Human {
public:
    Soldier() = default;
    virtual ~Soldier() = default;
public:
    void update(const sf::Time& delta_time) override;
    const bool onUnit(const sf::Vector2f& mouse_position) const override;
    const sf::Vector2f getStandingPosition() const override;
    const float aggressionTriggerRadius() const {return m_aggression_trigger_radius;}
    void attack(Unit* const enemy);
    void attackClear();
protected:
    void moveUpdate(const sf::Time& delta_time) override;
    void strikeUpdate(const sf::Time& delta_time);
    void followTarget();
    void followTargetUpdate(const sf::Time& delta_time);
    void followTargetClear();
    void strike(const sf::Time& delta_time);
protected:
// CONSTANTS
    const float FOLLOW_TARGET_REFRESH_TIMER_LIMIT = 2.0f;
    const float ATTACK_TARGET_REFRESH_TIMER_LIMIT = 1.5f;
// STATS
    Unit* m_enemy_target = nullptr;
    float m_attack_damage;
    float m_attack_range;
    float m_aggression_trigger_radius;
    float m_follow_target_refresh_timer{};
    float m_attack_target_refresh_timer{};
// STATUSES
    bool m_striking = false;
    bool m_following_target = false;
};

#endif // SOLDIER_H