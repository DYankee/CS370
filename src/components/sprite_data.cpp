#include "sprite_data.hpp"

    // Constructor to initialize textures and set the current texture to the first one
    SpriteData::SpriteData(std::map<std::string, Texture2D> textures, Color color)
    {
            this->color = color;
            this->textures = textures;
            this->curentTexture = &this->textures.begin()->second;
    };

    // Deconstructor to unload textures
    SpriteData::~SpriteData(){
        // Unload all textures in the map
        for (auto& pair : textures) {
            UnloadTexture(pair.second);
        }
    }

    // Set source rectangle based on texture size
    void SpriteData::setSrcRec(Texture2D texture) {
        srcRec = {0, 0, (float)texture.width, (float)texture.height};
    }

    // Set the current texture by name
    void SpriteData::setTexture(std::string name) {
        auto texture = textures.find(name);
        if (texture != textures.end()) {
            curentTexture = &texture->second;
            setSrcRec(texture->second);
        } else {
            TraceLog(LOG_ERROR, "Texture '%s' not found!", name.c_str());
        }
    }

    void SpriteData::addTexture(std::string name, std::string path) {
        Texture2D texture = LoadTexture(path.c_str());
        if (texture.id != 0) { // Check if texture loaded successfully
            textures[name] = texture;
        } else {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", path.c_str());
        }
    }