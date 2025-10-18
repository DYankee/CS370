#ifndef SPRITE_DATA_HPP
#define SPRITE_DATA_HPP

#include "../../include/raylib.h"
#include <map>
#include <string>

    struct SpriteData
    {
        std::map<std::string, Texture2D> textures;
        Texture2D *curentTexture;
        Rectangle srcRec;
        Color color;

        // Constructor
        SpriteData(std::map<std::string, Texture2D> textures, Color color);
        // Deconstructor
        ~SpriteData();

        // Methods
        void SetTexture(std::string name);
        void SetSrcRec(Texture2D texture);
        void AddTexture(std::string name, std::string path);
    };

#endif // SPRITE_DATA