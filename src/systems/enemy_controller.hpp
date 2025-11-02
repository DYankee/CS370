#ifndef ENEMY_CONTROLLER_HPP
#define ENEMY_CONTROLLER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../../include/raytmx.h"
#include "../components/components.hpp"
#include "../entities/entities.hpp"
#include "systems.hpp"

void SpawnEnemies(entt::registry &registry);

void DeSpawnEnemies(entt::registry &registry);

void UpdateEnemies(entt::registry &registry, float dt);

#endif
