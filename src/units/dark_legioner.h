#ifndef DARK_LEGIONER_H
#define DARK_LEGIONER_H

#include "soldier.h"

class DarkLegioner : public Soldier
{
public:
    DarkLegioner() = default;
    DarkLegioner(const sf::Vector2f start, Map* const map, Control controller);
    ~DarkLegioner() = default;
}; // DarkLegioner

#endif // DARK_LEGIONER_H_