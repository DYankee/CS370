#include "projectile_manager.hpp"
#include "../components/components.hpp"


void UpdateProjectiles(entt::registry &registry, float dt){

    registry.view<Transform, Vector3, ProjectileStats, Projectile>().each(
        [dt, &registry](entt::entity projectile, Transform &pos, Vector3 &targetPos, ProjectileStats &stats) {
        
        // Track if the projectile should be destroyed
        bool markForDestruction = false;
        
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
            if (collision){
                // Add function for damaging player here
            }
            //mark projectile for deletion
            markForDestruction = true;
        } else {
            // Otherwise, move the projectile towards the target by the calculated travelDistance
            pos.translation.x += normalizedDirX * travelDistance;
            pos.translation.y += normalizedDirY * travelDistance;
            
            //Check for map collisions
            bool collision = CheckProjectileMapCollision(registry, projectile);
            if (collision){
                //mark projectile for deletion
                markForDestruction = true;
            }

            // Check for player collision
            collision = CheckProjectilePlayerCollision(registry, projectile);
            if (collision){

                // Add function for damaging player here

                //mark projectile for deletion
                markForDestruction = true;
            }
        }
        if(markForDestruction){registry.destroy(projectile);}
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

bool CheckProjectileMapCollision(entt::registry &registry, entt::entity projectile){
    TraceLog(LOG_TRACE, "Enter function CheckProjectileMapCollision");
    
    bool collision = false;

    // Get projectile components
    Transform projectilePos = registry.get<Transform>(projectile);
    
    // Get map entity and components
    auto maps = registry.view<Map>();

    if (maps.size() == 0){
        TraceLog(LOG_FATAL, "No map found!");
    }

    TmxMap &map = registry.get<TmxMap>(maps.front());
    
    // create projectile rect
    Rectangle projectileRect{
        projectilePos.translation.x, projectilePos.translation.y,
        projectilePos.scale.x, projectilePos.scale.y,
    };


    
    TraceLog(LOG_TRACE, "Checking projectile map collision");
    TmxObject hitObjX;
    if (CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, projectileRect, &hitObjX)){
        collision = true;
    }

    TraceLog(LOG_TRACE, "projectile map collision: ", collision ? "True" : "False");
    return collision;
}

void RemoveAllProjectiles(entt::registry &registry){
    for (const auto entity : registry.view<Projectile>()){
        registry.destroy(entity);
    } 
}