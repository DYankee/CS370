#ifndef PLAYER_MOVMENT_HPP
#define PLAYER_MOVMENT_HPP
#include "../../include/entt.hpp"
#include "../entities/entities.hpp"

extern "C" {
    #define RAYTMX_IMPLEMENTATION
    #include "../../include/raytmx.h"
}

void PlayerMovementSystem(entt::registry &registry, float dt);

#endif