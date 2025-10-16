#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../../include/entt.hpp">
#include "../components/components.hpp"
#include "../systems/systems.hpp"

// Empty struct for entity tagging
struct Player{
};

// Function to create a player entity
// Takes in a pointer to an entt entity
void createPlayer(entt::registry &registry);

#endif