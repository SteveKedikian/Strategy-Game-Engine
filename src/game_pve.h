#ifndef GAME_PVE_H
#define GAME_PVE_H

#include "enum_classes.h"
#include "world_map/maps.h"
#include "units/dark_legioner.h"

// Here is written a scenario, where player is playing against enviroment (PVE)
// That can be a game versus AI bot or some history scenario
class GamePVE {
public:
    GamePVE();
    ~GamePVE() = default;
public:
    void startGame(); // A game scenario start for PVE type game
private:
    // Main Game Logic
    void events();
    void updates(const sf::Time& delta_time);
    void display();
private:
    void mouseMove();
    void mouseWheelScroll(int delta);
    void mouseClick(const sf::Event& event);
    void mouseLeftClick(const sf::Vector2f& mouse_position);
    void mouseRightClick(const sf::Vector2f& mouse_position);
    void viewUpdate(const sf::Time& delta_time);
    void checkUnits(const sf::Time& delta_time);
    void checkSoldiers();
    void checkForDeaths();
private:
// CONSTANTS
    const float VIEW_START_X = 0.0f;
    const float VIEW_START_Y = 0.0f;
    const int VIEW_BORDER_GAP = 50;
    const int VIEW_SCROLL_LIMIT_MAX = 10;
    const int VIEW_SCROLL_LIMIT_MIN = 0;
    const float VIEW_MOVE_SPEED = 0.5f;
    const float VIEW_ZOOM_IN_FACTOR = 0.8f;
    const float VIEW_ZOOM_OUT_FACTOR = 1.25f;
    const float CHECK_UNITS_REFRESH_TIMER_LIMIT = 1.5f;
private:
// WINDOW
    sf::RenderWindow m_window;
// VIEW
    sf::View m_view;
    int m_border_gap;
    int m_scroll_limit_max;
    int m_scroll_limit_min;
    float m_move_speed;
    float m_zoom_in_factor;
    float m_zoom_out_factor;
    bool m_mouse_at_border;
    int m_scroll_count;
// MAP
    Map m_map;
// ARMY
    std::vector<Soldier*> m_player_army;
    std::vector<Soldier*> m_enemy_army;
// EVENTS
    bool m_unit_selected = false;
// TIMERS
    float m_check_units_refresh_timer = 0.0f;
}; // GamePVE

#endif // GAME_PVE_H