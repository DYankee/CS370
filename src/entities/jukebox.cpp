#include "jukebox.hpp"
#include "../systems/asset_loader.hpp"

void CreateJukebox(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: CreateJukebox");
    // Add entity tag
    entt::entity jukebox = registry.create();
    registry.emplace<Jukebox>(jukebox);

    // Load songs
    std::map<std::string, Music> songs = LoadMusic({
        {"title","assets/audio/acnhtitle.mp3"},
        {"gameplay","assets/audio/stardewsummer.mp3"},
        {"death","assets/audio/deathScreen.mp3"}
    });
    registry.emplace<std::map<std::string, Music>>(jukebox);
}

entt::entity GetJukeboxEntity(entt::registry &registry){
    TraceLog(LOG_TRACE, "Entering function: GetJukeboxEntity");
    entt::entity jukebox = registry.view<Jukebox>().front();
    return jukebox;
}