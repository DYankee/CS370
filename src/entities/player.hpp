#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../../include/entt.hpp">
#include "../components/components.hpp"
#include "../systems/systems.hpp"

#define CHAR_WIDTH 32
#define CHAR_HEIGHT 32
#define SPEED 400.0f
#define JUMP_STRENGTH -700.0f    // Negative because y-axis goes down


// Empty struct for entity tagging
struct Player{
};

// Function to create a player entity
// Takes in a pointer to an entt entity
void createPlayer(entt::registry &registry, Camera2D camera);

void playerMovementSystem(entt::registry &registry, float dt, float gravity);

#endif