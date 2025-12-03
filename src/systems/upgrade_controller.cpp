#include "upgrade_controller.hpp"
#include "../entities/upgrade.hpp"
#include "../components/player_stats.hpp"
#include "../components/health_pickup.hpp"

void SpawnUpgrades(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: SpawnUpgrades");

    registry.view<Map, TmxMap>().each([&registry](TmxMap &map){

        TmxObjectGroup entitiesLayer = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;


        std::vector<TmxObject> upgradeObjects = FindObjectsByType(entitiesLayer.objects, entitiesLayer.objectsLength, "Upgrade");
        TraceLog(LOG_INFO, "Found %zu upgrade objects", upgradeObjects.size());

        for (TmxObject obj : upgradeObjects) {
            TraceLog(LOG_INFO, "Creating upgrade at: %f,%f", float(obj.x), float(obj.y));
            CreateUpgrade(registry, obj);
        }
    });
}


void DespawnUpgrades(entt::registry &registry){
    for (auto entity : registry.view<Upgrade>()){
        registry.destroy(entity);
    }
}

