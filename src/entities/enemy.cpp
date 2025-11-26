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
    EnemyStats stats = EnemyStats(FARMER, health, moveSpeed, dmg, AttackCoolDown, direction, false);
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
    float attackCooldown = statsMap["AttackCooldown"];

    Direction direction = LEFT;
    if (statsMap["Direction"] > 0){
        direction = RIGHT;
    }
    EnemyStats stats = EnemyStats(ALIEN, health, moveSpeed, dmg, attackCooldown, direction, false);
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
    SpriteData Sprite = SpriteData(LoadTextures({
        {"AlienR", "assets/sprites/enemies/alien/AlienR.png"},
        {"AlienL", "assets/sprites/enemies/alien/AlienL.png"},
        {"AlienRWalk", "assets/sprites/enemies/alien/AlienRWalk.png"},
        {"AlienLWalk", "assets/sprites/enemies/alien/AlienLWalk.png"},
    }),
    WHITE
    );
    switch (direction){
        case LEFT: {
            Sprite.SetTexture("AlienL");
            break;
        }
        case RIGHT: {
            Sprite.SetTexture("AlienR");
            break;
        }
    }
    Sprite.SetTexture("FarmerR");
    registry.emplace<SpriteData>(enemyEnt, Sprite);

    // Create Animation component for alien
    Animation alienAnimation;
    
    // Sprite sheet dimensions for walking
    int frameWidth = 16;
    int frameHeight = 16;
    int totalFrames = 6;
    
    // Create walk right animation sequence (6 frames)
    std::vector<AnimationFrame> walkRightFrames;
    for (int i = 0; i < totalFrames; i++) {
        walkRightFrames.push_back(AnimationFrame{
            Rectangle{(float)(i * frameWidth), 0, (float)frameWidth, (float)frameHeight},
            0.3f  // 0.3 seconds per frame
        });
    }
    alienAnimation.AddSequence("walkRight", AnimationSequence(walkRightFrames, true));
    
    // Create walk left animation sequence (4 frames)
    std::vector<AnimationFrame> walkLeftFrames;
    for (int i = 0; i < totalFrames; i++) {
        walkLeftFrames.push_back(AnimationFrame{
            Rectangle{(float)(i * frameWidth), 0, (float)frameWidth, (float)frameHeight},
            0.3f  // 0.3 seconds per frame
        });
    }
    alienAnimation.AddSequence("walkLeft", AnimationSequence(walkLeftFrames, true));
    
    // Add Animation component to the entity
    registry.emplace<Animation>(enemyEnt, alienAnimation);

    // Add weapon to enemy
    // Load weapon sprite
    SpriteData weaponSprite = SpriteData(LoadTextures({
        {"WeaponL", "assets/sprites/enemies/alien/AlienGunL.png"},
        {"WeaponR", "assets/sprites/enemies/alien/AlienGunR.png"},
    }),
    WHITE
    );
    switch (direction){
        case LEFT: {
            weaponSprite.SetTexture("WeaponL");
            break;
        }
        case RIGHT: {
            weaponSprite.SetTexture("WeaponR");
            break;
        }
    }
    TraceLog(LOG_INFO, "Weapon sprite id(%d) size(%d,%d)", weaponSprite.curentTexture.id, weaponSprite.curentTexture.width, weaponSprite.curentTexture.height);
    //Calculate Weapon position 
    Vector3 weaponOffset = Vector3{20,-5,-5};
    Weapon weapon = Weapon(weaponOffset, weaponSprite);
    registry.emplace<Weapon>(enemyEnt, weapon);

    // Add update function
    Enemy_behavior behavior = RangedEnemyUpdate;
    registry.emplace<Enemy_behavior>(enemyEnt, behavior);

    // Add the rest of the enemy components here
};

// Function to calculate the position of the enemy's weapon
Vector3 CalculateWeaponOffset(Vector3 offset, Vector3 enemyPos, EnemyStats stats){
    Vector3 pos;

    if (stats.CurrentDirection == LEFT){
        pos.x = enemyPos.x - offset.x;
        pos.y = enemyPos.y - offset.y;
    }
    else {
        pos.x = enemyPos.x + 8 + offset.x;  
        pos.y = enemyPos.y - offset.z; 
    }
    return pos;    
}
