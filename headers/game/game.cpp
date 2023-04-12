#include "game.h"
#include "auxiliary_functions.h"
#include "../maps/maps.h"
#include "../constants_and_enums/constants.h"

#include <cmath>
#include <iostream>

//     // get the current mouse position in the window
// sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

// // convert it to world coordinates
// sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

void mouseMove(nsm::CameraView& view) {
    // sf::VideoMode::getDesktopMode() will work for every Computer Screen, if fullscreen is used !
    if (sf::Mouse::getPosition().y > sf::VideoMode::getDesktopMode().height - nsm::CameraViewOptions::BorderGap ||
        sf::Mouse::getPosition().x > sf::VideoMode::getDesktopMode().width - nsm::CameraViewOptions::BorderGap ||
        sf::Mouse::getPosition().y < nsm::CameraViewOptions::BorderGap ||
        sf::Mouse::getPosition().x < nsm::CameraViewOptions::BorderGap)
    {
        view.mouseAtBorder(true);
    } else {
        view.mouseAtBorder(false);
    }
}

void mouseWheelScroll(nsm::CameraView& view, int delta) {
    view.zoom(delta);
}

void mouseClick(sf::RenderWindow& window, sf::Event& event, nsm::DarkLegioner& soldato) {
    // mouse position in whole map
    sf::Vector2f mouse_world_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // If Left Mouse Button is clicked, at the moment there can be 3 type of actions:
    // 1. Unit is selected (if clicked on unit)
    // 2. Unit is deselected (if unit was selected and if clicked anywhere except the unit)
    // 3. Does nothing at all (if not clicked on unit)
    if (event.mouseButton.button == sf::Mouse::Left) {
        if ((soldato.getSprite().getPosition().x < mouse_world_position.x && mouse_world_position.x < soldato.getSprite().getPosition().x + 41) && // <---- MAGIC
            (soldato.getSprite().getPosition().y < mouse_world_position.y && mouse_world_position.y < soldato.getSprite().getPosition().y + 62))   // <---- MAGIC
        {
            soldato.select(true);
        } else {
            soldato.select(false);
        }
    }
    // If Right Mouse Button is clicked, at the moment there can be 1 type of actions:
    // 1. Unit is starting to move to the clicked direction and position
    else if (event.mouseButton.button == sf::Mouse::Right && soldato.isSelected()) {
        soldato.setMoveToCoordinates(mouse_world_position.x, mouse_world_position.y); // Remember last Mouse Right click coordinates for Unit

        // distance between (x1, y1) and (x2, y2)
        // distance = square_root(delta_x^2 + delta_y^2)
        // count delta_y = y1 - y2 (The reason that we did y2 - y1, because we need that information for choosing Unit's watching direction)
        float delta_x = mouse_world_position.x - soldato.getSprite().getPosition().x - soldato.getSprite().getTextureRect().width / 2; 
        float delta_y = soldato.getSprite().getPosition().y - mouse_world_position.y + soldato.getSprite().getTextureRect().height;
        float distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

        // The distance we calculated, is showing diagonal from Unit to Mouse click coordinates
        // By using (delta_x / distance) * Unit_Speed, we count X coordinate raising rate, so we can start moving our Unit diagonaly
        // Same logic for delta_y but with minus, because of change we did before (y2 - y1)
        soldato.setDiagonalSpeedCoordinates((delta_x / distance) * soldato.getSpeed(),
                                            (-delta_y / distance) * soldato.getSpeed());
                                            
        soldato.setWatchingDirection(mouseRightClickDirectionFromObject(delta_x, delta_y));
        soldato.move();
    }
}

void game() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "RTS_GAME", sf::Style::Fullscreen);
    nsm::Avarayr map;

    sf::Mouse::setPosition(sf::Vector2i(0, 0));
    
    // sf::RenderWindow window(sf::VideoMode(1024, 683), "RTS_GAME");
    // sf::Texture background_texture;
    // background_texture.loadFromFile("../graphics/background/background_forest.jpg");
    // sf::Sprite background_sprite;
    // background_sprite.setTexture(background_texture);
    // background_sprite.setPosition(0, 0);

    // THIS MUST STAY, TO CHOOSE GOOD CUTTING FRAME
    // sf::RectangleShape rectangle;
    // rectangle.setPosition(300.0f, 300.0f);
    // rectangle.setSize(sf::Vector2f (36, 58));
    // rectangle.setFillColor(sf::Color::White);

    nsm::DarkLegioner soldato(50.0f, 50.0f);
    nsm::DarkLegioner zinvor(300.0f, 300.0f);

    nsm::CameraView camera_view(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

    sf::Clock clock;
    sf::Time delta_time;

    sf::Mouse::setPosition(sf::Vector2i(500, 500)); // This option is needed, because at the start, mouse is always at (0, 0)
                                                    // Which will cause window to move up automatically

    while (window.isOpen())
    {   
        delta_time = clock.restart();

        // If player clicked ESCAPE button, window will be closed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        sf::Event event;
        while (window.pollEvent(event)) {   
            // If player clicked X button on window, to close it 
            // As the game probably will be only fullscreen, this option may be removed
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseMoved) {
                mouseMove(camera_view);
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                mouseWheelScroll(camera_view, event.mouseWheelScroll.delta);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                mouseClick(window, event, soldato);
                mouseClick(window, event, zinvor);
            }
        }

        soldato.update(delta_time);
        zinvor.update(delta_time);
        camera_view.update(delta_time);

        window.clear();
        // window.draw(background_sprite);
        map.draw(window);
        // window.draw(rectangle); THIS HELPS TO FIND CORRECT SIZES
        window.draw(soldato.getSprite());
        window.draw(zinvor.getSprite());
        window.setView(camera_view.getView());
        window.display();
    }
}