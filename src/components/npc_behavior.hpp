#ifndef NPC_BEHAVIOR_HPP
#define NPC_BEHAVIOR_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../systems/systems.hpp"
#include "enemy_stats.hpp"
#include "physics_object.hpp"

typedef void (*NPCUpdateFunction)(entt::registry&, float, entt::entity);

struct NPC_behavior{
    NPCUpdateFunction Update;

    NPC_behavior(NPCUpdateFunction Update);
};

void NPCUpdate(entt::registry & registry, float dt, entt::entity npc);

#endif
