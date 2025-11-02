#include "enemy_controller.hpp"

// Function to find enemy spawn point and spawn the designated enemy at them
void SpawnEnemies(entt::registry &registry){
    registry.view<Map, TmxMap>().each([&registry](TmxMap &map){
        //get the entities group from the map
        TmxObjectGroup entities = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;
        // Get the enemySpawns form the entities list
        std::vector<TmxObject> enemySpawns = FindObjectsByType(entities.objects, entities.objectsLength, "Enemy");
        
        //loop through entity spawn
        for (TmxObject spawn : enemySpawns){
            CreateEnemy(registry, Vector2{float(spawn.x), float(spawn.y)});
        }
    });
}

void DeSpawnEnemies(entt::registry &registry){
    for (const auto entity : registry.view<Enemy>()){
        registry.destroy(entity);
    }
}