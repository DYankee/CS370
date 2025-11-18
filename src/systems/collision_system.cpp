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

    registry.view<Map, TmxMap>().each([&registry, &entity, dt](TmxMap &map) {
        TmxObject hitObj;

        // Get entity components
        auto& pos = registry.get<Transform>(entity);
        auto& physics = registry.get<PhysicsObject>(entity);

        // Log current pos
        TraceLog(LOG_INFO, "Entity Current Pos: %f,%f", pos.translation.x, pos.translation.y);
        TraceLog(LOG_INFO, "Entity Current Velocity: %f,%f", physics.velocity.x, physics.velocity.y);

        // Handle X Axis Movement & Collision
        transform.translation.x += physics.velocity.x * dt;

        Rectangle entityRectX = { 
            transform.translation.x, 
            transform.translation.y, 
            transform.scale.x, 
            transform.scale.y 
        };

        TraceLog(LOG_INFO, "Entity destination pos: %f,%f", nextPos.x, nextPos.y);
        
        Rectangle playerDestRec = { nextPos.x, nextPos.y, pos.scale.x, pos.scale.y };
        Rectangle playerDestRecX = { nextPos.x, pos.translation.y, pos.scale.x, pos.scale.y };
        Rectangle playerDestRecY = { pos.translation.x, nextPos.y, pos.scale.x, pos.scale.y };
        // Log new Pos
        TraceLog(LOG_INFO, "Player Current Pos: %f,%f", nextPos.x, nextPos.y);

        bool collided = CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRec, &hitObj);

        if (collided) {
            TraceLog(LOG_INFO, "Collision detected at position (%f, %f)", nextPos.x, nextPos.y);
            // Vertical collision detection

            float nextX = playerDestRec.x + playerDestRec.width;
            float nextY = playerDestRec.y + playerDestRec.height;

            // Horizontal collision only
            if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRecX, &hitObj)) {
                pos.translation.x = nextPos.x;
                physics.velocity.x -= physics.velocity.x / 2;
            } else {
                physics.velocity.x = 0;
                // make sure player isn't inside the collided object
                if (pos.translation.x < hitObj.x){
                pos.translation.x = hitObj.x - pos.scale.x;
                    } else {
                        pos.translation.x = hitObj.x + hitObj.width;
                    }
                     // Stop horizontal movement
                }
 
                if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRecY, &hitObj)) {
                    pos.translation.y = nextPos.y;
                } else {
                    physics.velocity.y = 0; // Stop vertical movement
                    // make sure player isn't inside the collided object
                    if (pos.translation.y < hitObj.y){
                        pos.translation.y = hitObj.y - pos.scale.y;
                    } else {
                        pos.translation.y = hitObj.y + hitObj.height;
                    }
                }    
        } else {
            // No collision: accept movement
            pos.translation = nextPos;
        }
        
        // Handle Y Axis Movement & Collision
        transform.translation.y += physics.velocity.y * dt;

        Rectangle entityRectY = { 
            transform.translation.x, 
            transform.translation.y, 
            transform.scale.x, 
            transform.scale.y 
        };

        if (CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, entityRectY, &hitObj)) {
            TraceLog(LOG_INFO, "Y Axis Collision");

            if (physics.velocity.y > 0) {
                // Falling Down - Snap to top of object (Floor)
                transform.translation.y = hitObj.y - transform.scale.y;
            } else if (physics.velocity.y < 0) {
                // Jumping Up - Snap to bottom of object (Ceiling)
                transform.translation.y = hitObj.y + hitObj.height;
            }
            // Kill Y momentum on impact
            physics.velocity.y = 0;
            physics.velocity.x /= 1.5;
        }


        // Log final pos
        TraceLog(LOG_INFO, "Entity Final Pos: %f, %f", transform.translation.x, transform.translation.y);
    });
}