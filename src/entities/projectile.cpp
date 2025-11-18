#include "projectile.hpp"
#include "../components/components.hpp"

void CreateProjectile(entt:: registry registry, Transform startPos, Vector2 direction, ProjectileStats stats){
    TraceLog(LOG_TRACE, "Entering function: Create projectile");

    entt::entity projectile = registry.create();
    
    // Add tag struct
    registry.emplace<Projectile>(projectile, Projectile{});

    // Set start pos
    registry.emplace<Transform>(projectile, startPos);

    // Set Direction
    registry.emplace<Vector2>(projectile, direction);

    // Set Stats
    registry.emplace<ProjectileStats>(projectile, stats);
}
