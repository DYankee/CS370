#include "projectile.hpp"

void CreateProjectile(entt:: registry& registry, Transform startPos, Vector3 targetPos, ProjectileStats stats, bool fromPlayer){
    TraceLog(LOG_TRACE, "Entering function: Create projectile");

    entt::entity projectile = registry.create();
    
    // Add tag struct
    registry.emplace<Projectile>(projectile, Projectile{fromPlayer});
    
    // Load projectile sprites
    SpriteData sprite = SpriteData(LoadTextures({
            {"ProjectileL", "assets/sprites/enemies/alien/AlienGunProjectileL.png"},
            {"ProjectileR", "assets/sprites/enemies/alien/AlienGunProjectileR.png"},
            {"PlayerProjectile", "assets/sprites/powerups/MilkCarton.png"}
        }),
        WHITE
    );
    if(!fromPlayer){
    if (startPos.translation.x < targetPos.x){
        sprite.SetTexture("ProjectileR");
    }
    else {
        sprite.SetTexture("ProjectileL");
    }
}
    else if (fromPlayer){
        sprite.SetTexture("PlayerProjectile");
    }
          Vector3 vec;
if (fromPlayer) {
    vec.x = targetPos.x - startPos.translation.x;
    vec.y = targetPos.y - startPos.translation.y;
    vec.z = 0;

    float length = sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length != 0) {
        vec.x /= length;
        vec.y /= length;
    }

    const float projectileSpeed = 800.0f;
    vec.x *= projectileSpeed;
    vec.y *= projectileSpeed;
} else {
    vec = targetPos;
}
    // Add SpriteData component to the entity
    registry.emplace<SpriteData>(projectile, sprite);
    
    // Set start pos
    startPos.scale.x = sprite.srcRec.width;
    startPos.scale.y = sprite.srcRec.height;
    registry.emplace<Transform>(projectile, startPos);

    // Set Direction
    registry.emplace<Vector3>(projectile, vec);

    // Set Stats
    registry.emplace<ProjectileStats>(projectile, stats);
}
