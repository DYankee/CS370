#ifndef HEALTH_UPGRADE_HPP
#define HEALTH_UPGRADE_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../components/components.hpp"
#include "../components/physics_object.hpp"


struct HealthUpgrade {};

struct HealthUpgradeStats {
    int healthValue = 1;
};


typedef void (*UpgradeUpdateFunction)(entt::registry&, float, entt::entity);


struct HealthUpgradeBehavior {
    UpgradeUpdateFunction Update;
    HealthUpgradeBehavior() = default;
    HealthUpgradeBehavior(UpgradeUpdateFunction Update);
};

// Functions
void CreateHealthUpgrade(entt::registry &registry, Vector2 position);
void FloatUpgrade(entt::registry &registry, float dt, entt::entity upgrade);

#endif
