#include "enemy_behavior.hpp"
#include "sprite_data.hpp"

void TestUpdateFunc(entt::registry &registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");

    // Get components from enemy entity
    auto& pos = registry.get<Transform>(enemy);
    auto& physics = registry.get<PhysicsObject>(enemy);
    auto& stats = registry.get<EnemyStats>(enemy);

    pos.translation.x += stats.enemySpeed * dt;
    TraceLog(LOG_TRACE, "Exiting TestUpdateFunc");
}

void BasicEnemyUpdate(entt::registry & registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering Function BasicEnemyUpdate");
    TraceLog(LOG_INFO, "Updating entity: %d", enemy);
    float maxDistance = 300;    

    // Get components from enemy entity    auto& pos = registry.get<Transform>(enemy);
    auto& pos = registry.get<Transform>(enemy);
    auto& physics = registry.get<PhysicsObject>(enemy);
    auto& stats = registry.get<EnemyStats>(enemy);
    auto& spawn = registry.get<Vector2>(enemy);
    auto& sprite = registry.get<SpriteData>(enemy);

    // Get components from enemy entity    auto& pos = registry.get<Transform>(enemy);
    auto& pos = registry.get<Transform>(enemy);
    auto& physics = registry.get<PhysicsObject>(enemy);
    auto& stats = registry.get<EnemyStats>(enemy);
    auto& spawn = registry.get<Vector2>(enemy);
    auto& sprite = registry.get<SpriteData>(enemy);

    physics.velocity.y += GRAVITY * dt;

    // Check if we are following the player
    if(stats.followsPlayer){

        // Move towards player
        if (pos.translation.x < playerPos.translation.x){
            physics.velocity.x = stats.enemySpeed * 1;
            stats.CurrentDirection = LEFT;
            sprite.SetTexture("FarmerL");
        } else {
            physics.velocity.x = stats.enemySpeed * -1;
            stats.CurrentDirection = RIGHT;
            sprite.SetTexture("FarmerR");
        }

        // Check if we should stop following the player
        float distanceFromPlayer = abs(pos.translation.x - playerPos.translation.x);
        if (distanceFromPlayer > 200){
            stats.followsPlayer = false;
        }
    } else {

        // Check distance from spawn point
        int distanceFromSpawn = abs(pos.translation.x - spawn.x);
        
        // set direction based on distance from spawn 
        if(distanceFromSpawn > maxDistance){
            if(pos.translation.x > spawn.x){
                stats.CurrentDirection = LEFT;
                sprite.SetTexture("FarmerL");
            }
            else{
                stats.CurrentDirection = RIGHT;
                sprite.SetTexture("FarmerR");
            }
        }

        // Move based on current direction
        if(stats.CurrentDirection == LEFT){
            physics.velocity.x = stats.enemySpeed * -1;
            sprite.SetTexture("FarmerL");
        }
        else if(stats.CurrentDirection == RIGHT){
            physics.velocity.x = stats.enemySpeed * 1;
            sprite.SetTexture("FarmerR");
        }
    }
    MoveEntity(registry, dt, enemy);
}


Enemy_behavior::Enemy_behavior(UpdateFunction Update){
    this->Update = Update;
}