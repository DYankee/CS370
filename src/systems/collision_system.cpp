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

    registry.view<Map, TmxMap>().each([&registry, &entity, dt](TmxMap &map) {
        TmxObject hitObj;

        // Get entity components
        auto& pos = registry.get<Transform>(entity);
        auto& physics = registry.get<PhysicsObject>(entity);

        // Log current pos
        TraceLog(LOG_INFO, "Entity Current Pos: %f,%f", pos.translation.x, pos.translation.y);
        TraceLog(LOG_INFO, "Entity Current Velocity: %f,%f", physics.velocity.x, physics.velocity.y);

        // Calculate next position
        Vector3 nextPos = {
            pos.translation.x + physics.velocity.x * dt,
            pos.translation.y + physics.velocity.y * dt,
            pos.translation.z
        };

        TraceLog(LOG_INFO, "Entity destination pos: %f,%f", nextPos.x, nextPos.y);
        
        Rectangle playerDestRec = { nextPos.x, nextPos.y, pos.scale.x, pos.scale.y };
        bool collided = CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRec, &hitObj);
        
        if (collided) {
            TraceLog(LOG_INFO, "Collision detected at position (%f, %f)", nextPos.x, nextPos.y);
            
            
            // Horizontal collision detection
            Rectangle playerDestRecX = { nextPos.x, pos.translation.y, pos.scale.x, pos.scale.y };
            if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRecX, &hitObj)) {
                pos.translation.x = nextPos.x;
                physics.velocity.x -= physics.velocity.x / 2;
            } else {
                // make sure player isn't inside the collided object
                if (pos.translation.x < hitObj.x){
                    pos.translation.x = hitObj.x - pos.scale.x;
                    physics.velocity.x = -20;
                } else {
                    pos.translation.x = hitObj.x + hitObj.width;
                    physics.velocity.x = 20;
                }
            }
 
            // Vertical collision detection
            Rectangle playerDestRecY = { pos.translation.x, nextPos.y, pos.scale.x, pos.scale.y };
            if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRecY, &hitObj)) {
                pos.translation.y = nextPos.y;
            } else {
                // make sure player isn't inside the collided object
                if (pos.translation.y < hitObj.y){
                    pos.translation.y = hitObj.y - pos.scale.y;
                    physics.velocity.y = 0; // Stop vertical movement
                } else {
                    pos.translation.y = hitObj.y + hitObj.height;
                    physics.velocity.y = 0; // Stop vertical movement
                }
            }

        } else {
            // No collision: accept movement
            pos.translation = nextPos;
            TraceLog(LOG_INFO, "Entity moved to pos: %f,%f", nextPos.x, nextPos.y);
        }
    }); 
}