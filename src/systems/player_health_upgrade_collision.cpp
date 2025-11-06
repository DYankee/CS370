#include "player_health_upgrade_collision.hpp"
#include "../components/player_stats.hpp"
#include "../entities/health_upgrade.hpp"
#include "../include/entt.hpp"
#include "../include/raylib.h"

void PlayerHealthCollisionSystem(entt::registry &registry, float dt) {
registry.view<PlayerStats, Transform, PhysicsObject>().each(
[&registry](auto playerEntity, PlayerStats &playerStats, Transform &playerTransform, PhysicsObject &physics) {

        auto pickupView = registry.view<HealthUpgrade, Transform>();  
       for (auto pickupEntity : pickupView) {
    auto &pickupTransform = pickupView.get<Transform>(pickupEntity);

    bool collisionX = playerTransform.translation.x + playerTransform.scale.x > pickupTransform.translation.x &&
                      playerTransform.translation.x < pickupTransform.translation.x + pickupTransform.scale.x;

    bool collisionY = playerTransform.translation.y + playerTransform.scale.y > pickupTransform.translation.y &&
                      playerTransform.translation.y < pickupTransform.translation.y + pickupTransform.scale.y;

    if (collisionX && collisionY) {
 

        playerStats.maxHealth += 1;
        playerStats.health = playerStats.maxHealth;

        registry.destroy(pickupEntity);
    }
}

    }  
);  


}
