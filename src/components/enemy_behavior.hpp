#ifndef ENEMY_BEHAVIOR_HPP
#define ENEMY_BEHAVIOR_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "enemy_stats.hpp"

typedef void (*UpdateFunction)(entt::registry&, float, EnemyStats&, Transform&);
struct Enemy_behavior{
    UpdateFunction Update;

    Enemy_behavior(UpdateFunction Update);
};

void TestUpdateFunc(entt::registry&, float, EnemyStats&, Transform&);

#endif