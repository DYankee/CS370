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
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");
    float maxDistance = 200;    


    // Get components from enemy entity    auto& pos = registry.get<Transform>(enemy);
    auto& pos = registry.get<Transform>(enemy);
    auto& physics = registry.get<PhysicsObject>(enemy);
    auto& stats = registry.get<EnemyStats>(enemy);
    auto& spawn = registry.get<Vector2>(enemy);
    auto& sprite = registry.get<SpriteData>(enemy);

    physics.velocity.y += 2000.0f * dt;

    if(!stats.followsPlayer){
        int distanceFromSpawn = abs(pos.translation.x - spawn.x);
        if(distanceFromSpawn > maxDistance){
            stats.CurrentDirection = ChangeDirection(stats.CurrentDirection);
        }

        if(stats.CurrentDirection == LEFT){
            physics.velocity.x = stats.enemySpeed * -1;
            sprite.SetTexture("FarmerL");
        }
        else if(stats.CurrentDirection == RIGHT){
            physics.velocity.x = stats.enemySpeed * 1;
            sprite.SetTexture("FarmerR");
        }
    }
    else{

    }
    MoveEntity(registry, dt, enemy);
}


Enemy_behavior::Enemy_behavior(UpdateFunction Update){
    this->Update = Update;
}