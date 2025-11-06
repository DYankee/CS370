#include "health_upgrade_controller.hpp"
#include "../entities/health_upgrade.hpp"
#include "../components/player_stats.hpp"
#include "../components/health_pickup.hpp"

HealthUpgradeBehavior::HealthUpgradeBehavior(UpgradeUpdateFunction Update) {
    this->Update = Update;
}


void SpawnHealthUpgrades(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: SpawnHealthUpgrades");

    registry.view<Map, TmxMap>().each([&registry](TmxMap &map){

        TmxObjectGroup entitiesLayer = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;


        std::vector<TmxObject> healthObjects = FindObjectsByType(entitiesLayer.objects, entitiesLayer.objectsLength, "HealthUpgrade");
        TraceLog(LOG_INFO, "Found %zu health objects", healthObjects.size());

        for (TmxObject obj : healthObjects) {
            TraceLog(LOG_INFO, "Creating health upgrade at: %f,%f", float(obj.x), float(obj.y));
            CreateHealthUpgrade(registry, {float(obj.x), float(obj.y)});
        }
    });
}


void DeSpawnHealthUpgrades(entt::registry &registry){
    for (auto entity : registry.view<HealthUpgrade>()){
        registry.destroy(entity);
    }
}

void UpdateHealthUpgrades(entt::registry &registry, float dt){
    TraceLog(LOG_TRACE, "Entering function: UpdateHealthUpgrades");

    auto view = registry.view<HealthUpgrade, HealthUpgradeBehavior, Transform, PhysicsObject, SpriteData>();
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
