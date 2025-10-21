#include "player.hpp"



// Function to create the player entity
void CreatePlayer(entt::registry &registry) {
    TraceLog(LOG_TRACE, "Entering Function: CreatePlayer");
    TraceLog(LOG_INFO, "Creating Player Entity");
    
    // Add Player entity to the registry
    entt::entity playerEnt = registry.create();

    // Add Player component to the entity
    Player playerComponent;
    registry.emplace<Player>(playerEnt, playerComponent);


    // Load player sprites
    SpriteData cowSprite = SpriteData(LoadTextures({
            {"cowR", "assets/sprites/cowR.png"},
            {"cowL", "assets/sprites/cowL.png"}}),
        WHITE
    );
    cowSprite.SetTexture("cowR");
    // Add SpriteData component to the entity
    registry.emplace<SpriteData>(playerEnt, cowSprite);

    // Add Transform component to the entity
    Transform playerTransform = Transform{ {400.0f, 300.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {CHAR_WIDTH, CHAR_HEIGHT} };
    registry.emplace<Transform>(playerEnt, playerTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(playerEnt, physics);

    // Add PlayerStats component to the entity
    PlayerStats stats = PlayerStats(MAX_HEALTH, MAX_IFRAMES, SPEED, JUMP_STRENGTH, GRAVITY);
    registry.emplace<PlayerStats>(playerEnt, stats);

    // Add the rest of the components needed for the player here
};