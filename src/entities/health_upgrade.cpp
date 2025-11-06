#include "health_upgrade.hpp"
#include "../components/components.hpp"
#include "../components/player_stats.hpp"
#include "../entities/entities.hpp"
#include "../include/raylib.h"

void CreateHealthUpgrade(entt::registry &registry, Vector2 position) {
    TraceLog(LOG_TRACE, "Entering Function: CreateHealthUpgrade");
    TraceLog(LOG_INFO, "Creating Health Upgrade Entity");

    // add to the registry
    entt::entity upgradeEnt = registry.create();


    HealthUpgrade healthComp;
    registry.emplace<HealthUpgrade>(upgradeEnt, healthComp);

    // add sprite
    SpriteData sprite = SpriteData(LoadTextures({{"Heart", "assets/sprites/CowFace.png"}}), WHITE);
    sprite.SetTexture("Heart");
    registry.emplace<SpriteData>(upgradeEnt, sprite);

    Transform trans = Transform{{position.x, position.y, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32}};
    registry.emplace<Transform>(upgradeEnt, trans);


    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(upgradeEnt, physics);

    registry.emplace<Vector2>(upgradeEnt, position);

}
