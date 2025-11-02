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
            {"cowL", "assets/sprites/cowL.png"},
            {"cowRWalk", "assets/sprites/cowRWalk.png"},
            {"cowLWalk", "assets/sprites/cowLWalk.png"},
            {"cowRJump", "assets/sprites/cowRJump.png"},
            {"cowLJump", "assets/sprites/cowLJump.png"}

        }),
        WHITE
    );
    cowSprite.SetTexture("cowR");
    // Add SpriteData component to the entity
    registry.emplace<SpriteData>(playerEnt, cowSprite);

    // Create Animation component
    Animation playerAnimation;
    
    // Sprite sheet dimensions for walking
    int frameWidth = 16;
    int frameHeight = 16;
    int totalFrames = 4;  
    
    // Create walk right animation sequence (4 frames)
    std::vector<AnimationFrame> walkRightFrames;
    for (int i = 0; i < totalFrames; i++) {
        walkRightFrames.push_back(AnimationFrame{
            Rectangle{(float)(i * frameWidth), 0, (float)frameWidth, (float)frameHeight},
            0.1f  // 0.1 seconds per frame
        });
    }
    playerAnimation.AddSequence("walkRight", AnimationSequence(walkRightFrames, true));
    
    // Create walk left animation sequence (4 frames)
    std::vector<AnimationFrame> walkLeftFrames;
    for (int i = 0; i < totalFrames; i++) {
        walkLeftFrames.push_back(AnimationFrame{
            Rectangle{(float)(i * frameWidth), 0, (float)frameWidth, (float)frameHeight},
            0.1f  // 0.1 seconds per frame
        });
    }
    playerAnimation.AddSequence("walkLeft", AnimationSequence(walkLeftFrames, true));
    
    // Create idle animations (single frame - first frame of each animation)
    playerAnimation.AddSequence("idleRight", AnimationSequence({
        AnimationFrame{Rectangle{0, 0, (float)frameWidth, (float)frameHeight}, 1.0f}
    }, true));
    playerAnimation.AddSequence("idleLeft", AnimationSequence({
        AnimationFrame{Rectangle{0, 0, (float)frameWidth, (float)frameHeight}, 1.0f}
    }, true));
    
    // Sprite sheet dimensions for jumping
    int jumpFrameWidth = 16;
    int jumpFrameHeight = 16;
    int jumpTotalFrames = 13;
    
    // Create jump right animation sequence (13 frames)
    std::vector<AnimationFrame> jumpRightFrames;
    for (int i = 0; i < jumpTotalFrames; i++) {
        jumpRightFrames.push_back(AnimationFrame{
            Rectangle{(float)(i * jumpFrameWidth), 0, (float)jumpFrameWidth, (float)jumpFrameHeight},
            0.1f  // 0.1 seconds per frame
        });
    }
    playerAnimation.AddSequence("jumpRight", AnimationSequence(jumpRightFrames, false));
    
    // Create jump left animation sequence (13 frames)
    std::vector<AnimationFrame> jumpLeftFrames;
    for (int i = 0; i < jumpTotalFrames; i++) {
        jumpLeftFrames.push_back(AnimationFrame{
            Rectangle{(float)(i * jumpFrameWidth), 0, (float)jumpFrameWidth, (float)jumpFrameHeight},
            0.1f  // 0.1 seconds per frame
        });
    }
    playerAnimation.AddSequence("jumpLeft", AnimationSequence(jumpLeftFrames, false));
    
    // Add Animation component to the entity
    registry.emplace<Animation>(playerEnt, playerAnimation);

    // Add Transform component to the entity
    registry.view<Map, TmxMap>().each([&registry, &playerEnt](TmxMap &map){
        TmxObjectGroup entities = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;
        TmxObject player = FindObjectByName(entities.objects, entities.objectsLength, "Player");


        Transform playerTransform = Transform{ {(float)player.x, (float)player.y, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {CHAR_WIDTH, CHAR_HEIGHT} };

        registry.emplace<Transform>(playerEnt, playerTransform);
    });

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    physics.velocity = {0.0f, 0.0f}; // Ensure velocity starts at zero
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