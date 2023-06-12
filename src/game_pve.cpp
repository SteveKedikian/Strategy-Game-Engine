#include "game_pve.h"

#include <iostream>

GamePVE::GamePVE() 
    : m_window(sf::VideoMode::getDesktopMode(), "RTS_GAME", sf::Style::Fullscreen)
    , m_map("map_name")
{
    m_view.reset(sf::FloatRect(VIEW_START_X, VIEW_START_Y, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
    m_mouse_at_border = false;
    m_scroll_count = VIEW_SCROLL_LIMIT_MAX;
    m_border_gap = VIEW_BORDER_GAP;
    m_scroll_limit_max = VIEW_SCROLL_LIMIT_MAX;
    m_scroll_limit_min = VIEW_SCROLL_LIMIT_MIN;
    m_move_speed = VIEW_MOVE_SPEED;
    m_zoom_in_factor = VIEW_ZOOM_IN_FACTOR;
    m_zoom_out_factor = VIEW_ZOOM_OUT_FACTOR;
    m_map.mapMaker();
}

void GamePVE::events() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseMoved:
                mouseMove();
                break;
            case sf::Event::MouseWheelScrolled:
                mouseWheelScroll(event.mouseWheelScroll.delta);
                break;
            case sf::Event::MouseButtonPressed:
                mouseClick(event);
                break;
        }
    }
}

void GamePVE::updates(const sf::Time& delta_time) {
    viewUpdate(delta_time);
    checkUnits(delta_time);
    checkForDeaths();

    for (int i = 0; i < m_player_army.size(); ++i) {
        m_player_army[i]->update(delta_time);
    }

    for (int i = 0; i < m_enemy_army.size(); ++i) {
        m_enemy_army[i]->update(delta_time);
    }
}

void GamePVE::display() {
    m_window.clear();
    m_map.draw(m_window);

    for (int i = 0; i < m_player_army.size(); ++i) {
        m_window.draw(m_player_army[i]->getSprite());
    }

    for (int i = 0; i < m_enemy_army.size(); ++i) {
        m_window.draw(m_enemy_army[i]->getSprite());
    }

    m_window.setView(m_view);
    m_window.display();
}

void GamePVE::mouseMove() {
    if (sf::Mouse::getPosition().y > sf::VideoMode::getDesktopMode().height - m_border_gap ||
        sf::Mouse::getPosition().x > sf::VideoMode::getDesktopMode().width - m_border_gap ||
        sf::Mouse::getPosition().y < m_border_gap ||
        sf::Mouse::getPosition().x < m_border_gap)
    {
        m_mouse_at_border = true;
    } else {
        m_mouse_at_border = false;
    }
}

void GamePVE::mouseWheelScroll(int delta) {
    if (delta == 1) { // zoom in
        if (m_scroll_count > m_scroll_limit_min) {
            m_view.zoom(m_zoom_in_factor);
            --m_scroll_count;
        }
    } else { // zoom out
        if (m_scroll_count < m_scroll_limit_max) {
            m_view.zoom(m_zoom_out_factor);
            ++m_scroll_count;
        }
    }
}

void GamePVE::mouseClick(const sf::Event& event) {
    sf::Vector2f mouse_world_position = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
    if (event.mouseButton.button == sf::Mouse::Left) {
        mouseLeftClick(mouse_world_position);
    } else if (event.mouseButton.button == sf::Mouse::Right) {
        mouseRightClick(mouse_world_position);
    }
}

void GamePVE::mouseLeftClick(const sf::Vector2f& mouse_position) {
    for (int i = 0; i < m_player_army.size(); ++i) {
        if (m_player_army[i]->onUnit(mouse_position)) {
            m_player_army[i]->select(true);
            m_unit_selected = true;
        } else {
            m_player_army[i]->select(false);
        }
    }

    for (int i = 0; i < m_enemy_army.size(); ++i) {
        if (m_enemy_army[i]->onUnit(mouse_position)) {
            m_enemy_army[i]->select(true);
        } else {
            m_enemy_army[i]->select(false);
        }
    }
}

void GamePVE::mouseRightClick(const sf::Vector2f& mouse_position) {
    if (!m_unit_selected) {
        return;
    }

    for (int i = 0; i < m_enemy_army.size(); ++i) {
        if (m_enemy_army[i]->onUnit(mouse_position)) {
            for (int j = 0; j < m_player_army.size(); ++j) {
                if (m_player_army[j]->isSelected()) {
                    m_player_army[j]->moveClear();
                    m_player_army[j]->attackClear();
                    m_player_army[j]->attack(m_enemy_army[i]);
                    m_enemy_army[0]->move(sf::Vector2f(200.0f, 200.0f));
                }
            }
            return;
        }
    }

    for (int i = 0; i < m_player_army.size(); ++i) {
        if (m_player_army[i]->isSelected()) {
            m_player_army[i]->moveClear();
            m_player_army[i]->attackClear();
            m_player_army[i]->move(mouse_position);
        }
    }   
}

