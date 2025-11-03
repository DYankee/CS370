#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "../../include/entt.hpp"
#include "../../include/raytmx.h"
#include "../entities/entities.hpp"
#include "../components/components.hpp"
#include "systems.hpp"


// Check for collisions between player and spike objects
void SpikeCollision(entt::registry &registry, float dt);

// Check for collisions between player and tile layers
void MoveEntity(entt::registry &registry, float dt, entt::entity);

#endif // COLLISION_SYSTEM_HPP