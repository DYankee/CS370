#include "collision_system.hpp" //find an object/group layer by name

static TmxLayer* FindLayerByName(TmxLayer* layers, int layersLength, const char* name) {
    if (!layers || layersLength == 0 || !name){
         return NULL;
    }
    for (int i = 0; i < layersLength; ++i) {
        if (layers[i].name && strcmp(layers[i].name, name) == 0) return &layers[i];
        if (layers[i].type == LAYER_TYPE_GROUP && layers[i].layersLength > 0) {
            TmxLayer* found = FindLayerByName(layers[i].layers, layers[i].layersLength, name);
            if (found) return found;
        }
    }
    return NULL;
}