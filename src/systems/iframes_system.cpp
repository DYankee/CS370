#include "iframes_system.hpp"
#include "../components/player_stats.hpp"
#include "../components/sprite_data.hpp"
#include "../include/raylib.h"
#include "../include/entt.hpp"

// Decrease iframes
void UpdateIFrames(entt::registry &registry, float dt) {
    // Update PlayerStats iFrames
    registry.view<PlayerStats, SpriteData>().each([dt](PlayerStats &stats, SpriteData &sprite) {
        if (stats.iFrames > 0.0f) {
            stats.iFrames -= dt;
            if (stats.iFrames < 0.0f) stats.iFrames = 0.0f;

            // make player red
            sprite.color = Fade(RED, 0.7f);
        } else {
            // make default color
            sprite.color = WHITE;
        }
    });
}