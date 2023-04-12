#ifndef GAME_H
#define GAME_H

#include "../units/dark_legioner.h"
#include "camera_view.h"

#include <SFML/Graphics.hpp>

/*
    Game function, where logic of game will be written
    Like creating any scenario
*/
void game();

/*
    Whenever Mouse pointer is changing position:
    Used for camera view control
*/
void mouseMove(nsm::CameraView& view);

/*
    Whenever Mouse Wheel is being used:
    Scrolling up, zoom camera in
    Scrolling down, zoom camera out
*/
void mouseWheelScroll(int delta);

/*
    Whenever Mouse action is used:
    Like selecting unit, moving the unit, attacking, building and other
*/
void mouseClick(sf::RenderWindow& window, sf::Event& event, nsm::DarkLegioner& soldato);

#endif // GAME_H