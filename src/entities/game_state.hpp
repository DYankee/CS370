#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../../include/entt.hpp"

typedef enum GameScreen { TITLE = 0, CONTROLS, GAMEPLAY, DEATH} GameScreen;

struct GameState {};

void CreateGameState(entt::registry &registry);

// Get reference to gameState entity
entt::entity GetGameStateEntity(entt::registry &registry);

#endif
