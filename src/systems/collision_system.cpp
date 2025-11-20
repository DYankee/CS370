#include "collision_system.hpp" //find an object/group layer by name

void SpikeCollision(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: SpikeCollision");
    TraceLog(LOG_INFO, "Starting spike collision check");

    registry.view<Player, PhysicsObject, Transform, PlayerStats>().each([dt, &registry](PhysicsObject &physics, Transform &transform, PlayerStats &stats) {
        // Check collisions with spike objects
        if (stats.iFrames <= 0.0f) {
            // find object layer named "Spikes"
            registry.view<Map, TmxMap>().each([&physics, &transform, &stats](TmxMap &map) {
                TmxLayer* spikesLayer = FindLayerByName(map.layers, map.layersLength, "Spikes");
                if (spikesLayer != NULL && spikesLayer->type == LAYER_TYPE_OBJECT_GROUP) {
                    TmxObject hitObj;
                    Rectangle playerRec = { transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y };
                    bool hit = CheckCollisionTMXObjectGroupRec(spikesLayer->exact.objectGroup, playerRec, &hitObj);
                    if (hit) {
                        // handle damage/response
                        stats.health -= 1;
                        // Apply knockback
                        if (physics.velocity.x >= 0) { 
                            physics.velocity.x = -100.0f;
                        } else {              
                            physics.velocity.x = 300.0f;
                        }
                        physics.velocity.y = -600.0f; // Upward knockback

                        //start I frames
                        stats.iFrames = stats.maxIFrames;
                       
                        TraceLog(LOG_INFO, "Ouch! Health: %d", stats.health);
                    }   
                }
            });
        }
    });
}



// Check collisions against tile layers
void MoveEntity(entt::registry& registry, float dt, entt::entity &entity){
    TraceLog(LOG_TRACE, "Entering Function: MoveEntity");
    TraceLog(LOG_INFO, "Moving entity: %d", entity);

    // Get a reference to the current map
    auto view = registry.view<Map>();
    if (view.front() == entt::null){
        TraceLog(LOG_ERROR, "No map loaded in function MoveEntity");
    }
    entt::entity mapEntity = view.front();
    TmxMap map = registry.get<TmxMap>(mapEntity);
    if (&map == NULL|| map.layers == NULL || map.layersLength == 0){
        TraceLog(LOG_ERROR, "No map loaded");
    }
    
    TmxObject hitObj;

    // Get entity components
    auto& pos = registry.get<Transform>(entity);
    auto& physics = registry.get<PhysicsObject>(entity);

    // Log current pos
    TraceLog(LOG_INFO, "Entity: %d, Current Pos: %f,%f",entity, pos.translation.x, pos.translation.y);
    TraceLog(LOG_INFO, "Entity: %d, Current Velocity: %f,%f",entity, physics.velocity.x, physics.velocity.y);

    // Calculate next position
    Vector3 nextPos = {
        pos.translation.x + physics.velocity.x * dt,
        pos.translation.y + physics.velocity.y * dt,
        pos.translation.z
    };

    TraceLog(LOG_INFO, "Entity: %d, destination pos: %f,%f",entity, nextPos.x, nextPos.y);
        
    TraceLog(LOG_INFO, "Checking entity: %d, for collision", entity);
    Rectangle entityDestRec = { nextPos.x, nextPos.y, pos.scale.x, pos.scale.y };

    bool collided = CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, entityDestRec, &hitObj);
    TraceLog(LOG_INFO, "Entity: %d collision? %d",entity, collided);
    if (collided) {
        TraceLog(LOG_INFO, "Entity: %d, collision detected at position (%f, %f) with map object: %c, pos(%f,%f) size(%f,%f)",
            entity, nextPos.x, nextPos.y,
            hitObj.id, hitObj.x, hitObj.y, hitObj.width, hitObj.height);
            
        // Horizontal collision detection
        Rectangle entityDestRecX = { nextPos.x, pos.translation.y, pos.scale.x, pos.scale.y };
        if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, entityDestRecX, &hitObj)) {
            physics.velocity.x -= physics.velocity.x / 2;
        } else {
            // make sure player isn't inside the collided object
            if (nextPos.x < hitObj.x){
                nextPos.x = hitObj.x - pos.scale.x;
                physics.velocity.x = -20;
            } else {
                nextPos.x = hitObj.x + hitObj.width;
                physics.velocity.x = 20;
            }
        }
        TraceLog(LOG_INFO, "Entity: %d, position after x axis collision check (%f, %f)",entity, nextPos.x, nextPos.y);
        // Vertical collision detection
        Rectangle entityDestRecY = { pos.translation.x, nextPos.y, pos.scale.x, pos.scale.y };
        if (CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, entityDestRecY, &hitObj)) {
            // make sure player isn't inside the collided object
            if (nextPos.y < hitObj.y){
                nextPos.y = hitObj.y - pos.scale.y;
                physics.velocity.y = 0; // Stop vertical movement
            } else {
                nextPos.y = hitObj.y + hitObj.height;
                physics.velocity.y = 0; // Stop vertical movement
            }
        }
        TraceLog(LOG_INFO, "Entity: %d, position after y axis collision check (%f, %f)",entity, nextPos.x, nextPos.y);
    }
    // Move entity to collision checked new location
    pos.translation = nextPos;
    TraceLog(LOG_INFO, "Entity: %d, moved to pos: %f,%f",entity, nextPos.x, nextPos.y);
}