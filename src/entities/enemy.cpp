#include "enemy.hpp"
#include "../include/raylib.h"

void CreateEnemy(entt::registry &registry) {
    TraceLog(LOG_TRACE, "Entering Function: CreateEnemy");
    TraceLog(LOG_INFO, "Creating Enemy Entity");
    
    // Add entity to the registry
    entt::entity enemyEnt = registry.create();

    // Add Enemy component to the entity
    Enemy enemyComponent;
    registry.emplace<Enemy>(enemyEnt, enemyComponent);

    // Add sprites
    // test sprite for now
    SpriteData enemySprite = SpriteData(LoadTextures({
        {"FarmerR", "assets/sprites/FarmerR.png"}
    }),
    WHITE
    );
    enemySprite.SetTexture("FarmerR");
    registry.emplace<SpriteData>(enemyEnt, enemySprite);

    // add Transform component
    Transform enemyTransform = Transform{ {240.0f, 930.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32} };
                                            //test values
    registry.emplace<Transform>(enemyEnt, enemyTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(enemyEnt, physics);


    // Add the rest of the enemy components here

};