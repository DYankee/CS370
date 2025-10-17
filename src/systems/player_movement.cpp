#include "player_movement.hpp"
// Player movement system
void PlayerMovementSystem(entt::registry &registry, float dt) {

    // Get the Transform and PhysicsObject from the Player Component
    registry.view<Transform, PhysicsObject, SpriteData, PlayerStats, Player>().each([dt, &registry](Transform &transform, PhysicsObject &physics, SpriteData &sprite, PlayerStats &stats) {

        transform.translation.y += stats.gravity * dt;
        // Move box based on key input
        if (IsKeyDown(KEY_D)) {
            physics.velocity.x = stats.speed;    // Move right
            sprite.SetTexture("cowR");
        } else if (IsKeyDown(KEY_A)) {
            physics.velocity.x = -stats.speed;   // Move left
            sprite.SetTexture("cowL");
        } else {
            physics.velocity.x = 0;        // No horizontal movement
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
        // Calculate new position
        transform.translation.x += physics.velocity.x * dt;
        transform.translation.y += physics.velocity.y * dt;
    });
}