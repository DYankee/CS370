#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

extern "C" {
    #define RAYTMX_IMPLEMENTATION
    #include "../../include/raytmx.h"
}

//find an object/group layer by name
static TmxLayer* FindLayerByName(TmxLayer* layers, int layersLength, const char* name);

#endif // COLLISION_SYSTEM_HPP