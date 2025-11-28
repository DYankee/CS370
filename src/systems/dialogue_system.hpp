#ifndef DIALOGUE_SYSTEM_HPP
#define DIALOGUE_SYSTEM_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../components/components.hpp"
#include "../entities/entities.hpp"

void UpdateDialogue(entt::registry &registry, float dt);
void DrawDialogue(entt::registry &registry);

#endif
