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

    // Takes in a pointer to an entt entity
    void CreatePlayer(entt::registry &registry, Camera2D camera);
    
    // Function to handle player movement
    void PlayerMovementSystem(entt::registry &registry, float dt, float gravity);
};



#endif