#include "enemy_controller.hpp"

// Function to find enemy spawn point and spawn the designated enemy at them
void SpawnEnemies(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: SpawnEnemies");
    registry.view<Map, TmxMap>().each([&registry](TmxMap &map){
        //get the entities group from the map
        TmxObjectGroup entities = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;
        // Get the enemySpawns form the entities list
        std::vector<TmxObject> enemySpawns = FindObjectsByType(entities.objects, entities.objectsLength, "Enemy");
        

        //loop through entity spawn
        for (TmxObject spawn : enemySpawns){
            TraceLog(LOG_INFO, "Creating enemy at: %f,%f", float(spawn.x), float(spawn.y));
            CreateEnemy(registry, Vector2{float(spawn.x), float(spawn.y)});
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
    registry.view<Enemy, Enemy_behavior, EnemyStats, Transform>().each([&registry, dt](
        Enemy_behavior &update,
        EnemyStats &stats,
        Transform &pos)
    {
        update.Update(registry, dt, stats, pos);
    });
}