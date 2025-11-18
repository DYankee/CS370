#include "projectile_manager.hpp"
#include "../components/components.hpp"


void UpdateProjectiles(entt::registry &registry, float dt){
    registry.view<Projectile, Transform, Vector2, ProjectileStats>().each([dt, &registry](
    Transform &pos,
    Vector2 &direction,
    ProjectileStats &stats){
        
    });
}