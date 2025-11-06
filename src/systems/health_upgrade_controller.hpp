#ifndef HEALTH_UPGRADE_CONTROLLER_HPP
#define HEALTH_UPGRADE_CONTROLLER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../components/components.hpp"
#include "../components/health_pickup.hpp"


void SpawnHealthUpgrades(entt::registry &registry);
void UpdateHealthUpgrades(entt::registry &registry, float dt);

#endif
