#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../components/components.hpp"
#include "../systems/systems.hpp"

// Create empty struct
struct Enemy{};

void CreateEnemy(entt::registry &registry, Vector2 spawnPoint);



#endif