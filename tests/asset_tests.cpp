#ifndef ASSETS_CPP
#define ASSETS_CPP

#include <vector>
#include <filesystem>
#include <iostream>
#include "../include/raylib.h"

namespace fs = std::filesystem;
struct Assets{
    std::vector<std::string> pngs;
    std::vector<std::string> maps;
};

// Get and sort all assets from assets folder into the assets struct
Assets GetAssets(std::string path){
    Assets assets;
    std::cout << "Getting assets" << std::endl;
    for (const auto &entry : fs::recursive_directory_iterator(path)){
        if (fs::is_regular_file(entry.status())){
            std::string cPath = entry.path().string();
            // Filter for png files and add them to the pngs vec
            if (cPath.find(".png") != std::string::npos){
                std::cout << "Filtered paths:" << cPath << std::endl;
                assets.pngs.push_back(entry.path().string());
            }
            // Filter for tmx files and add them to the maps vec
            else if (cPath.find(".tmx") != std::string::npos){
                std::cout << cPath << std::endl;
                assets.maps.push_back(entry.path().string());
            }
        }
    }
    return assets;
}

// Takes in a vector of file paths and tries to load the textures associated with them
bool LoadTextureTest(std::vector<std::string> files){
    bool result = false;
    Texture2D currTexture;
    for (const std::string &path : files){
        currTexture = LoadTexture(path.c_str());
        if (currTexture.id > 0){
            result = true;
        }
        else {
            result = false;
        }
        UnloadTexture(currTexture);
    }

    return result;
};

bool LoadMapTest(std::vector<std::string> files){
    bool result = false;
    
    return result;
}
#endif