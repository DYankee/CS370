#include "map.hpp"

// Map struct constructor
Map::Map(){};

// Function to create and setup a map entity
void Map::CreateMap(entt::registry &registry, std::string tmxFilePath, Music music) {
    entt::entity mapEntity = registry.create();
    TmxMap* map = LoadTMX(tmxFilePath.c_str());
    if (!map) {
        TraceLog(LOG_ERROR, "Failed to load TMX map: %s", tmxFilePath.c_str());
        CloseWindow();
        return;
    }
    registry.emplace<Map>(mapEntity, Map());
    registry.emplace<TmxMap>(mapEntity, map);
    registry.emplace<Music>(mapEntity, music);
}


// Function to update map state
void Map::UpdateMap(entt::registry &registry, float dt) {
    registry.view<Map, TmxMap, Music>().each([dt](TmxMap &tmxMap, Music &music) {
        UpdateMusicStream(music);
    });
}