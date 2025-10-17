#include "map.hpp"


// Function to create and setup a map entity
void CreateMap(entt::registry &registry, std::string tmxFilePath, Music music) {
    entt::entity mapEntity = registry.create();
    TmxMap *mapPtr = LoadTMX(tmxFilePath.c_str());
    if (!mapPtr) {
        TraceLog(LOG_ERROR, "Failed to load TMX map: %s", tmxFilePath.c_str());
        CloseWindow();
        return;
    }
    TmxMap map = *mapPtr;
    registry.emplace<Map>(mapEntity, Map());
    registry.emplace<TmxMap>(mapEntity, map);
    registry.emplace<Music>(mapEntity, music);
}


// Function to update map state
void UpdateMap(entt::registry &registry, float dt) {
    registry.view<Map, TmxMap, Music>().each([dt](TmxMap &tmxMap, Music &music) {
        UpdateMusicStream(music);
    });
}