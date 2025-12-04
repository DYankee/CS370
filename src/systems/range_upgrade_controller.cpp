#include "range_upgrade_controller.hpp"
#include "../entities/range_upgrade.hpp"
#include "../components/player_stats.hpp"
#include "../components/range_pickup.hpp"

RangeUpgradeBehavior::RangeUpgradeBehavior(UpgradeUpdateFunction Update) {
    this->Update = Update;
}


void SpawnRangeUpgrades(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: SpawnRangeUpgrades");

    registry.view<Map, TmxMap>().each([&registry](TmxMap &map){

        TmxObjectGroup entitiesLayer = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;


        std::vector<TmxObject> rangeObjects = FindObjectsByType(entitiesLayer.objects, entitiesLayer.objectsLength, "RangeUpgrade");
        TraceLog(LOG_INFO, "Found %zu range objects", rangeObjects.size());

        for (TmxObject obj : rangeObjects) {
            TraceLog(LOG_INFO, "Creating range upgrade at: %f,%f", float(obj.x), float(obj.y));
            CreateRangeUpgrade(registry, {float(obj.x), float(obj.y)});
        }
    });
}


void DeSpawnRangeUpgrades(entt::registry &registry){
    for (auto entity : registry.view<RangeUpgrade>()){
        registry.destroy(entity);
    }
}

void UpdateRangeUpgrades(entt::registry &registry, float dt){
    TraceLog(LOG_TRACE, "Entering function: UpdateRangeUpgrades");

    auto view = registry.view<RangeUpgrade, RangeUpgradeBehavior, Transform, PhysicsObject, SpriteData>();
    for (auto ent : view){

        RangeUpgradeBehavior &behavior = registry.get<RangeUpgradeBehavior>(ent);
        Transform &transform = registry.get<Transform>(ent);
        PhysicsObject &physics = registry.get<PhysicsObject>(ent);


        behavior.Update(registry, dt, ent);

        // move
        transform.translation.x += physics.velocity.x * dt;
        transform.translation.y += physics.velocity.y * dt;
    }
}
