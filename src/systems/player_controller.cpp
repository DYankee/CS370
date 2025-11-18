#include "player_controller.hpp"
// Player movement system
void PlayerInputSystem(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: PlayerInputSystem");

    // Get the Transform and PhysicsObject from the Player Component
    registry.view<Transform, PhysicsObject, SpriteData, PlayerStats, Player, Animation>().each([dt, &registry](Transform &transform, PhysicsObject &physics, SpriteData &sprite, PlayerStats &stats, Animation &animation) {
        static float attackTimer;
        // Log player starting velocity
        TraceLog(LOG_INFO, "Player current velocity: %f,%f", physics.velocity.x, physics.velocity.y);

        // Apply gravity
        physics.velocity.y += stats.gravity * dt;
        
        // Check if currently jumping (jump animation is playing and not finished)
        bool isJumping = (animation.currentSequence == "jumpRight" || animation.currentSequence == "jumpLeft") && !animation.IsFinished();
        
        // Check if currently headbutting
        bool isHeadbutting = (animation.currentSequence == "headbuttRight" || animation.currentSequence == "headbuttLeft") && !animation.IsFinished();
        
        // Check if attacking and decrease timer
        if (stats.isAttacking) {
            attackTimer -= dt;
            if (attackTimer <= 0.0f) {
                stats.isAttacking = false;
                TraceLog(LOG_INFO, "Attack ended.");
            }
        }
        // If button pressed set attacking true and start headbutt animation
        if (IsKeyPressed(KEY_R) && !stats.isAttacking && !isJumping) {
            stats.isAttacking = true;
            attackTimer = 0.5f;  // Duration matches animation (5 frames * 0.1s = 0.5s)
            float lungePower = 1500.0f;
            TraceLog(LOG_INFO, "Player started attacking");
            
            // Play headbutt animation based on current direction
            if (animation.currentSequence == "walkLeft" || animation.currentSequence == "idleLeft" || 
                animation.currentSequence == "jumpLeft" || animation.currentSequence == "headbuttLeft") {
                TraceLog(LOG_INFO, "Setting cow sprite texture to: cowLHeadbutt");
                sprite.SetTexture("cowLHeadbutt");
                animation.PlaySequence("headbuttLeft");
                physics.velocity.x = -lungePower;
            } else {
                TraceLog(LOG_INFO, "Setting cow sprite texture to: cowRHeadbutt");
                sprite.SetTexture("cowRHeadbutt");
                animation.PlaySequence("headbuttRight");
                physics.velocity.x = lungePower;
            }
        }
        // Move box based on key input
        // Don't change animation if currently jumping or headbutting
        if (IsKeyDown(KEY_D) && !isHeadbutting) {
            physics.velocity.x = stats.speed;    // Move right
            if (!isJumping) {
                TraceLog(LOG_INFO, "Setting cow sprite texture to: cowRWalk");
                sprite.SetTexture("cowRWalk");
                animation.PlaySequence("walkRight");
            }
        } else if (IsKeyDown(KEY_A) && !isHeadbutting) {
            physics.velocity.x = -stats.speed;   // Move left
            if (!isJumping) {
                TraceLog(LOG_INFO, "Setting cow sprite texture to: cowLWalk");
                sprite.SetTexture("cowLWalk");
                animation.PlaySequence("walkLeft");
            }
        } else {
            physics.velocity.x = physics.velocity.x;        // No horizontal movement
            // Set idle animation based on last direction
            if (animation.currentSequence == "walkRight") {
                sprite.SetTexture("cowR");
                animation.PlaySequence("idleRight");
            } else if (animation.currentSequence == "walkLeft") {
                sprite.SetTexture("cowL");
                animation.PlaySequence("idleLeft");
            } else if (animation.currentSequence == "jumpRight" && animation.IsFinished()) {
                // Transition from jump to idle when jump animation finishes
                sprite.SetTexture("cowR");
                animation.PlaySequence("idleRight");
            } else if (animation.currentSequence == "jumpLeft" && animation.IsFinished()) {
                // Transition from jump to idle when jump animation finishes
                sprite.SetTexture("cowL");
                animation.PlaySequence("idleLeft");
            } else if (animation.currentSequence == "headbuttRight" && animation.IsFinished()) {
                // Transition from headbutt to idle when headbutt animation finishes
                sprite.SetTexture("cowR");
                animation.PlaySequence("idleRight");
            } else if (animation.currentSequence == "headbuttLeft" && animation.IsFinished()) {
                // Transition from headbutt to idle when headbutt animation finishes
                sprite.SetTexture("cowL");
                animation.PlaySequence("idleLeft");
            }
        }
        
        // Update animation
        animation.Update(dt);

        // Only allow jump if player is on the ground
        if (IsKeyPressed(KEY_SPACE)) {
            registry.view<TmxMap>().each([&transform, &physics, &sprite, &stats, &animation](TmxMap &map){{
                Rectangle testRec = { transform.translation.x, transform.translation.y + 1, transform.scale.x, transform.scale.y };
                TmxObject collidedObj;
                bool onGround = CheckCollisionTMXTileLayersRec(
                    &map, map.layers, map.layersLength, testRec, &collidedObj
                );
                if (onGround) {
                    physics.velocity.y = stats.jumpStrength;
                    PlaySound(stats.jumpSound);
                    // Play jump animation based on current direction
                    if (animation.currentSequence == "walkLeft" || animation.currentSequence == "idleLeft" || animation.currentSequence == "jumpLeft") {
                        TraceLog(LOG_INFO, "Setting cow sprite texture to: cowLJump");
                        sprite.SetTexture("cowLJump");
                        animation.PlaySequence("jumpLeft");
                    } else {
                        TraceLog(LOG_INFO, "Setting cow sprite texture to: cowRJump");
                        sprite.SetTexture("cowRJump");
                        animation.PlaySequence("jumpRight");
                    }
                }
            }});
        }

        // Log new velocity
        TraceLog(LOG_INFO, "Player new velocity: %f,%f", physics.velocity.x, physics.velocity.y);
    });

    // Update the players position
    auto players = registry.view<Player>();
    entt::entity player = players.front();

    //get reference to the map entity
    auto maps = registry.view<Map>();
    entt::entity mapEnt = maps.front();
    TmxMap& map = registry.get<TmxMap>(mapEnt); 

    // Get the Transform and PhysicsObject from the Player Component
    Transform &transform = registry.get<Transform>(player);
    PhysicsObject &physics = registry.get<PhysicsObject>(player);
    SpriteData &sprite = registry.get<SpriteData>(player);
    PlayerStats &stats = registry.get<PlayerStats>(player);
    Animation &animation = registry.get<Animation>(player);
        
    static float attackTimer;
    // Log player starting velocity
    TraceLog(LOG_INFO, "Player current velocity: %f,%f", physics.velocity.x, physics.velocity.y);

    // Apply gravity
    physics.velocity.y += stats.gravity * dt;
        
    // Check if currently jumping (jump animation is playing and not finished)
    bool isJumping = (animation.currentSequence == "jumpRight" || animation.currentSequence == "jumpLeft") && !animation.IsFinished();
        
    // Check if currently headbutting
    bool isHeadbutting = (animation.currentSequence == "headbuttRight" || animation.currentSequence == "headbuttLeft") && !animation.IsFinished();
        
    // Check if attacking and decrease timer
    if (stats.isAttacking) {
        attackTimer -= dt;
        if (attackTimer <= 0.0f) {
            stats.isAttacking = false;
            TraceLog(LOG_INFO, "Attack ended.");
        }
    }
    // If button pressed set attacking true and start headbutt animation
    if (IsKeyPressed(KEY_R) && !stats.isAttacking && !isJumping) {
        stats.isAttacking = true;
        attackTimer = 0.5f;  // Duration matches animation (5 frames * 0.1s = 0.5s)
        float lungePower = 1500.0f;
        TraceLog(LOG_INFO, "Player started attacking");
            
        // Play headbutt animation based on current direction
        if (animation.currentSequence == "walkLeft" || animation.currentSequence == "idleLeft" || 
            animation.currentSequence == "jumpLeft" || animation.currentSequence == "headbuttLeft") {
            TraceLog(LOG_INFO, "Setting cow sprite texture to: cowLHeadbutt");
            sprite.SetTexture("cowLHeadbutt");
            animation.PlaySequence("headbuttLeft");
            physics.velocity.x = -lungePower;
        } else {
            TraceLog(LOG_INFO, "Setting cow sprite texture to: cowRHeadbutt");
            sprite.SetTexture("cowRHeadbutt");
            animation.PlaySequence("headbuttRight");
            physics.velocity.x = lungePower;
        }
    }
    // Move box based on key input
    // Don't change animation if currently jumping or headbutting
    if (IsKeyDown(KEY_D) && !isHeadbutting) {
        physics.velocity.x = stats.speed;    // Move right
        if (!isJumping) {
            TraceLog(LOG_INFO, "Setting cow sprite texture to: cowRWalk");
            sprite.SetTexture("cowRWalk");
            animation.PlaySequence("walkRight");
        }
    } else if (IsKeyDown(KEY_A) && !isHeadbutting) {
        physics.velocity.x = -stats.speed;   // Move left
        if (!isJumping) {
            TraceLog(LOG_INFO, "Setting cow sprite texture to: cowLWalk");
            sprite.SetTexture("cowLWalk");
            animation.PlaySequence("walkLeft");
        }
    } else {
        physics.velocity.x = physics.velocity.x;        // No horizontal movement
        // Set idle animation based on last direction
        if (animation.currentSequence == "walkRight") {
            sprite.SetTexture("cowR");
            animation.PlaySequence("idleRight");
        } else if (animation.currentSequence == "walkLeft") {
            sprite.SetTexture("cowL");
            animation.PlaySequence("idleLeft");
        } else if (animation.currentSequence == "jumpRight" && animation.IsFinished()) {
            // Transition from jump to idle when jump animation finishes
            sprite.SetTexture("cowR");
            animation.PlaySequence("idleRight");
        } else if (animation.currentSequence == "jumpLeft" && animation.IsFinished()) {
            // Transition from jump to idle when jump animation finishes
            sprite.SetTexture("cowL");
            animation.PlaySequence("idleLeft");
        } else if (animation.currentSequence == "headbuttRight" && animation.IsFinished()) {
            // Transition from headbutt to idle when headbutt animation finishes
            sprite.SetTexture("cowR");
            animation.PlaySequence("idleRight");
        } else if (animation.currentSequence == "headbuttLeft" && animation.IsFinished()) {
            // Transition from headbutt to idle when headbutt animation finishes
            sprite.SetTexture("cowL");
            animation.PlaySequence("idleLeft");
        }
    }
        
    // Update animation
    animation.Update(dt);

    // Only allow jump if player is on the ground
    if (IsKeyPressed(KEY_SPACE)) {
        Rectangle testRec = { transform.translation.x, transform.translation.y + 1, transform.scale.x, transform.scale.y };
        TmxObject collidedObj;
        bool onGround = CheckCollisionTMXTileLayersRec(
            &map, map.layers, map.layersLength, testRec, &collidedObj
        );
        if (onGround) {
            physics.velocity.y += stats.jumpStrength;
            PlaySound(stats.jumpSound);
            // Play jump animation based on current direction
            if (animation.currentSequence == "walkLeft" || animation.currentSequence == "idleLeft" || animation.currentSequence == "jumpLeft") {
                TraceLog(LOG_INFO, "Setting cow sprite texture to: cowLJump");
                sprite.SetTexture("cowLJump");
                animation.PlaySequence("jumpLeft");
            } else {
                TraceLog(LOG_INFO, "Setting cow sprite texture to: cowRJump");
                sprite.SetTexture("cowRJump");
                animation.PlaySequence("jumpRight");
            }
        }
    }

    // Log new velocity
    TraceLog(LOG_INFO, "Player new velocity: %f,%f", physics.velocity.x, physics.velocity.y);

    if (player != entt::null){
        MovePlayer(registry, dt, player);
    }
}

