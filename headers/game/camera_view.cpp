#include "camera_view.h"
#include "../constants_and_enums/constants.h"

nsm::CameraView::CameraView(float start_x, float start_y, int size_x, int size_y) {
    m_view.reset(sf::FloatRect(start_x, start_y, size_x, size_y));
    m_mouse_at_border = false;
    m_scroll_count = nsm::CameraViewOptions::ScrollLimitMax;
}

void nsm::CameraView::mouseAtBorder(bool at_border) {
    m_mouse_at_border = at_border;
}

void nsm::CameraView::zoom(int delta) {
    if (delta == 1) { // zoom in
        if (m_scroll_count > nsm::CameraViewOptions::ScrollLimitMin) {
            m_view.zoom(nsm::CameraViewOptions::ZoomInFactor);
            --m_scroll_count;
        }
    } else { // zoom out
        if (m_scroll_count < nsm::CameraViewOptions::ScrollLimitMax) {
            m_view.zoom(nsm::CameraViewOptions::ZoomOutFactor);
            ++m_scroll_count;
        }
    }
}

void nsm::CameraView::update(sf::Time delta_time) {
    if (m_mouse_at_border) {
        if (sf::Mouse::getPosition().y > sf::VideoMode::getDesktopMode().height - nsm::CameraViewOptions::BorderGap) {
            m_view.move(0, nsm::CameraViewOptions::MoveSpeed * delta_time.asMilliseconds());

        } else if (sf::Mouse::getPosition().x > sf::VideoMode::getDesktopMode().width - nsm::CameraViewOptions::BorderGap) {
            m_view.move(nsm::CameraViewOptions::MoveSpeed * delta_time.asMilliseconds(), 0);

        } else if (sf::Mouse::getPosition().y < nsm::CameraViewOptions::BorderGap ) {
            m_view.move(0, -(nsm::CameraViewOptions::MoveSpeed) * delta_time.asMilliseconds());

        } else if (sf::Mouse::getPosition().x < nsm::CameraViewOptions::BorderGap) {
            m_view.move(-(nsm::CameraViewOptions::MoveSpeed) * delta_time.asMilliseconds(), 0);
        }
    }
}

sf::View nsm::CameraView::getView() {
    return m_view;
}