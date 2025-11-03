#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../../include/raytmx.h"
#include "../components/components.hpp"
#include "../entities/entities.hpp"

void CheckForMapChange(entt::registry &registry);
void ChangeMap(entt::registry &registry, std::string tmxFilePath); 

//find an object/group layer by name
TmxLayer* FindLayerByName(TmxLayer *layers, int layersLength, const char *name);

//find an object from a group by name
TmxObject FindObjectByName(TmxObject *objects, int objectsLength, const char *name);

//find a group of objects by type
std::vector<TmxObject> FindObjectsByType(TmxObject *objects, int objectsLength ,const char *type);

// Get the properties from a TmxObject
std::map<std::string, float> GetObjectProperties(TmxObject object);
#endif