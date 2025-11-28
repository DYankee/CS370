#include "npc_controller.hpp"

// Function to find NPC spawn points and spawn the designated NPCs at them
void SpawnNPCs(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: SpawnNPCs");
    registry.view<Map, TmxMap>().each([&registry](TmxMap &map){
        // Get the entities group from the map
        TmxObjectGroup entities = FindLayerByName(map.layers, map.layersLength, "Entities")->exact.objectGroup;
        
        // Get the NPCs from the entities list by type
        std::vector<TmxObject> pigs = FindObjectsByType(entities.objects, entities.objectsLength, "Pig");
        std::vector<TmxObject> hatPigs = FindObjectsByType(entities.objects, entities.objectsLength, "HatPig");
        std::vector<TmxObject> chickens = FindObjectsByType(entities.objects, entities.objectsLength, "Chicken");
        std::vector<TmxObject> sheep = FindObjectsByType(entities.objects, entities.objectsLength, "Sheep");
        std::vector<TmxObject> chicks = FindObjectsByType(entities.objects, entities.objectsLength, "Chick");
        
        // Spawn Pigs
        for (TmxObject npc : pigs){
            TraceLog(LOG_INFO, "Creating Pig at: %f,%f", float(npc.x), float(npc.y));
            CreatePig(registry, npc);
        }
        
        // Spawn Hat Pigs
        for (TmxObject npc : hatPigs){
            TraceLog(LOG_INFO, "Creating Hat Pig at: %f,%f", float(npc.x), float(npc.y));
            CreateHatPig(registry, npc);
        }
        
        // Spawn Chickens
        for (TmxObject npc : chickens){
            TraceLog(LOG_INFO, "Creating Chicken at: %f,%f", float(npc.x), float(npc.y));
            CreateChicken(registry, npc);
        }
        
        // Spawn Sheep
        for (TmxObject npc : sheep){
            TraceLog(LOG_INFO, "Creating Sheep at: %f,%f", float(npc.x), float(npc.y));
            CreateSheep(registry, npc);
        }
        
        // Spawn Chicks
        for (TmxObject npc : chicks){
            TraceLog(LOG_INFO, "Creating Chick at: %f,%f", float(npc.x), float(npc.y));
            CreateChick(registry, npc);
        }
    });
}

void DeSpawnNPCs(entt::registry &registry){
    for (const auto entity : registry.view<NPC>()){
        registry.destroy(entity);
    }
}

void UpdateNPCs(entt::registry &registry, float dt){
    TraceLog(LOG_TRACE, "Entering function: UpdateNPCs");
    
    auto view = registry.view<NPC, NPC_behavior>();
    for (entt::entity npc : view){
        // Get the update function from the entity
        NPC_behavior& update = registry.get<NPC_behavior>(npc);

        // Call the function with the entity as an argument
        update.Update(registry, dt, npc);
    }
}