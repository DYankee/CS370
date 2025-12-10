#ifndef RANGE_UPGRADE_CONTROLLER_HPP
#define RANGE_UPGRADE_CONTROLLER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../components/components.hpp"
#include "../components/range_pickup.hpp"


void SpawnRangeUpgrades(entt::registry &registry);
void DeSpawnRangeUpgrades(entt::registry &registry);
void UpdateRangeUpgrades(entt::registry &registry, float dt);

#endif
