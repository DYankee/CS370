#include "map_manager.hpp"

int mapIndex = 1;

// Change the current map to a new TMX file and set player start position
void ChangeMap(entt::registry &registry, std::string tmxFilePath) {
    TraceLog(LOG_TRACE, "Entering Function: ChangeMap");
    TraceLog(LOG_INFO, "Changing map to: %s", tmxFilePath.c_str());

    registry.view<Map, TmxMap>().each([&registry, &tmxFilePath](TmxMap &currentMap) {
        // Load new map
        TmxMap* newMapPtr = LoadTMX(tmxFilePath.c_str());
        if (!newMapPtr) {
            TraceLog(LOG_ERROR, "Failed to load TMX map: %s", tmxFilePath.c_str());
            CloseWindow();
            return;
        }
        // Unload old map
        //UnloadTMX(&currentMap);
        
        // Update to the newmap
        currentMap = *newMapPtr;
        
        // Set player start position
        registry.view<Player, Transform>().each([&registry, &currentMap](Transform &transform) {

            TmxObjectGroup entities = FindLayerByName(currentMap.layers, currentMap.layersLength, "Entities")->exact.objectGroup;
            TmxObject player = FindObjectByName(entities.objects, entities.objectsLength, "Player");

            TraceLog(LOG_INFO, "Moving player to map spawn at: %f,%f", player.x, player.y);
            transform.translation.x = player.x;
            transform.translation.y = player.y;

            TraceLog(LOG_INFO, "Player new location: %f,%f", transform.translation.x, transform.translation.y);

            registry.view<PlayerCamera, Camera2D>().each([&transform](Camera2D &camera){
                SetCameraPos(camera, transform);
            });
        });
    });
}

// Check if the player has reached map boundaries to trigger a map change
void CheckForMapChange(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering Function: CheckForMapChange");
    TraceLog(LOG_INFO, "Checking for map change");
    registry.view<Player, Transform>().each([&registry](Transform &transform) {
        Vector2 playerPos = { transform.translation.x, transform.translation.y };
        registry.view<Map, TmxMap>().each([&registry, &playerPos](TmxMap &map) {
            
            // Change to earlier stage if player goes past left edge
            if (playerPos.x < 0) {
                mapIndex--;
                if(mapIndex >= 1) {
                    ChangeMap(registry, "assets/tiled/stage" + std::to_string(mapIndex)+ ".tmx");
                }
                else {
                    mapIndex = 2; // just goes back to stage1
                }
            }

            // Change to next stage if player goes past right edge
            if (playerPos.x > 1920) {
                mapIndex++;
                ChangeMap(registry, "assets/tiled/stage" + std::to_string(mapIndex) + ".tmx");
            }
        });
    });    
}

// Function to update map state
void UpdateMap(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: UpdateMap");

    registry.view<Map, TmxMap, Music>().each([dt](TmxMap &tmxMap, Music &music) {
        UpdateMusicStream(music);
    });
}