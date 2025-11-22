#ifndef ENEMY_CONTROLLER_HPP
#define ENEMY_CONTROLLER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../../include/raytmx.h"
#include "../entities/enemy.hpp"
#include "../components/components.hpp"
#include "systems.hpp"

enum EnemyType {NONE, FARMER, ALIEN};

void SpawnEnemies(entt::registry &registry);

void DeSpawnEnemies(entt::registry &registry);

void UpdateEnemies(entt::registry &registry, float dt);

EnemyType GetEnemyType(TmxObject obj);

#endif
