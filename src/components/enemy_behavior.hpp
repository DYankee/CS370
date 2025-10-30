#ifndef ENEMY_BEHAVIOR_HPP
#define ENEMY_BEHAVIOR_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"


typedef void (*UpdateFunction)(entt::registry&, float);

struct Enemy_behavior{
    UpdateFunction Update;

    Enemy_behavior(UpdateFunction Update);
};


#endif