#include "projectile_manager.hpp"
#include "../components/components.hpp"


void UpdateProjectiles(entt::registry &registry, float dt){
    registry.view<Projectile, Transform, Vector3, ProjectileStats>().each(
        [dt, &registry](Transform &pos, Vector3 &targetPos, ProjectileStats &stats) {
        
        // Calculate the direction vector from the current position to the target position
        float dx = targetPos.x - pos.translation.x;
        float dy = targetPos.y - pos.translation.y;

        // Calculate the squared distance to the target
        float distanceSquared = (dx * dx) + (dy * dy);

        // Check if the projectile is already at or very close to the target
        // Using a small epsilon to account for floating point inaccuracies
        if (distanceSquared < 0.001f) {
            pos.translation.x = targetPos.x; // Snap to target
            pos.translation.y = targetPos.y; // Snap to target
            // Projectile has reached its target, you might want to consider
            // despawning it or triggering an event here.
            return;
        }

        float distance = std::sqrt(distanceSquared);

        // Normalize the direction vector
        // This gives a unit vector pointing from pos to targetPos
        float invDistance = 1.0f / distance;
        float normalizedDirX = dx * invDistance;
        float normalizedDirY = dy * invDistance;

        // Calculate the maximum distance the projectile can travel this frame
        float travelDistance = stats.Speed * dt;

        // Ensure the projectile doesn't overshoot the target
        if (travelDistance > distance) {
            // If the calculated travel distance is greater than the remaining distance,
            // move directly to the target position.
            pos.translation.x = targetPos.x;
            pos.translation.y = targetPos.y;
            // Again, consider despawning or marking for removal here.
        } else {
            // Otherwise, move the projectile towards the target by the calculated travelDistance
            pos.translation.x += normalizedDirX * travelDistance;
            pos.translation.y += normalizedDirY * travelDistance;
        }
    });
}