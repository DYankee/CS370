#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../components/components.hpp"
#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../../include/raytmx.h"


// Create empty struct
struct Enemy{};


void CreateFarmer(entt::registry &registry, TmxObject enemyInfo);
void CreateAlien(entt::registry &registry, TmxObject enemyInfo);





#endif