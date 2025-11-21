#include "projectile.hpp"

void CreateProjectile(entt:: registry& registry, Transform startPos, Vector3 targetPos, ProjectileStats stats){
    TraceLog(LOG_TRACE, "Entering function: Create projectile");

    entt::entity projectile = registry.create();
    
    // Add tag struct
    registry.emplace<Projectile>(projectile, Projectile{});
    
    // Load projectile sprites
    SpriteData sprite = SpriteData(LoadTextures({
            {"base", "assets/sprites/powerups/MilkCarton.png"},
        }),
        WHITE
    );
    sprite.SetTexture("base");
    // Add SpriteData component to the entity
    registry.emplace<SpriteData>(projectile, sprite);
    
    // Set start pos
    startPos.scale.x = sprite.srcRec.width;
    startPos.scale.y = sprite.srcRec.height;
    registry.emplace<Transform>(projectile, startPos);

    // Set Direction
    registry.emplace<Vector3>(projectile, targetPos);

    // Set Stats
    registry.emplace<ProjectileStats>(projectile, stats);
}
