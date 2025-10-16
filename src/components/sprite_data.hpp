#ifndef SPRITE_DATA_HPP
#define SPRITE_DATA_HPP

#include <raylib.h>
#include <map>
#include <string>

    struct SpriteData
    {
        Texture2D *curentTexture;
        std::map<std::string, Texture2D> textures;

        // Constructor
        SpriteData(std::map<std::string, Texture2D> textures);
        // Deconstructor
        ~SpriteData();

        // Methods
        void setTexture(std::string name);
        void addTexture(std::string name, std::string path);
    };

#endif // SPRITE_DATA