#include "game_state.hpp"
#include "../../include/entt.hpp"
#include "../../include/raylib.h"

void CreateGameState(entt::registry &registry){
    
    
    // Add entity tag    
    entt::entity gameState = registry.create();
    registry.emplace<GameState>(gameState);

    // Add gameScreen state
    GameScreen currentScreen = TITLE;
    registry.emplace<GameScreen>(gameState, currentScreen);
}


entt::entity GetGameStateEntity(entt::registry &registry){
    entt::entity gameState = registry.view<GameState>().front();
    return gameState;
}