#ifndef NPC_CONTROLLER_HPP
#define NPC_CONTROLLER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../../include/raytmx.h"
#include "../components/components.hpp"
#include "../entities/entities.hpp"
#include "systems.hpp"

void SpawnNPCs(entt::registry &registry);

void DeSpawnNPCs(entt::registry &registry);

void UpdateNPCs(entt::registry &registry, float dt);

#endif
