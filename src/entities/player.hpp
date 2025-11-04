#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../components/components.hpp"
#include "../systems/systems.hpp"

#define CHAR_WIDTH 32
#define CHAR_HEIGHT 32
#define MAX_HEALTH 3
#define SPEED 400.0f             // player move speed
#define JUMP_STRENGTH -600.0f   // Negative because y-axis goes down
#define GRAVITY 2000.0f          // Gravity strength 
#define MAX_IFRAMES 1.0f         // Max i-frames duration in seconds

// Empty struct for entity tagging
struct Player{
};

// Takes in a pointer to an entt entity
void CreatePlayer(entt::registry &registry);

#endif