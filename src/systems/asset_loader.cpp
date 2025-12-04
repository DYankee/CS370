#include "asset_loader.hpp"

// Function to load multiple textures and store them in a map
std::map<std::string, Texture2D> LoadTextures(std::map<std::string, std::string> texturePaths){
    TraceLog(LOG_TRACE, "Entering Function: LoadTextures");
        
    std::map<std::string, Texture2D> textures;
    //Loop through the provided paths and load each texture into the map
    for (const auto pair : texturePaths) {
        const std::string name = pair.first;
        const std::string path = pair.second;
        Texture2D texture = LoadTexture(path.c_str());
        if (texture.id != 0) { // Check if texture loaded successfully
            textures[name] = texture;
        } else {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", path.c_str());
        }
    }
    return textures;
}

// Function to load multiple songs and store them in a map
std::map<std::string, Music> LoadMusic(std::map<std::string, std::string> songPaths){
    TraceLog(LOG_TRACE, "Entering Function: LoadMusic");
        
    std::map<std::string, Music> songs;
    //Loop through the provided paths and load each texture into the map
    for (const auto pair : songPaths) {
        const std::string name = pair.first;
        const std::string path = pair.second;
        Music song = LoadMusicStream(path.c_str());
        SetMusicVolume(song, 1.0f);
        if (song.stream.buffer != NULL ) { // Check if texture loaded successfully
            songs[name] = song;
        } else {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", path.c_str());
        }
    }
    return songs;
}