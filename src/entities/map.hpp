#ifndef MAP_HPP
#define MAP_HPP
#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#define RAYTMX_IMPLEMENTATION
#include "../../include/raytmx.h"

// Map component for tagging map entities and storing functions that operate on them
struct Map{
};

// Function to create and setup a map entity
void CreateMap(entt::registry &registry, std::string tmxFilePath, Music music);
    
// Function to update map state
void UpdateMap(entt::registry &registry, float dt);



#endif // MAP_HPP