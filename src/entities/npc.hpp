#ifndef NPC_HPP
#define NPC_HPP

#include "../components/components.hpp"
#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../../include/raytmx.h"


// Create empty struct
struct NPC{};


void CreatePig(entt::registry &registry, TmxObject npcInfo);
void CreateHatPig(entt::registry &registry, TmxObject npcInfo);
void CreateChicken(entt::registry &registry, TmxObject npcInfo);
void CreateSheep(entt::registry &registry, TmxObject npcInfo);
void CreateChick(entt::registry &registry, TmxObject npcInfo);


#endif
