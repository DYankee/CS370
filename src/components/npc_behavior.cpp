#include "npc_behavior.hpp"
#include "sprite_data.hpp"

void NPCUpdate(entt::registry & registry, float dt, entt::entity npc){
    TraceLog(LOG_TRACE, "Entering Function NPCUpdate");
    
    // Get player position
    auto players = registry.view<Player>();
    entt::entity player = players.front();
    auto& playerPos = registry.get<Transform>(player);

    // Get components from NPC entity
    auto& pos = registry.get<Transform>(npc);
    auto& physics = registry.get<PhysicsObject>(npc);
    auto& stats = registry.get<EnemyStats>(npc);
    auto& sprite = registry.get<SpriteData>(npc);

    // Check spawn pause timer
    if (stats.spawnPauseTimer > 0) {
        stats.spawnPauseTimer -= dt;
        physics.velocity.x = 0; // Keep horizontal velocity at 0 during pause
        physics.velocity.y += GRAVITY * dt; // Still apply gravity
        MoveEntity(registry, dt, npc);
        return; // Skip rest of update during spawn pause
    }

    // Apply gravity
    physics.velocity.y += GRAVITY * dt;

    // Make NPC face player by updating direction
    if(playerPos.translation.x < pos.translation.x){
        if(stats.CurrentDirection != LEFT){
            stats.CurrentDirection = LEFT;
            // Update sprite - iterate through texture names to find the left version
            for(auto& [name, texture] : sprite.textures){
                if(name.back() == 'L'){
                    sprite.SetTexture(name);
                    break;
                }
            }
        }
    }
    else {
        if(stats.CurrentDirection != RIGHT){
            stats.CurrentDirection = RIGHT;
            // Update sprite - iterate through texture names to find the right version
            for(auto& [name, texture] : sprite.textures){
                if(name.back() == 'R'){
                    sprite.SetTexture(name);
                    break;
                }
            }
        }
    }
    
    // Move entity with physics
    MoveEntity(registry, dt, npc);
}

NPC_behavior::NPC_behavior(NPCUpdateFunction Update){
    this->Update = Update;
}
