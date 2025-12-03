#ifndef UPGRADE_CONTROLLER_HPP
#define UPGRADE_CONTROLLER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../components/components.hpp"
#include "../components/health_pickup.hpp"


void SpawnUpgrades(entt::registry &registry);
void UpdateUpgrades(entt::registry &registry, float dt);
void DespawnUpgrades(entt::registry &registry);

#endif
