# Sprite Data Component


## Attributes
- Texture2D *currentTexture; A pointer to the currently selected texture  
- Rectangle srcRec;
- std::map<std::string, Texture2D> textures; A map containing all the textures loaded into memory mapped to a string label
- Color color;

## Functions
### Constructor/Destructor:
- SpriteData(std::map<std::string, Texture2D> textures): Takes in a map containing the label and path to each texture
- ~SpriteData()

### Methods:
- setTexture(std::string): Tries to set the current texture to the associated texture from the textures map 
- addTexture(std::string, std::string path): adds a texture to the map
setSrcRec(Texture2D texture)