void GamePVE::viewUpdate(const sf::Time& delta_time) {
    if (m_mouse_at_border) {
        if (sf::Mouse::getPosition().y > sf::VideoMode::getDesktopMode().height - m_border_gap) {
            m_view.move(0, m_move_speed * delta_time.asMilliseconds());

        } else if (sf::Mouse::getPosition().x > sf::VideoMode::getDesktopMode().width - m_border_gap) {
            m_view.move(m_move_speed * delta_time.asMilliseconds(), 0);

        } else if (sf::Mouse::getPosition().y < m_border_gap) {
            m_view.move(0, -(m_move_speed) * delta_time.asMilliseconds());

        } else if (sf::Mouse::getPosition().x < m_border_gap) {
            m_view.move(-(m_move_speed) * delta_time.asMilliseconds(), 0);
        }
    }
}

void GamePVE::checkUnits(const sf::Time& delta_time) {
    if (m_check_units_refresh_timer > CHECK_UNITS_REFRESH_TIMER_LIMIT) {
        checkSoldiers();
        m_check_units_refresh_timer = 0.0f;
    } else {
        m_check_units_refresh_timer += delta_time.asSeconds();
    }
}

void GamePVE::checkSoldiers() {
    for (int i = 0; i < m_player_army.size(); ++i) {
        for (int j = 0; j < m_enemy_army.size(); ++j) {
            if (!m_player_army[i]->isActive()) {
                if ((abs(m_player_army[i]->getStandingPosition().x - m_enemy_army[j]->getStandingPosition().x) <= m_player_army[i]->aggressionTriggerRadius()) &&
                    (abs(m_player_army[i]->getStandingPosition().y - m_enemy_army[j]->getStandingPosition().y) <= m_player_army[i]->aggressionTriggerRadius())) 
                {
                    m_player_army[i]->attack(m_enemy_army[j]);
                }
            }

            if (!m_enemy_army[j]->isActive()) {
                if ((abs(m_enemy_army[j]->getStandingPosition().x - m_player_army[i]->getStandingPosition().x) <= m_enemy_army[j]->aggressionTriggerRadius()) &&
                    (abs(m_enemy_army[j]->getStandingPosition().y - m_player_army[i]->getStandingPosition().y) <= m_enemy_army[j]->aggressionTriggerRadius())) 
                {
                    m_enemy_army[j]->attack(m_player_army[i]);
                }
            }
        }
    }
}

void GamePVE::checkForDeaths() {
    for (int i = 0; i < m_player_army.size(); ++i) {
        if (!m_player_army[i]->isAlive()) {
            delete m_player_army[i];
            // m_player_army[i] = nullptr;
            m_player_army.erase(m_player_army.begin() + i);
        }
    }
    
    for (int i = 0; i < m_enemy_army.size(); ++i) {
        if (!m_enemy_army[i]->isAlive()) {
            delete m_enemy_army[i];
            // m_enemy_army[i] = nullptr;
            m_enemy_army.erase(m_enemy_army.begin() + i);
        }
    }
}

void GamePVE::startGame() {
    m_player_army.push_back(new DarkLegioner(sf::Vector2f(50.0f, 50.0f), &m_map, Control::Player));
    m_player_army.push_back(new DarkLegioner(sf::Vector2f(55.0f, 80.0f), &m_map, Control::Player));
    m_enemy_army.push_back(new DarkLegioner(sf::Vector2f(200.0f, 20.0f), &m_map, Control::AIBot));
    m_enemy_army.push_back(new DarkLegioner(sf::Vector2f(250.0f, 20.0f), &m_map, Control::AIBot));

    // sf::Clock clock;
    // sf::Time delta_time;
    // while (m_window.isOpen())
    // {
    //     // If player clicked ESCAPE button, window will be closed
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    //         m_window.close();
    //     }
    //     events();

    //     delta_time = clock.restart();
    //     updates(delta_time);

    //     display();
    // }

    sf::Clock clock;
    sf::Time time_per_frame = sf::seconds(1.f / 120.f);
    sf::Time time_since_last_update = sf::Time::Zero;
    while (m_window.isOpen()) {
        sf::Time elapsed_time = clock.restart();
        time_since_last_update += elapsed_time;

        bool repaint = false;

        // If player clicked ESCAPE button, window will be closed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }

        events();

        while (time_since_last_update >= time_per_frame) {
            time_since_last_update -= time_per_frame;
            repaint = true;
            updates(time_per_frame);
        }
        // updates(elapsed_time); // Minimal time step

        if (repaint) {
            display();
        }
    }
}
