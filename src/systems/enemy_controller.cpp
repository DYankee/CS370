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

            EnemyType type = GetEnemyType(enemy);
            switch (type){
                case NONE: {
                    TraceLog(LOG_ERROR, "Enemy type not found!");
                    break;
                }
                case FARMER: {
                    TraceLog(LOG_INFO, "Creating Farmer enemy");
                    CreateFarmer(registry, enemy);
                    break;
                }
                case ALIEN: {
                    TraceLog(LOG_INFO, "Creating Alien enemy");
                    CreateAlien(registry, enemy);
                    break;
                }
            }
        }
    });
}

EnemyType GetEnemyType(TmxObject obj){
    TraceLog(LOG_TRACE, "Entering Function: GetEnemyType");
    EnemyType type = NONE;
    for (int i = 0; i < obj.propertiesLength; i++){
        TraceLog(LOG_INFO, "GetEnemyType: Filtering for property name(Type)");
        TraceLog(LOG_INFO, "GetEnemyType: property name(%s)", obj.properties[i].name);

        if (strcmp(obj.properties[i].name, "Type") == 0){
            TraceLog(LOG_INFO, "GetEnemyType: Property name(Type) found", obj.properties[i].name);
            if (strcmp(obj.properties[i].stringValue, "Farmer") == 0){
                type = FARMER;
            }
            else if (strcmp(obj.properties[i].stringValue, "Alien") == 0){
                type = ALIEN;
            }
            else {
                TraceLog(LOG_ERROR, "GetEnemyType: Property value(%s) not a valid value", obj.properties[i].stringValue);
            }
        }
        else {
            TraceLog(LOG_ERROR, "GetEnemyType: Property name(Type) not found");
        }
    }
    return type;    
}


void DeSpawnEnemies(entt::registry &registry){
    for (const auto entity : registry.view<Enemy>()){
        registry.destroy(entity);
    }
}

void UpdateEnemies(entt::registry &registry, float dt){
    TraceLog(LOG_TRACE, "Entering function: UpdateEnemies");

    auto view = registry.view<Enemy>();
    for (entt::entity enemy :view){
        // Get the update function from the entity
        Enemy_behavior update = registry.get<Enemy_behavior>(enemy);

        // Call the function with the entity as an argument
        TraceLog(LOG_TRACE, "Calling update function for enemy entity: %d", enemy);
        update.Update(registry, dt, enemy);
    }
}