#ifndef PLAYER_MOVEMENT_HPP
#define PLAYER_MOVEMENT_HPP
#include "../../include/entt.hpp"
#include "../../include/raytmx.h"
#include "../entities/entities.hpp"

typedef enum GameScreen { TITLE = 0, GAMEPLAY, DEATH} GameScreen;

void PlayerInputSystem(entt::registry &registry, float dt);
void MovePlayer(entt::registry &registry, float dt, entt::entity entity);
void CheckForPlayerDeath(entt::registry &registry, GameScreen &currentScreen);

#endif