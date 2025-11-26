#include "npc.hpp"
#include "../include/raylib.h"
#include "../components/npc_behavior.hpp"

void CreatePig(entt::registry &registry, TmxObject npcInfo) {
    TraceLog(LOG_TRACE, "Entering Function: CreatePig");
    TraceLog(LOG_INFO, "Creating Pig NPC Entity");
    
    // Add entity to the registry
    entt::entity npcEnt = registry.create();

    // Add NPC component to the entity
    NPC npcComponent;
    registry.emplace<NPC>(npcEnt, npcComponent);

    // Add Transform component to the entity
    Transform npcTransform = Transform{ {float(npcInfo.x), float(npcInfo.y), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32} };
    registry.emplace<Transform>(npcEnt, npcTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(npcEnt, physics);

    // Add Vector2 to mark where the NPC spawned from
    registry.emplace<Vector2>(npcEnt, Vector2{float(npcInfo.x), float(npcInfo.y)});

    // Add stats to NPC
    std::map<std::string, float> statsMap = GetObjectProperties(npcInfo);
    float health = statsMap["Health"];
    float moveSpeed = statsMap["MoveSpeed"];
    Direction direction = LEFT;
    if (statsMap["Direction"] > 0){
        direction = RIGHT;
    }
    EnemyStats stats = EnemyStats(NONE, health, moveSpeed, 0.0f, 0.0f, direction, false);
    registry.emplace<EnemyStats>(npcEnt, stats);
    
    // Add sprites
    SpriteData pigSprite = SpriteData(LoadTextures({
        {"PigR", "assets/sprites/npcs/PigR.png"},
        {"PigL", "assets/sprites/npcs/PigL.png"},
    }),
    WHITE
    );    
    switch (direction){
        case LEFT: {
            pigSprite.SetTexture("PigL");
            break;
        }
        case RIGHT: {
            pigSprite.SetTexture("PigR");
            break;
        }
    }
    registry.emplace<SpriteData>(npcEnt, pigSprite);
    
    // Add NPC_behavior to make NPC face the player
    NPC_behavior behavior = NPC_behavior(NPCUpdate);
    registry.emplace<NPC_behavior>(npcEnt, behavior);
}

void CreateChicken(entt::registry &registry, TmxObject npcInfo) {
    TraceLog(LOG_TRACE, "Entering Function: CreateChicken");
    TraceLog(LOG_INFO, "Creating Chicken NPC Entity");
    
    // Add entity to the registry
    entt::entity npcEnt = registry.create();

    // Add NPC component to the entity
    NPC npcComponent;
    registry.emplace<NPC>(npcEnt, npcComponent);

    // Add Transform component to the entity
    Transform npcTransform = Transform{ {float(npcInfo.x), float(npcInfo.y), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32} };
    registry.emplace<Transform>(npcEnt, npcTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(npcEnt, physics);

    // Add Vector2 to mark where the NPC spawned from
    registry.emplace<Vector2>(npcEnt, Vector2{float(npcInfo.x), float(npcInfo.y)});

    // Add stats to NPC
    std::map<std::string, float> statsMap = GetObjectProperties(npcInfo);
    float health = statsMap["Health"];
    float moveSpeed = statsMap["MoveSpeed"];
    Direction direction = LEFT;
    if (statsMap["Direction"] > 0){
        direction = RIGHT;
    }
    EnemyStats stats = EnemyStats(NONE, health, moveSpeed, 0.0f, 0.0f, direction, false);
    registry.emplace<EnemyStats>(npcEnt, stats);
    
    // Add sprites
    SpriteData chickenSprite = SpriteData(LoadTextures({
        {"ChickenR", "assets/sprites/npcs/ChickenR.png"},
        {"ChickenL", "assets/sprites/npcs/ChickenL.png"},
    }),
    WHITE
    );    
    switch (direction){
        case LEFT: {
            chickenSprite.SetTexture("ChickenL");
            break;
        }
        case RIGHT: {
            chickenSprite.SetTexture("ChickenR");
            break;
        }
    }
    registry.emplace<SpriteData>(npcEnt, chickenSprite);
    
    // Add NPC_behavior to make NPC face the player
    NPC_behavior behavior = NPC_behavior(NPCUpdate);
    registry.emplace<NPC_behavior>(npcEnt, behavior);
}

void CreateSheep(entt::registry &registry, TmxObject npcInfo) {
    TraceLog(LOG_TRACE, "Entering Function: CreateSheep");
    TraceLog(LOG_INFO, "Creating Sheep NPC Entity");
    
    // Add entity to the registry
    entt::entity npcEnt = registry.create();

    // Add NPC component to the entity
    NPC npcComponent;
    registry.emplace<NPC>(npcEnt, npcComponent);

    // Add Transform component to the entity
    Transform npcTransform = Transform{ {float(npcInfo.x), float(npcInfo.y), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32} };
    registry.emplace<Transform>(npcEnt, npcTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(npcEnt, physics);

    // Add Vector2 to mark where the NPC spawned from
    registry.emplace<Vector2>(npcEnt, Vector2{float(npcInfo.x), float(npcInfo.y)});

    // Add stats to NPC
    std::map<std::string, float> statsMap = GetObjectProperties(npcInfo);
    float health = statsMap["Health"];
    float moveSpeed = statsMap["MoveSpeed"];
    Direction direction = LEFT;
    if (statsMap["Direction"] > 0){
        direction = RIGHT;
    }
    EnemyStats stats = EnemyStats(NONE, health, moveSpeed, 0.0f, 0.0f, direction, false);
    registry.emplace<EnemyStats>(npcEnt, stats);
    
    // Add sprites
    SpriteData sheepSprite = SpriteData(LoadTextures({
        {"SheepR", "assets/sprites/npcs/SheepR.png"},
        {"SheepL", "assets/sprites/npcs/SheepL.png"},
    }),
    WHITE
    );    
    switch (direction){
        case LEFT: {
            sheepSprite.SetTexture("SheepL");
            break;
        }
        case RIGHT: {
            sheepSprite.SetTexture("SheepR");
            break;
        }
    }
    registry.emplace<SpriteData>(npcEnt, sheepSprite);
    
    // Add NPC_behavior to make NPC face the player
    NPC_behavior behavior = NPC_behavior(NPCUpdate);
    registry.emplace<NPC_behavior>(npcEnt, behavior);
}

void CreateChick(entt::registry &registry, TmxObject npcInfo) {
    TraceLog(LOG_TRACE, "Entering Function: CreateChick");
    TraceLog(LOG_INFO, "Creating Chick NPC Entity");
    
    // Add entity to the registry
    entt::entity npcEnt = registry.create();

    // Add NPC component to the entity
    NPC npcComponent;
    registry.emplace<NPC>(npcEnt, npcComponent);

    // Add Transform component to the entity
    Transform npcTransform = Transform{ {float(npcInfo.x), float(npcInfo.y), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32} };
    registry.emplace<Transform>(npcEnt, npcTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(npcEnt, physics);

    // Add Vector2 to mark where the NPC spawned from
    registry.emplace<Vector2>(npcEnt, Vector2{float(npcInfo.x), float(npcInfo.y)});

    // Add stats to NPC
    std::map<std::string, float> statsMap = GetObjectProperties(npcInfo);
    float health = statsMap["Health"];
    float moveSpeed = statsMap["MoveSpeed"];
    Direction direction = LEFT;
    if (statsMap["Direction"] > 0){
        direction = RIGHT;
    }
    EnemyStats stats = EnemyStats(NONE, health, moveSpeed, 0.0f, 0.0f, direction, false);
    registry.emplace<EnemyStats>(npcEnt, stats);
    
    // Add sprites
    SpriteData chickSprite = SpriteData(LoadTextures({
        {"ChickR", "assets/sprites/npcs/ChickR.png"},
        {"ChickL", "assets/sprites/npcs/ChickL.png"},
    }),
    WHITE
    );    
    switch (direction){
        case LEFT: {
            chickSprite.SetTexture("ChickL");
            break;
        }
        case RIGHT: {
            chickSprite.SetTexture("ChickR");
            break;
        }
    }
    registry.emplace<SpriteData>(npcEnt, chickSprite);
    
    // Add NPC_behavior to make NPC face the player
    NPC_behavior behavior = NPC_behavior(NPCUpdate);
    registry.emplace<NPC_behavior>(npcEnt, behavior);
}
