#include "player.hpp"

// Player struct constructor
Player::Player(){};

// Function to create the player entity
void createPlayer(entt::registry &registry) {

    // Add Player entity to the registry
    entt::entity playerEnt = registry.create();

    // Add Player component to the entity
    Player playerComponent;
    registry.emplace<Player>(playerEnt, playerComponent);

    // Load player sprites
    SpriteData cowSprite = SpriteData(loadTextures({
        {"cowR", "assets/sprites/cowR.png"},
        {"cowL", "assets/sprites/cowL.png"}
    }));
    cowSprite.setTexture("cowR");

    // Add SpriteData component to the entity
    registry.emplace<SpriteData>(playerEnt, cowSprite);

    
    // Add the rest of the components needed for the player here
};