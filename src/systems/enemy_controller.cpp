#include "enemy_controller.hpp"

// Function to find enemy spawn point and spawn the designated enemy at them
void SpawnEnemies(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: SpawnEnemies");
    registry.view<Map, TmxMap>().each([&registry](TmxMap &map){
        //get the entities group from the map
        TmxObjectGroup entities = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;
        // Get the enemySpawns form the entities list
        std::vector<TmxObject> enemies = FindObjectsByType(entities.objects, entities.objectsLength, "Enemy");
        //loop through entity spawn
        for (TmxObject enemy : enemies){
            TraceLog(LOG_INFO, "Creating enemy at: %f,%f", float(enemy.x), float(enemy.y));
            CreateEnemy(registry, enemy);
        }
    });
}

void DeSpawnEnemies(entt::registry &registry){
    for (const auto entity : registry.view<Enemy>()){
        registry.destroy(entity);
    }
}

void UpdateEnemies(entt::registry &registry, float dt){
    TraceLog(LOG_TRACE, "Entering function: UpdateEnemies");

    auto view = registry.view<Enemy>();
    for (auto enemy :view){
        // Get the update function from the entity
        Enemy_behavior update = registry.get<Enemy_behavior>(enemy);

        // Call the function with the entity as an argument
        update.Update(registry, dt, enemy);
    }
}