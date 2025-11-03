#include "enemy_behavior.hpp"

void TestUpdateFunc(entt::registry &registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");

    // Get components from enemy entity
    auto [pos, physics, stats] = registry.get<Transform, PhysicsObject, EnemyStats>(enemy);

    pos.translation.x += stats.enemySpeed * dt;
    TraceLog(LOG_TRACE, "Exiting TestUpdateFunc");
}


Enemy_behavior::Enemy_behavior(UpdateFunction Update){
    this->Update = Update;
}