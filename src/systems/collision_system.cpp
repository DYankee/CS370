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
void TileCollision(entt::registry& registry, float dt){
    TraceLog(LOG_TRACE, "Entering Function: TileCollision");
    TraceLog(LOG_INFO, "Starting tile collision check");

    registry.view<Player, PhysicsObject, Transform>().each([dt, &registry](PhysicsObject &physics, Transform &transform) {
        registry.view<Map, TmxMap>().each([&physics, &transform, dt](TmxMap &map) {
            TmxObject hitObj;
            
            // Log current pos
            TraceLog(LOG_INFO, "Player Current Pos: %f,%f", transform.translation.x, transform.translation.y);

            // Calculate next position
            Vector3 nextPos = {
                transform.translation.x + physics.velocity.x * dt,
                transform.translation.y + physics.velocity.y * dt,
                transform.translation.z
            };
            // Log new Pos
            TraceLog(LOG_INFO, "Player Current Pos: %f,%f", nextPos.x, nextPos.y);

            Rectangle playerDestRec = { nextPos.x, nextPos.y, transform.scale.x, transform.scale.y };

            bool collided = CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRec, &hitObj);

            if (collided) {
                TraceLog(LOG_INFO, "Collision detected at position (%f, %f)", nextPos.x, nextPos.y);
                // Vertical collision detection
                if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRec, &hitObj)) {
                    transform.translation.y = nextPos.y;
                } else {
                    physics.velocity.y = 0; // Stop vertical movement
                }
                
                // Horizontal collision only
                if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRec, &hitObj)) {
                    transform.translation.x = nextPos.x;
                } else {
                    physics.velocity.x = 0; // Stop horizontal movement
                }
            } else {
                // No collision: accept movement
                transform.translation = nextPos;
            }
        }); 
    });
}