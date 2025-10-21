#include "map_manager.hpp"

// Change the current map to a new TMX file and set player start position
void ChangeMap(entt::registry &registry, std::string tmxFilePath, Vector2 startPosition) {
    TraceLog(LOG_TRACE, "Entering Function: ChangingMap");
    TraceLog(LOG_INFO, "Changing map to: %s", tmxFilePath.c_str());

    registry.view<Map, TmxMap>().each([&registry, &tmxFilePath, &startPosition](TmxMap &oldMap) {
        // Load new map
        TmxMap* newMapPtr = LoadTMX(tmxFilePath.c_str());
        if (!newMapPtr) {
            TraceLog(LOG_ERROR, "Failed to load TMX map: %s", tmxFilePath.c_str());
            CloseWindow();
            return;
        }
        TmxMap newMap = *newMapPtr;

        // Unload old map
        UnloadTMX(&oldMap);
        
        // Update to the newmap
        oldMap = newMap;
        
        // Set player start position
        registry.view<Player, Transform>().each([&startPosition](Transform &transform) {
            transform.translation.x = startPosition.x;
            transform.translation.y = startPosition.y;
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
            
            // Change to stage2 if player goes past left edge
            if (playerPos.x < 0) {
                ChangeMap(registry, "assets/tiled/stage2.tmx", {400.0f, 300.0f});
            }

            // Change to stage1 if player goes past bottom edge
            if (playerPos.y > 600) {
                ChangeMap(registry, "assets/tiled/stage1.tmx", {400.0f, 300.0f});
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