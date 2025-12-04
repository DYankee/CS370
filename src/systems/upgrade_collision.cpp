#include "upgrade_collision.hpp"
#include "../components/player_stats.hpp"
#include "../entities/upgrade.hpp"
#include "../include/entt.hpp"
#include "../include/raylib.h"

void UpgradeCollisionSystem(entt::registry &registry, float dt) {
registry.view<PlayerStats, PlayerUpgrades, Transform, PhysicsObject>().each(
[&registry](auto playerEntity, PlayerStats &playerStats, PlayerUpgrades &playerUpgrades, Transform &playerTransform, PhysicsObject &physics) {

    auto pickupView = registry.view<Upgrade, Transform, TmxObject>();  
    for (auto pickupEntity : pickupView) {
    auto &pickupTransform = pickupView.get<Transform>(pickupEntity);

    bool collisionX = playerTransform.translation.x + playerTransform.scale.x > pickupTransform.translation.x &&
                      playerTransform.translation.x < pickupTransform.translation.x + pickupTransform.scale.x;

    bool collisionY = playerTransform.translation.y + playerTransform.scale.y > pickupTransform.translation.y &&
                      playerTransform.translation.y < pickupTransform.translation.y + pickupTransform.scale.y;

    auto &info = pickupView.get<TmxObject>(pickupEntity);
    std::string name = info.name;

    if (collisionX && collisionY) {
        
        if(name == "TestUpgrade") {
            playerUpgrades.testUpgrade = true;
        }

        registry.destroy(pickupEntity);
    }
}
}
);  
}