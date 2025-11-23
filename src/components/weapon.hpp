#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../../include/raylib.h"
#include "../../include/entt.hpp"
#include "sprite_data.hpp"

struct Weapon {
    Vector3 offset;
    SpriteData sprite;

    Weapon(Vector3, SpriteData);
};


#endif
