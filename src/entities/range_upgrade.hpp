#ifndef RANGE_UPGRADE_HPP
#define RANGE_UPGRADE_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../components/components.hpp"
#include "../components/physics_object.hpp"


struct RangeUpgrade {};

struct RangeUpgradeStats {
    int rangeValue = 1;
};


typedef void (*UpgradeUpdateFunction)(entt::registry&, float, entt::entity);


struct RangeUpgradeBehavior {
    UpgradeUpdateFunction Update;
    RangeUpgradeBehavior() = default;
    RangeUpgradeBehavior(UpgradeUpdateFunction Update);
};

// Functions
void CreateRangeUpgrade(entt::registry &registry, Vector2 position);
void FloatUpgrade(entt::registry &registry, float dt, entt::entity upgrade);

#endif
