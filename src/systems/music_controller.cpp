#include "music_controller.hpp"

void UpdateMusic(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: UpdateMusic");

    // Get necessary entities
    entt::entity jukebox = GetJukeboxEntity(registry);

    // Get songs
    std::map<std::string, Music> &songs = registry.get<std::map<std::string, Music>>(jukebox);
    
    for (const auto& song : songs){
        TraceLog(LOG_TRACE, "Updating music stream: %s", song.first.c_str());
        UpdateMusicStream(song.second);
    }
}

void StopAllMusic(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: StopAllMusic");
    // Get necessary entities
    entt::entity jukebox = GetJukeboxEntity(registry);
    // Get songs
    std::map<std::string, Music> &songs = registry.get<std::map<std::string, Music>>(jukebox);

    for (const auto &[name, song] : songs){
        StopMusicStream(song);
    }
}

void StartSong(entt::registry &registry, std::string song){
    TraceLog(LOG_TRACE, "Entering function: StartSong");
    // Get necessary entities
    entt::entity jukebox = GetJukeboxEntity(registry);
    // Get songs
    std::map<std::string, Music> &songs = registry.get<std::map<std::string, Music>>(jukebox);
    
    // Start song

    TraceLog(LOG_TRACE, "Starting song(%s)", song.c_str());
    PlayMusicStream(songs[song]);
}