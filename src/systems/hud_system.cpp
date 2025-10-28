#include "hud_system.hpp"
#include "../components/player_hud.hpp"
#include "../components/player_stats.hpp"
#include "../include/raylib.h"
#include "../include/entt.hpp"

void DrawHealthHUD(entt::registry &registry) {
    // Draw HUDResources
    registry.view<HUDResources>().each([&registry](entt::entity hudEnt, HUDResources &hud){

        PlayerStats &stats = registry.get<PlayerStats>(hud.player);

        for (int i = 0; i < stats.maxHealth; ++i) {
            Vector2 drawPos = { hud.pos.x + i * hud.spacing, hud.pos.y };
            if (i < stats.health) {
                DrawTexture(hud.heart, (int)drawPos.x, (int)drawPos.y, WHITE);
            } else {
                DrawTexture(hud.heart, (int)drawPos.x, (int)drawPos.y, Fade(WHITE, 0.25f));
            }
        }
    });
}