void MovePlayer(entt::registry &registry, float dt, entt::entity entity){
    TraceLog(LOG_TRACE, "Entering Function: MovePlayer: ");

    registry.view<Map, TmxMap>().each([&registry, &entity, dt](TmxMap &map) {

        // Get entity components
        auto &transform = registry.get<Transform>(entity);
        auto &physics = registry.get<PhysicsObject>(entity);
        TraceLog(LOG_INFO, "MovePlayer: Player starting pos(%f,%f), vel(%f,%f)", 
            transform.translation.x, transform.translation.y,
            physics.velocity.x, physics.velocity.y
        );

        // Handle X Axis Movement & Collision
        float originalX = transform.translation.x;
        transform.translation.x += physics.velocity.x * dt;
        TraceLog(LOG_INFO, "MovePlayer: Player x destination pos(%f,%f), vel(%f,%f)", 
            transform.translation.x, transform.translation.y,
            physics.velocity.x, physics.velocity.y
        );

        Rectangle entityRectX = { 
            transform.translation.x, 
            transform.translation.y, 
            transform.scale.x, 
            transform.scale.y 
        };
        TmxObject hitObjX;
        if (CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, entityRectX, &hitObjX)) {
            TraceLog(LOG_INFO, "MovePlayer: X Axis Collision");
            
            // Determine direction based on velocity
            if (physics.velocity.x > 0) {
                // Moving Right - Snap to left side of object
                transform.translation.x = hitObjX.x - transform.scale.x;
                physics.velocity.x = 0;
            } else if (physics.velocity.x < 0) {
                // Moving Left - Snap to right side of object
                transform.translation.x = hitObjX.x + hitObjX.width;
                physics.velocity.x = 0;
            }
        }
        TraceLog(LOG_INFO, "MovePlayer: Player x after col pos(%f,%f), vel(%f,%f)", 
            transform.translation.x, transform.translation.y,
            physics.velocity.x, physics.velocity.y
        );

        // Handle Y Axis Movement & Collision
        float originalY = transform.translation.y;
        transform.translation.y += physics.velocity.y * dt;
        TraceLog(LOG_INFO, "MovePlayer: Player y destination pos(%f,%f), vel(%f,%f)", 
            transform.translation.x, transform.translation.y,
            physics.velocity.x, physics.velocity.y
        );

        Rectangle entityRectY = { 
            transform.translation.x, 
            transform.translation.y, 
            transform.scale.x, 
            transform.scale.y 
        };
        TmxObject hitObjY;
        if (CheckCollisionTMXTileLayersRec(&map, map.layers, map.layersLength, entityRectY, &hitObjY)) {
            TraceLog(LOG_INFO, "MovePlayer: Y Axis Collision");

            if (physics.velocity.y > 0) {
                // Falling Down - Snap to top of object (Floor)
                transform.translation.y = hitObjY.y - transform.scale.y;
            } else if (physics.velocity.y < 0) {
                // Jumping Up - Snap to bottom of object (Ceiling)
                transform.translation.y = hitObjY.y + hitObjY.height;
            }
            // Kill Y momentum on impact
            physics.velocity.y = 0;

            // Slow x momentum while on floor/ceiling
            physics.velocity.x -= physics.velocity.x / 5;
        }
        TraceLog(LOG_INFO, "MovePlayer: Player after y col pos(%f,%f), vel(%f,%f)", 
            transform.translation.x, transform.translation.y,
            physics.velocity.x, physics.velocity.y
        );

        // Log final pos
        TraceLog(LOG_INFO, "MovePlayer: Player final pos(%f,%f), vel(%f,%f)", 
            transform.translation.x, transform.translation.y,
            physics.velocity.x, physics.velocity.y
        );
    });
}
