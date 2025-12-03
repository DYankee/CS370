#include "upgrade_controller.hpp"
#include "../entities/upgrade.hpp"
#include "../components/player_stats.hpp"
#include "../components/health_pickup.hpp"

UpgradeBehavior::UpgradeBehavior(UpgradeUpdateFunction Update) {
    this->Update = Update;
}


void SpawnUpgrades(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: SpawnUpgrades");

    registry.view<Map, TmxMap>().each([&registry](TmxMap &map){

        TmxObjectGroup entitiesLayer = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;


        std::vector<TmxObject> upgradeObjects = FindObjectsByType(entitiesLayer.objects, entitiesLayer.objectsLength, "Upgrade");
        TraceLog(LOG_INFO, "Found %zu upgrade objects", upgradeObjects.size());

        for (TmxObject obj : upgradeObjects) {
            TraceLog(LOG_INFO, "Creating upgrade at: %f,%f", float(obj.x), float(obj.y));
            CreateUpgrade(registry, {float(obj.x), float(obj.y)});
        }
    });
}


void DespawnUpgrades(entt::registry &registry){
    for (auto entity : registry.view<Upgrade>()){
        registry.destroy(entity);
    }
}

void UpdateUpgrades(entt::registry &registry, float dt){
    TraceLog(LOG_TRACE, "Entering function: UpdateUpgrades");

    auto view = registry.view<Upgrade, UpgradeBehavior, Transform, PhysicsObject, SpriteData>();
    for (auto ent : view){

        HealthUpgradeBehavior &behavior = registry.get<HealthUpgradeBehavior>(ent);
        Transform &transform = registry.get<Transform>(ent);
        PhysicsObject &physics = registry.get<PhysicsObject>(ent);


        behavior.Update(registry, dt, ent);

        // move
        transform.translation.x += physics.velocity.x * dt;
        transform.translation.y += physics.velocity.y * dt;
    }
}