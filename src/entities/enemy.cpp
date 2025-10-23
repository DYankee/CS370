#include "enemy.hpp"

void CreateEnemy(entt::registry &registry) {
    TraceLog(LOG_TRACE, "Entering Function: CreateEnemy");
    TraceLog(LOG_INFO, "Creating Enemy Entity");
    
    // Add entity to the registry
    entt::entity enemyEnt = registry.create();

    // Add Enemy component to the entity
    Enemy enemyComponent;
    registry.emplace<Enemy>(enemyEnt, enemyComponent);

    // TODO


};