#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../../include/raytmx.h"
#include "../components/components.hpp"
#include "../entities/entities.hpp"

void CheckForMapChange(entt::registry &registry);
void ChangeMap(entt::registry &registry, std::string tmxFilePath, Vector2 startPosition); 

#endif