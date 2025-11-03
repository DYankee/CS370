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
void MoveEntity(entt::registry& registry, float dt, entt::entity entity){
    TraceLog(LOG_TRACE, "Entering Function: MoveEntity");
    registry.view<Map, TmxMap>().each([&registry, &entity, dt](TmxMap &map) {
        TmxObject hitObj;

        // Get entity components
        auto [pos, physics] = registry.get<Transform, PhysicsObject>(entity);

        // Log current pos
        TraceLog(LOG_INFO, "Player Current Pos: %f,%f", pos.translation.x, pos.translation.y);


        // Calculate next position
        Vector3 nextPos = {
            pos.translation.x + physics.velocity.x * dt,
            pos.translation.y + physics.velocity.y * dt,
            pos.translation.z
        };
        Rectangle playerDestRec = { nextPos.x, nextPos.y, pos.scale.x, pos.scale.y };
        Rectangle playerDestRecX = { nextPos.x, pos.translation.y, pos.scale.x, pos.scale.y };
        Rectangle playerDestRecY = { pos.translation.x, nextPos.y, pos.scale.x, pos.scale.y };
        // Log new Pos
        TraceLog(LOG_INFO, "Player Current Pos: %f,%f", nextPos.x, nextPos.y);

        bool collided = CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRec, &hitObj);

        if (collided) {
            TraceLog(LOG_INFO, "Collision detected at position (%f, %f)", nextPos.x, nextPos.y);
            // Vertical collision detection
            if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRecY, &hitObj)) {
                pos.translation.y = nextPos.y;
            } else {
                physics.velocity.y = 0; // Stop vertical movement
            }

            // Horizontal collision only
            if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRecX, &hitObj)) {
                pos.translation.x = nextPos.x;
            } else {
                physics.velocity.x = 0; // Stop horizontal movement
            }
        } 
        else {
            // No collision: accept movement
            pos.translation = nextPos;
        }
    }); 
}