#ifndef ENEMY_BEHAVIOR_HPP
#define ENEMY_BEHAVIOR_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../systems/systems.hpp"
#include "enemy_stats.hpp"
#include "physics_object.hpp"
#include "enemy_stats.hpp"

typedef void (*UpdateFunction)(entt::registry&, float, entt::entity);

struct Enemy_behavior{
    UpdateFunction Update;

    Enemy_behavior(UpdateFunction Update);
};

void TestUpdateFunc(entt::registry&, float, entt::entity);


void BasicEnemyUpdate(entt::registry & registry, float dt, entt::entity enemy);

#endif