#include "collision_system.hpp" //find an object/group layer by name

static TmxLayer* FindLayerByName(TmxLayer* layers, int layersLength, const char* name) {
    if (!layers || layersLength == 0 || !name){
         return NULL;
    }
    for (int i = 0; i < layersLength; ++i) {
        if (layers[i].name && strcmp(layers[i].name, name) == 0) return &layers[i];
        if (layers[i].type == LAYER_TYPE_GROUP && layers[i].layersLength > 0) {
            TmxLayer* found = FindLayerByName(layers[i].layers, layers[i].layersLength, name);
            if (found) return found;
        }
    }
    return NULL;
}

void SpikeCollision(entt::registry &registry, float dt) {
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
                            physics.velocity.x = -300.0f;
                        } else {              
                            physics.velocity.x = 300.0f;
                        }
                        physics.velocity.y = 400.0f; // Upward knockback

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
    registry.view<Player, PhysicsObject, Transform>().each([dt, &registry](PhysicsObject &physics, Transform &transform) {
        registry.view<Map, TmxMap>().each([&physics, &transform, dt](TmxMap &map) {
            TmxObject hitObj;
            
            // Calculate next position
            Vector3 nextPos = {
                transform.translation.x + physics.velocity.x * dt,
                transform.translation.y + physics.velocity.y * dt,
                transform.translation.z
            };
            Rectangle playerDestRec = { nextPos.x, nextPos.y, transform.scale.x, transform.scale.y };

            bool collided = CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRec, &hitObj);

            if (collided) {
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