#ifndef ENEMY_BEHAVIOR_HPP
#define ENEMY_BEHAVIOR_HPP

#include "../../include/raylib.h"
#include "enemy_stats.hpp"

typedef void (*UpdateFunction)(float, EnemyStats&, Transform&);

struct Enemy_behavior{
    UpdateFunction Update;

    Enemy_behavior(UpdateFunction Update);
};

void TestUpdateFunc(float, EnemyStats&, Transform&);

#endif