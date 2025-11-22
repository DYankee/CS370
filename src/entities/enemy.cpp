#include "enemy.hpp"
#include "../include/raylib.h"

void CreateFarmer(entt::registry &registry, TmxObject enemyInfo) {
    TraceLog(LOG_TRACE, "Entering Function: CreateEnemy");
    TraceLog(LOG_INFO, "Creating Enemy Entity");
    
    // Add entity to the registry
    entt::entity enemyEnt = registry.create();

    // Add Enemy component to the entity
    Enemy enemyComponent;
    registry.emplace<Enemy>(enemyEnt, enemyComponent);

    // Add Transform component to the entity
    Transform enemyTransform = Transform{ {float(enemyInfo.x), float(enemyInfo.y), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32} };
    registry.emplace<Transform>(enemyEnt, enemyTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(enemyEnt, physics);

    // Add Vector2 to mark where the enemy spawned from
    registry.emplace<Vector2>(enemyEnt, Vector2{float(enemyInfo.x), float(enemyInfo.y)});

    // Add stats to enemy
    std::map<std::string, float> statsMap = GetObjectProperties(enemyInfo);
    float health = statsMap["Health"];
    float dmg = statsMap["DMG"];
    float moveSpeed = statsMap["MoveSpeed"];
    float AttackCoolDown = statsMap["AttackCoolDown"];
    Direction direction = LEFT;
    if (statsMap["Direction"] > 0){
        direction = RIGHT;
    }
    EnemyStats stats = EnemyStats(health, moveSpeed, dmg, AttackCoolDown, direction, false);
    registry.emplace<EnemyStats>(enemyEnt, stats);
    
    // Add sprites
    SpriteData farmerSprite = SpriteData(LoadTextures({
        {"FarmerR", "assets/sprites/enemies/farmer/FarmerR.png"},
        {"FarmerL", "assets/sprites/enemies/farmer/FarmerL.png"},
    }),
    WHITE
    );    
    switch (direction){
        case LEFT: {
            farmerSprite.SetTexture("FarmerL");
            break;
        }
        case RIGHT: {
            farmerSprite.SetTexture("FarmerR");
            break;
        }
    }
    farmerSprite.SetTexture("FarmerR");
    registry.emplace<SpriteData>(enemyEnt, farmerSprite);


    // Add update function
    Enemy_behavior behavior = BasicEnemyUpdate;
    registry.emplace<Enemy_behavior>(enemyEnt, behavior);

    // Add the rest of the enemy components here
};

void CreateAlien(entt::registry &registry, TmxObject enemyInfo) {
    TraceLog(LOG_TRACE, "Entering Function: CreateEnemy");
    TraceLog(LOG_INFO, "Creating Enemy Entity");
    
    // Add entity to the registry
    entt::entity enemyEnt = registry.create();

    // Add Enemy component to the entity
    Enemy enemyComponent;
    registry.emplace<Enemy>(enemyEnt, enemyComponent);



    // Add Transform component to the entity
    Transform enemyTransform = Transform{ {float(enemyInfo.x), float(enemyInfo.y), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32} };
    registry.emplace<Transform>(enemyEnt, enemyTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(enemyEnt, physics);

    // Add Vector2 to mark where the enemy spawned from
    registry.emplace<Vector2>(enemyEnt, Vector2{float(enemyInfo.x), float(enemyInfo.y)});

    // Add stats to enemy
    std::map<std::string, float> statsMap = GetObjectProperties(enemyInfo);
    float health = statsMap["Health"];
    float dmg = statsMap["DMG"];
    float moveSpeed = statsMap["MoveSpeed"];
    float AttackCoolDown = statsMap["AttackCoolDown"];
    Direction direction = LEFT;
    if (statsMap["Direction"] > 0){
        direction = RIGHT;
    }
    EnemyStats stats = EnemyStats(health, moveSpeed, dmg, 4, direction, false);
    registry.emplace<EnemyStats>(enemyEnt, stats);
    
    // Add sprites
    SpriteData farmerSprite = SpriteData(LoadTextures({
        {"FarmerR", "assets/sprites/enemies/farmer/FarmerR.png"},
        {"FarmerL", "assets/sprites/enemies/farmer/FarmerL.png"},
        {"FarmerRWalk", "assets/sprites/enemies/farmer/FarmerRWalk.png"},
        {"FarmerLWalk", "assets/sprites/enemies/farmer/FarmerLWalk.png"},
    }),
    WHITE
    );    
    switch (direction){
        case LEFT: {
            farmerSprite.SetTexture("FarmerL");
            break;
        }
        case RIGHT: {
            farmerSprite.SetTexture("FarmerR");
            break;
        }
    }
    farmerSprite.SetTexture("FarmerR");
    registry.emplace<SpriteData>(enemyEnt, farmerSprite);

    // Create Animation component for farmer
    Animation farmerAnimation;
    
    // Sprite sheet dimensions for walking
    int frameWidth = 16;
    int frameHeight = 16;
    int totalFrames = 6;
    
    // Create walk right animation sequence (6 frames)
    std::vector<AnimationFrame> walkRightFrames;
    for (int i = 0; i < totalFrames; i++) {
        walkRightFrames.push_back(AnimationFrame{
            Rectangle{(float)(i * frameWidth), 0, (float)frameWidth, (float)frameHeight},
            0.1f  // 0.1 seconds per frame
        });
    }
    farmerAnimation.AddSequence("walkRight", AnimationSequence(walkRightFrames, true));
    
    // Create walk left animation sequence (6 frames)
    std::vector<AnimationFrame> walkLeftFrames;
    for (int i = 0; i < totalFrames; i++) {
        walkLeftFrames.push_back(AnimationFrame{
            Rectangle{(float)(i * frameWidth), 0, (float)frameWidth, (float)frameHeight},
            0.1f  // 0.1 seconds per frame
        });
    }
    farmerAnimation.AddSequence("walkLeft", AnimationSequence(walkLeftFrames, true));
    
    // Create idle animations (single frame - first frame of each animation)
    farmerAnimation.AddSequence("idleRight", AnimationSequence({
        AnimationFrame{Rectangle{0, 0, (float)frameWidth, (float)frameHeight}, 1.0f}
    }, true));
    farmerAnimation.AddSequence("idleLeft", AnimationSequence({
        AnimationFrame{Rectangle{0, 0, (float)frameWidth, (float)frameHeight}, 1.0f}
    }, true));
    
    // Add Animation component to the entity
    registry.emplace<Animation>(enemyEnt, farmerAnimation);


    // Add sprites
    SpriteData farmerSprite = SpriteData(LoadTextures({
        {"AlienR", "assets/sprites/enemies/alien/AlienR.png"},
        {"AlienL", "assets/sprites/enemies/alien/AlienL.png"},
    }),
    WHITE
    );
    switch (direction){
        case LEFT: {
            farmerSprite.SetTexture("AlienL");
            break;
        }
        case RIGHT: {
            farmerSprite.SetTexture("AlienR");
            break;
        }
    }
    farmerSprite.SetTexture("FarmerR");
    registry.emplace<SpriteData>(enemyEnt, farmerSprite);

    // Add update function
    Enemy_behavior behavior = RangedEnemyUpdate;
    registry.emplace<Enemy_behavior>(enemyEnt, behavior);

    // Add the rest of the enemy components here
};
