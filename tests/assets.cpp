#ifndef ASSETS_CPP
#define ASSETS_CPP

#include <filesystem>
#include <iostream>
#include "../include/raylib.h"

namespace fs = std::filesystem;

// Takes in the path to a directory and tries to load all the assets in it
int LoadTextureTest(std::string path){
    int entryCount = 0;
    int failures = 0;

    Texture2D currTexture;

    for (auto &entry : fs::directory_iterator(path)){
        std::cout << "current path: " << entry.path() << std::endl;

        currTexture = LoadTexture(entry.path().c_str());
        if (currTexture.id <= 0){
            failures += 1;
        }
        UnloadTexture(currTexture);
        entryCount += 1;
    }

    return failures;
};

int assetTests(){
    int failures = 0;
    failures += LoadTextureTest("sprites");
    failures += LoadTextureTest("graphics");
    failures += LoadTextureTest("graphics/bgart");
    failures += LoadTextureTest("graphics/tileset");
    return failures;
}

#endif