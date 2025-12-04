#include "range_upgrade.hpp"
#include "../components/components.hpp"
#include "../components/player_stats.hpp"
#include "../entities/entities.hpp"
#include "../include/raylib.h"

void CreateRangeUpgrade(entt::registry &registry, Vector2 position) {
    TraceLog(LOG_TRACE, "Entering Function: CreateRangeUpgrade");
    TraceLog(LOG_INFO, "Creating Range Upgrade Entity");

    // add to the registry
    entt::entity rangeUpgradeEnt = registry.create();


    RangeUpgrade rangeComp;
    registry.emplace<RangeUpgrade>(rangeUpgradeEnt, rangeComp);

    // add sprite
    SpriteData sprite = SpriteData(LoadTextures({{"Milk", "assets/sprites/powerups/MilkCarton.png"}}), WHITE);
    sprite.SetTexture("Milk");
    registry.emplace<SpriteData>(rangeUpgradeEnt, sprite);

    Transform trans = Transform{{position.x, position.y, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {32, 32}};
    registry.emplace<Transform>(rangeUpgradeEnt, trans);


    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(rangeUpgradeEnt, physics);

    registry.emplace<Vector2>(rangeUpgradeEnt, position);

}
