#ifndef PLAYER_MOVEMENT_HPP
#define PLAYER_MOVEMENT_HPP
#include "../../include/entt.hpp"
#include "../../include/raytmx.h"
#include "../entities/entities.hpp"

void PlayerMovementSystem(entt::registry &registry, float dt);

#endif