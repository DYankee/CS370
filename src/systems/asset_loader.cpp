#include "asset_loader.hpp"

// Function to load multiple textures and store them in a map
// Created by Zachary Geary
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