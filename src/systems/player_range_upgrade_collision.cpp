#include "player_range_upgrade_collision.hpp"
#include "../components/player_stats.hpp"
#include "../entities/range_upgrade.hpp"
#include "../include/entt.hpp"
#include "../include/raylib.h"

void PlayerRangeCollisionSystem(entt::registry &registry, float dt) {
registry.view<PlayerStats, Transform, PhysicsObject>().each(
[&registry](auto playerEntity, PlayerStats &playerStats, Transform &playerTransform, PhysicsObject &physics) {

        auto pickupView = registry.view<RangeUpgrade, Transform>();  
       for (auto pickupEntity : pickupView) {
    auto &pickupTransform = pickupView.get<Transform>(pickupEntity);

    bool collisionX = playerTransform.translation.x + playerTransform.scale.x > pickupTransform.translation.x &&
                      playerTransform.translation.x < pickupTransform.translation.x + pickupTransform.scale.x;

    bool collisionY = playerTransform.translation.y + playerTransform.scale.y > pickupTransform.translation.y &&
                      playerTransform.translation.y < pickupTransform.translation.y + pickupTransform.scale.y;

    if (collisionX && collisionY) {
 

        playerStats.hasRanged = true;

        registry.destroy(pickupEntity);
    }
}

    }  
);  


}
