#include "projectile_manager.hpp"
#include "../components/components.hpp"


void UpdateProjectiles(entt::registry &registry, float dt){

    registry.view<Transform, Vector3, ProjectileStats, Projectile>().each(
        [dt, &registry](entt::entity projectile, Transform &pos, Vector3 &targetPos, ProjectileStats &stats, Projectile &proj) {

            bool markForDestruction = false;

            if (proj.fromPlayer) {
                pos.translation.x += targetPos.x * dt;
                pos.translation.y += targetPos.y * dt;
            } else {
            // Calculate the direction vector from the current position to the target position
            float dx = targetPos.x - pos.translation.x;
            float dy = targetPos.y - pos.translation.y;

            // Calculate the squared distance to the target
            float distanceSquared = (dx * dx) + (dy * dy);
            float distance = std::sqrt(distanceSquared);

            // Normalize the direction vector
            // This gives a unit vector pointing from pos to targetPos
            float invDistance = 1.0f / distance;
            float normalizedDirX = dx * invDistance;
            float normalizedDirY = dy * invDistance;

            // Calculate the maximum distance the projectile can travel this frame
            float travelDistance = stats.Speed * dt;

            // Ensure the projectile doesn't overshoot the target
            if (travelDistance > distance) {
                // If the calculated travel distance is greater than the remaining distance move directly to the target position.
                pos.translation.x = targetPos.x;
                pos.translation.y = targetPos.y;

                // Check for player collision
                bool collision = CheckProjectilePlayerCollision(registry, projectile);
                if (!proj.fromPlayer && collision){
                    ApplyProjectileDamage(registry, projectile);
                }
                //mark projectile for deletion
                markForDestruction = true;
            } else {
                // Otherwise, move the projectile towards the target by the calculated travelDistance
                pos.translation.x += normalizedDirX * travelDistance;
                pos.translation.y += normalizedDirY * travelDistance;
                }
            }

            // Check collisions
            if (CheckProjectileMapCollision(registry, projectile)) {
                markForDestruction = true;
            }

            if (!proj.fromPlayer && CheckProjectilePlayerCollision(registry, projectile)) {
                ApplyProjectileDamage(registry, projectile);
                markForDestruction = true;
            }
            if (proj.fromPlayer && CheckProjectileEnemyCollision(registry, projectile)) {
            markForDestruction = true;
            }

            if (markForDestruction) {
                registry.destroy(projectile);
            }
    });
}


bool CheckProjectilePlayerCollision(entt::registry &registry, entt::entity projectile){
    bool collision = false;

    // Get projectile components
    Transform &projectilePos = registry.get<Transform>(projectile);

    // Get player components
    entt::entity player = registry.view<Player>().front();
    Transform &playerPos = registry.get<Transform>(player);
    
    //Check if they overlap
    if (playerPos.translation.x + playerPos.scale.x <= projectilePos.translation.x 
    || projectilePos.translation.x + projectilePos.scale.x <= playerPos.translation.x) {
        collision = false;
    } 
    else if (playerPos.translation.y + playerPos.scale.y <= projectilePos.translation.y 
    || projectilePos.translation.y + projectilePos.scale.y <= playerPos.translation.y) {
        collision = false;
    }
    else {
        collision = true;
    }
    return collision;
}
bool CheckProjectileEnemyCollision(entt::registry &registry, entt::entity projectile) {
    Transform &projectilePos = registry.get<Transform>(projectile);


    bool hitEnemy = false;

    registry.view<EnemyStats, Transform, PhysicsObject>().each(
        [&](entt::entity enemyEntity, EnemyStats &enemyStats, Transform &enemyPos, PhysicsObject &enemyPhysics) {

            // Skip NPCs
            if (registry.any_of<NPC>(enemyEntity)) return;

            bool collision = true;

            if (enemyPos.translation.x + enemyPos.scale.x <= projectilePos.translation.x ||
                projectilePos.translation.x + projectilePos.scale.x <= enemyPos.translation.x) 
            {
                collision = false;
            }
            else if (enemyPos.translation.y + enemyPos.scale.y <= projectilePos.translation.y ||
                     projectilePos.translation.y + projectilePos.scale.y <= enemyPos.translation.y) 
            {
                collision = false;
            }
            else 
            {
                collision = true;
            }

            if (collision) {
                registry.destroy(enemyEntity);
                hitEnemy = true;
            }
        }
    );

    return hitEnemy;
}



bool CheckProjectileMapCollision(entt::registry &registry, entt::entity projectile){
    TraceLog(LOG_TRACE, "Enter function CheckProjectileMapCollision");
    
    bool collision = false;

    // Get projectile components
    Transform &projectilePos = registry.get<Transform>(projectile);
    
    // Get map entity and components
    auto maps = registry.view<Map>();
    TmxMap &map = registry.get<TmxMap>(maps.front());
    
    // create projectile rect
    Rectangle projectileRect{
        projectilePos.translation.x, projectilePos.translation.y,
        projectilePos.scale.x, projectilePos.scale.y,
    };

    TraceLog(LOG_TRACE, "Checking projectile map collision");
    TmxObject hitObj;
    if (CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, projectileRect, &hitObj)){
        collision = true;
    }

    TraceLog(LOG_TRACE, "projectile map collision: ", collision ? "True" : "False");
    return collision;
}

void ApplyProjectileDamage(entt::registry &registry, entt::entity projectile){
    // Get player components
    entt::entity player = registry.view<Player>().front();
    PlayerStats &playerStats = registry.get<PlayerStats>(player);

    // Get projectile components
    ProjectileStats &projectileStats = registry.get<ProjectileStats>(projectile);

    // Check if player can be damaged
    if(playerStats.iFrames <= 0.0f){
        // Apply damage to player
        playerStats.health -= projectileStats.dmg; 
        
        //start I frames
        playerStats.iFrames = playerStats.maxIFrames;
    }
}

void RemoveAllProjectiles(entt::registry &registry){
    for (const auto entity : registry.view<Projectile>()){
        registry.destroy(entity);
    } 
}