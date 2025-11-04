#include "enemy_behavior.hpp"

void TestUpdateFunc(entt::registry &registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");

    // Get components from enemy entity
    auto [pos, physics, stats] = registry.get<Transform, PhysicsObject, EnemyStats>(enemy);

    pos.translation.x += stats.enemySpeed * dt;
    TraceLog(LOG_TRACE, "Exiting TestUpdateFunc");
}

void BasicEnemyUpdate(entt::registry & registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");
    float maxDistance = 200;    


    // Get components from enemy entity
    auto [pos, spawn, physics, stats] = registry.get<Transform, Vector2, PhysicsObject, EnemyStats>(enemy);

    physics.velocity.y += GRAVITY * dt;

    if(!stats.followsPlayer){
        int distanceFromSpawn = abs(pos.translation.x - spawn.x);
        if(distanceFromSpawn > maxDistance){
            stats.CurrentDirection = ChangeDirection(stats.CurrentDirection);
        }

        if(stats.CurrentDirection == LEFT){
            physics.velocity.x = stats.enemySpeed * -1;
        }
        else if(stats.CurrentDirection == RIGHT){
            physics.velocity.x = stats.enemySpeed * 1;
        }
    }
    else{

    }
    MoveEntity(registry, dt, enemy);
}


Enemy_behavior::Enemy_behavior(UpdateFunction Update){
    this->Update = Update;
}