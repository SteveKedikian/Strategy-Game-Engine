#ifndef UNIT_H
#define UNIT_H

#include "../enum_classes.h"
#include "../world_map/maps.h"

#include <SFML/Graphics.hpp>
#include <string>

class Unit
{
public:
    Unit() = default;
    virtual ~Unit() = default;
public:
    void select(const bool select) {m_selected = select;} // Set status 'm_selected' to given function argument
    void takeDamage(const float damage) {m_hp -= damage;}
    const bool isSelected() const {return m_selected;} // Return 'm_selected' value, shows if Unit was selected or not
    const bool isAlive() const {return m_alive;}
    const sf::Sprite& getSprite() const {return m_sprite;}
public:
    virtual void update(const sf::Time& delta_time) = 0; // Update Unit's atributes, by given time and statuses that were changed before update.
    virtual const bool onUnit(const sf::Vector2f& mouse_position) const = 0;
    virtual const sf::Vector2f getStandingPosition() const = 0;
protected:
// STATS
    Control m_controller;
    std::string m_name;
    Faction m_faction;
    Map* m_map;
    float m_hp;
    float m_collision_radius;
    int m_price;
// STATUSES
    bool m_selected = false;
    bool m_alive = true;
// TEXTURE AND SPRITE
    sf::Texture m_texture;
    sf::Sprite m_sprite;
}; // Unit

#endif // UNIT_H