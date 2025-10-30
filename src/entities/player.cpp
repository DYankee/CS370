#include "player.hpp"
#include "../components/player_hud.hpp"
#include "../include/raylib.h"

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
            {"cowL", "assets/sprites/cowL.png"}
        }),
        WHITE
    );
    cowSprite.SetTexture("cowR");
    // Add SpriteData component to the entity
    registry.emplace<SpriteData>(playerEnt, cowSprite);

    // Add Transform component to the entity
    Transform playerTransform = Transform{ {100.0f, 100.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {CHAR_WIDTH, CHAR_HEIGHT} };
    registry.emplace<Transform>(playerEnt, playerTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(playerEnt, physics);

    // Load jump sound
    Sound jumpSound = LoadSound("assets/audio/jumpMoo.mp3");

    // Add PlayerStats component to the entity
    PlayerStats stats = PlayerStats(MAX_HEALTH, MAX_IFRAMES, SPEED, JUMP_STRENGTH, GRAVITY, jumpSound);
    registry.emplace<PlayerStats>(playerEnt, stats);

    // Create hud
    {
        Texture2D heartTex = LoadTexture("assets/sprites/CowFace.png");
        entt::entity hudEnt = registry.create();
        registry.emplace<HUDResources>(hudEnt, HUDResources{ heartTex, Vector2{20.0f, 20.0f}, 48, playerEnt });
    }

  // Add the rest of the components needed for the player here
};