#ifndef ASSET_LOADER_HPP
#define ASSET_LOADER_HPP

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <raylib.h>



// Function to load multiple textures and store them in a map
// Created by Zachary Geary
std::map<std::string, Texture2D> LoadTextures(std::map<std::string, std::string> texturePaths);


#endif // ASSET_LOADER_HPP