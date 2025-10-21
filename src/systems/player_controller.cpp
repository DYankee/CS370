#include "player_controller.hpp"
// Player movement system
void PlayerInputSystem(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: PlayerInputSystem");

    // Get the Transform and PhysicsObject from the Player Component
    registry.view<Transform, PhysicsObject, SpriteData, PlayerStats, Player>().each([dt, &registry](Transform &transform, PhysicsObject &physics, SpriteData &sprite, PlayerStats &stats) {
        
        // Log player starting velocity
        TraceLog(LOG_INFO, "Player current velocity: %f,%f", physics.velocity.x, physics.velocity.y);

        // Apply gravity
        physics.velocity.y += stats.gravity * dt;
        
        // Move box based on key input
        if (IsKeyDown(KEY_D)) {
            physics.velocity.x = stats.speed;    // Move right
            TraceLog(LOG_INFO, "Setting cow sprite texture to: cowR");
            sprite.SetTexture("cowR");
        } else if (IsKeyDown(KEY_A)) {
            physics.velocity.x = -stats.speed;   // Move left
            TraceLog(LOG_INFO, "Setting cow sprite texture to: cowL");
            sprite.SetTexture("cowL");
        } else {
            physics.velocity.x = physics.velocity.x;        // No horizontal movement
        }

        // Only allow jump if player is on the ground
        if (IsKeyPressed(KEY_SPACE)) {
            registry.view<TmxMap>().each([&transform, &physics, &sprite, &stats](TmxMap &map){{
                Rectangle testRec = { transform.translation.x, transform.translation.y + 1, transform.scale.x, transform.scale.y };
                TmxObject collidedObj;
                bool onGround = CheckCollisionTMXTileLayersRec(
                    &map, map.layers, map.layersLength, testRec, &collidedObj
                );
                if (onGround) {
                    physics.velocity.y = stats.jumpStrength;
                }
            }});
        }

        // Log new velocity
        TraceLog(LOG_INFO, "Player new velocity: %f,%f", physics.velocity.x, physics.velocity.y);
    });
}

void MovePlayer(entt::registry &registry, float dt){
    TraceLog(LOG_TRACE, "Entering Function: MovePlayer");

    registry.view<Player, Transform, PhysicsObject>().each([&registry, dt](Transform &transform, PhysicsObject &physics){
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
            TraceLog(LOG_INFO, "Player Destination Pos: %f,%f", nextPos.x, nextPos.y);

            Rectangle playerDestRec = { nextPos.x, nextPos.y, transform.scale.x, transform.scale.y };
            Rectangle playerDestRecX = { nextPos.x, transform.translation.y, transform.scale.x, transform.scale.y };
            Rectangle playerDestRecY = { transform.translation.x, nextPos.y, transform.scale.x, transform.scale.y };

            bool collided = CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRec, &hitObj);

            if (collided) {
                TraceLog(LOG_INFO, "Collision detected at position (%f, %f)", nextPos.x, nextPos.y);
                // Vertical collision detection
                if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRecY, &hitObj)) {
                    transform.translation.y = nextPos.y;
                } else {
                    physics.velocity.y = 0; // Stop vertical movement
                }
                
                // Horizontal collision only
                if (!CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, playerDestRecX, &hitObj)) {
                    transform.translation.x = nextPos.x;
                    physics.velocity.x -= physics.velocity.x / 2;
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