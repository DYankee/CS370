// CS370.cpp
// CS370.cpp
#include <iostream>

// Include all ECS headers
#include "entities/entities.hpp"
#include "components/components.hpp"
#include "systems/systems.hpp"

#include "../include/raytmx.h"
#include "../include/raylib.h"

using namespace std;

// Player and physics constants
#define CHAR_WIDTH 32
#define CHAR_HEIGHT 32
#define GRAVITY 1000.0f          // Gravity strength 
#define SPEED 400.0f             // speed 

typedef enum GameScreen { TITLE = 0, GAMEPLAY } GameScreen;

void Update(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: Update (main)");
    PlayerInputSystem(registry, dt);
    MovePlayer(registry, dt);
    CameraUpdate(registry, dt);
    SpikeCollision(registry, dt);
    CheckForMapChange(registry);
    UpdateMap(registry, dt);
};

void Render(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: Render (main)");
    BeginDrawing();
    
    registry.view<Camera2D, PlayerCamera>().each([&registry](Camera2D camera){
        BeginMode2D(camera);
        registry.view<Transform, Player, PlayerStats>().each([&registry, &camera](Transform &transform, PlayerStats &stats) {
            ClearBackground(RAYWHITE);
        
            // Draw TMX map
            TraceLog(LOG_TRACE, "Drawing Map");
            registry.view<TmxMap, Map>().each([&camera](TmxMap &map) {
                AnimateTMX(&map); // Update animated tiles
                DrawTMX(&map, &camera, 0, 0, WHITE); // Draw tile map with parallax support 
            });
            
            
            // Draw player
            TraceLog(LOG_TRACE, "Drawing Player");
            registry.view<SpriteData, Player>().each([&transform](SpriteData &sprite) {
                Rectangle dstRec = {transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y};
                Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                TraceLog(LOG_INFO, "Drawing Player at: %f,%f", dstRec.x, dstRec.y);
                TraceLog(LOG_INFO, "Width/Height: %f,%f", dstRec.width, dstRec.height);
                DrawTexturePro(*sprite.curentTexture, sprite.srcRec, dstRec, origin, transform.rotation.x, sprite.color);
            });
            
            //show health
            //for (int i = 0; i < stats.maxHealth; i++) {
            //    Vector2 pos = { healthPos.x + i * iconSpacing, healthPos.y };
        //    if (i < playerHealth) {
            //        DrawTexture(heart, pos.x, pos.y, WHITE);
            //    } else {
                //        DrawTexture(heart, pos.x, pos.y, Fade(WHITE, 0.2f));
                //    }
                //}
                
                // Draw text
                const char* msg = "Move A/D, Jump SPACE";
                //DrawRectangle(8, 8, MeasureText(msg, 20) + 4, 24, Fade(BLACK, 0.5f));
                //DrawText(msg, 10, 10, 20, WHITE);
        
            });
            EndMode2D(); // End 2D camera mode
    });
    EndDrawing();
    TraceLog(LOG_TRACE, "Exiting Function: Render (main)");
}

void RenderTitleScreen(const Vector2 &screenSize) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    // Draw title
    const char* title = "Milksong";
    int titleFontSize = 80;
    int titleWidth = MeasureText(title, titleFontSize);
    DrawText(title, (screenSize.x - titleWidth) / 2, screenSize.y / 3, titleFontSize, WHITE);
    
    // Draw instructions
    const char* instructions = "PRESS ENTER TO START";
    int instructionsFontSize = 30;
    int instructionsWidth = MeasureText(instructions, instructionsFontSize);
    DrawText(instructions, (screenSize.x - instructionsWidth) / 2, screenSize.y / 2 + 50, instructionsFontSize, GRAY);
    
    EndDrawing();
}

int main() {
    // Set log level
    SetTraceLogLevel(LOG_ALL);

    // Window setup
    float accumulator = 0.0f;             // Keeps track of leftover frame time
    const float dt = 1.0f / 60.0f;        // 60 FPS physics step

    const Vector2 screenSize { 1920, 1080};
    InitWindow(screenSize.x, screenSize.y, "CS370");
    // ToggleFullscreen();
 	SetTargetFPS(60);

    // Music setup
    InitAudioDevice();
    Music music = LoadMusicStream("assets/music/stardewsummer.mp3");
    SetMusicVolume(music, 1.0f);
    // PlayMusicStream(music);

    // Game state
    GameScreen currentScreen = TITLE;

    // Create entt registry
    entt::registry registry = entt::registry();
    bool gameInitialized = false;

    // load health sprite 
    // Texture2D heart = LoadTexture("assets/sprites/CowFace.png");
    // Vector2 healthPos = { 20, 30 }; // top left
    // const int iconSpacing = 50;     // space between icons

    // Main game loop
    while (!WindowShouldClose()) {
    float frameTime = GetFrameTime();

    // Handle ESC key to close
        if (IsKeyDown(KEY_ESCAPE)) {
            break;
        }

        // Update based on current screen
        switch (currentScreen) {
            case TITLE:
            {
                // Press enter to start the game
                if (IsKeyPressed(KEY_ENTER)) {
                    currentScreen = GAMEPLAY;
                    
                    // Initialize game only once
                    if (!gameInitialized) {
                        // Load TMX map using RayTMX
                        CreateMap(registry, "assets/tiled/stage1.tmx", music);
                        CreateCamera(registry, screenSize); 

                        // Player setup
                        // Create player entity
                        CreatePlayer(registry);
                        
                        gameInitialized = true;
                    }
                }
            } break;
            
            case GAMEPLAY:
            {
                // Update Game State
                Update(registry, frameTime);

                //if (iFrames > 0.0f) {
                //iFrames -= dt;
                //cowColor = Fade(RED, 0.5f);
                //}
                //else {
                //    cowColor = WHITE;
                //}
            } break;
            
            default: break;
        }

        // Render based on current screen
        switch (currentScreen) {
            case TITLE:
            {
                // Drawing title screen
                RenderTitleScreen(screenSize);
            } break;
            
            case GAMEPLAY:
            {
                // Drawing gameplay
                Render(registry, frameTime);
            } break;
            
            default: break;
        }
    }
    
    // Cleanup
    UnloadMusicStream(music);
    CloseAudioDevice();   
    CloseWindow();

    return 0;
}