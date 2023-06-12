#ifndef ENUM_CLASSES_H
#define ENUM_CLASSES_H

// Will be used to set or get Unit's watching direction
enum class Direction {
    Left,
    Right,
    Up,
    Down
};

enum class Control {
    Player,
    AIBot
};

enum class Faction {
    Armenia,
    Persia
};

enum class HumanType {
    ArmSwordman,
    ArmSpearman,
    ArmArcher,
    ArmCavalry,
    ArmCivilian,
    ArmElite,
    PersSwordman,
    PersSpearman,
    PersArcher,
    PersCavalry,
    PersCivilian,
    PersElite
};

#endif // ENUM_CLASSES_H