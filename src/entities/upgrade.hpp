#ifndef UPGRADE_HPP
#define UPGRADE_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../components/components.hpp"
#include "../components/physics_object.hpp"
#include "../../include/raytmx.h"


struct HealthUpgrade {};

struct Upgrade {};

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

void CreateUpgrade(entt::registry &registry, TmxObject UpgradeInfo);

#endif
