#pragma once
#include "../include/raylib.h"
#include "../include/entt.hpp"

struct HUDResources {
    Texture2D heart;      // cowFace texture
    Vector2 pos;          // top left screen
    int spacing;          
    entt::entity player; 

    HUDResources() = default;
    HUDResources(Texture2D heart_, Vector2 pos_, int spacing_, entt::entity player_ = entt::null)
        : heart(heart_), pos(pos_), spacing(spacing_), player(player_) {}
};