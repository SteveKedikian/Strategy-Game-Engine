#ifndef CONSTANTS_H
#define CONTSTANTS_H

namespace nsm {

struct CameraViewOptions {
    static const int BorderGap = 50;
    static const int ScrollLimitMax = 10;
    static const int ScrollLimitMin = 0;
    static constexpr float MoveSpeed = 0.5f;
    static constexpr float ZoomInFactor = 0.8f;
    static constexpr float ZoomOutFactor = 1.25f;

}; // struct - CameraViewOptions

}; // namespace - nsm

#endif // CONSTANTS_H