#ifndef CAMERA_VIEW_H
#define CAMERA_VIEW_H

#include <SFML/Graphics.hpp>

namespace nsm {

class CameraView
{
public:
    CameraView(float start_x, float start_y, int size_x, int size_y);

public:
    void mouseAtBorder(bool at_border);
    void zoom(int delta); // if delta = 1 (zoom in), if delta = -1 (zoom out), for MouseWheelScroll there is only 1 or -1
    void update(sf::Time delta_time);

    sf::View getView();

private:
    sf::View m_view;
    bool m_mouse_at_border;
    int m_scroll_count;

}; // class - CameraView

}; // namespace

#endif // CAMERA_VIEW_H