#ifndef PLAYER_HEALTH_UPGRADE_COLLISION_HPP
#define PLAYER_HEALTH_UPGRADE_COLLISION_HPP

#include "../../include/entt.hpp"
#include "../components/health_pickup.hpp"

void PlayerHealthCollisionSystem(entt::registry &registry, float dt);

#endif
