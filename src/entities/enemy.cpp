#include "enemy.hpp"
#include "../include/raylib.h"

void CreateEnemy(entt::registry &registry, Vector2 spawnPoint) {
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

    // Add Transform component to the entity
    registry.view<Map, TmxMap>().each([&registry, &enemyEnt, &spawnPoint](TmxMap &map){
        TmxObjectGroup entities = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;
        TmxObject enemy = FindObjectByName(entities.objects, entities.objectsLength, "Enemy");

        Transform enemyTransform = Transform{ {(float)enemy.x, (float)enemy.y, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32} };

        registry.emplace<Transform>(enemyEnt, enemyTransform);
    });

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(enemyEnt, physics);

    // Add Vector2 to mark where the enemy spawned from
    registry.emplace<Vector2>(enemyEnt, spawnPoint);

    // Add the rest of the enemy components here

};