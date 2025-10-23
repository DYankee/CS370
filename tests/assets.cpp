#ifndef ASSETS_CPP
#define ASSETS_CPP

#include <filesystem>
#include <iostream>
#include "../include/raylib.h"

namespace fs = std::filesystem;

int LoadTextureTest(std::string path){
    int entryCount = 0;
    for (const auto &entry : fs::directory_iterator(path)){
        entryCount += 1;
        Texture2D currTexture = LoadTexture(path.c_str());
        std::cout << entry.path() << std::endl;
    }
    return entryCount;
};

#endif