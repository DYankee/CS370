// CS370.cpp
#include <iostream>

// Include all ECS headers
#include "entities/entities.hpp"
#include "components/components.hpp"
#include "systems/systems.hpp"

#include "../include/raytmx.h"
#include "../include/raylib.h"
#include "components/player_hud.hpp"
#include "systems/hud_system.hpp"
#include "systems/iframes_system.hpp"

using namespace std;

// Player and physics constants
#define CHAR_WIDTH 32
#define CHAR_HEIGHT 32
#define GRAVITY 2000.0f          // Gravity strength 
#define SPEED 400.0f             // speed 

typedef enum GameScreen { TITLE = 0, GAMEPLAY } GameScreen;

void Update(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: Update (main)");
    PlayerInputSystem(registry, dt);
    MovePlayer(registry, dt);
    UpdateEnemies(registry, dt);
    CameraUpdate(registry, dt);
    SpikeCollision(registry, dt);
    CheckForMapChange(registry);
    UpdateMap(registry, dt);
    UpdateIFrames(registry, dt);
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
            registry.view<SpriteData, Player, Animation>().each([&transform](SpriteData &sprite, Animation &animation) {
                Rectangle srcRec = sprite.srcRec;
                
                // Use animation frame if animation is playing
                if (animation.isPlaying) {
                    srcRec = animation.GetCurrentFrame();
                }
                
                Rectangle dstRec = {transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y};
                Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                TraceLog(LOG_INFO, "Drawing Player at: %f,%f", dstRec.x, dstRec.y);
                TraceLog(LOG_INFO, "Width/Height: %f,%f", dstRec.width, dstRec.height);
                DrawTexturePro(sprite.curentTexture, srcRec, dstRec, origin, transform.rotation.x, sprite.color);
            });

            // Draw Enemies
            TraceLog(LOG_TRACE, "Drawing enemies");
            registry.view<SpriteData, Transform, Enemy>().each([](SpriteData &sprite, Transform &pos){
                Rectangle dstRec = {pos.translation.x, pos.translation.y, pos.scale.x, pos.scale.y};
                Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                TraceLog(LOG_INFO, "Drawing Enemy at: %f,%f", dstRec.x, dstRec.y);
                TraceLog(LOG_INFO, "Width/Height: %f,%f", dstRec.width, dstRec.height);
                DrawTexturePro(sprite.curentTexture, sprite.srcRec, dstRec, origin, pos.rotation.x, sprite.color);
            });

                
                // Draw text
                const char* msg = "Move A/D, Jump SPACE";
                //DrawRectangle(8, 8, MeasureText(msg, 20) + 4, 24, Fade(BLACK, 0.5f));
                //DrawText(msg, 10, 10, 20, WHITE);
        
            });
            EndMode2D(); // End 2D camera mode
            // Draw HUD
            DrawHealthHUD(registry);
    });
    EndDrawing();
    TraceLog(LOG_TRACE, "Exiting Function: Render (main)");
}

void RenderTitleScreen(const Vector2 &screenSize, Texture2D buttonTexture, Rectangle btnBounds, Rectangle sourceRec, Texture2D backgroundTexture, Texture2D titleTexture) {
    BeginDrawing();

    // Draw background
    Rectangle bgSource = { 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height };
    Rectangle bgDest = { 0, 0, screenSize.x, screenSize.y };
    Vector2 bgOrigin = { 0, 0 };
    DrawTexturePro(backgroundTexture, bgSource, bgDest, bgOrigin, 0.0f, WHITE);
    
    // Draw title texture
    Rectangle titleSource = { 0, 0, (float)titleTexture.width, (float)titleTexture.height };
    float titleScale = 1.0f;
    Rectangle titleDest = { 
        (screenSize.x - titleTexture.width * titleScale) / 2, 50.0f,
        titleTexture.width * titleScale, 
        titleTexture.height * titleScale 
    };
    Vector2 titleOrigin = { 0, 0 };
    DrawTexturePro(titleTexture, titleSource, titleDest, titleOrigin, 0.0f, WHITE);
    
    // Draw texture button
    Vector2 btnPosition = { btnBounds.x, btnBounds.y };
    DrawTextureRec(buttonTexture, sourceRec, btnPosition, WHITE);
    
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
    PlayMusicStream(music);

    // Load sound effects
    Sound titleMooSound = LoadSound("assets/audio/titleMoo.mp3");

    // Load title texture
    Texture2D titleTexture = LoadTexture("assets/graphics/title.png");

    // Load button texture
    Texture2D buttonTexture = LoadTexture("assets/graphics/button.png");

    // Load background texture
    Texture2D backgroundTexture = LoadTexture("assets/graphics/bgart/mainbackground.png");
    
    // Define source rectangle for button
    Rectangle sourceRec = { 0, 0, (float)buttonTexture.width, (float)buttonTexture.height };
    
    // Define button bounds on screen
    Rectangle btnBounds = { 
        screenSize.x/2.0f - buttonTexture.width/2.0f, 
        screenSize.y/2.0f + 100.0f, 
        (float)buttonTexture.width, 
        (float)buttonTexture.height 
    };
    
    bool btnAction = false;         // Button action should be activated
    Vector2 mousePoint = { 0.0f, 0.0f };

    // Game state
    GameScreen currentScreen = TITLE;

    // Create entt registry
    entt::registry registry = entt::registry();
    bool gameInitialized = false;

    // Main game loop
    while (!WindowShouldClose()) {
        float frameTime = GetFrameTime();
        mousePoint = GetMousePosition();
        btnAction = false;

        // Handle ESC key to close
        if (IsKeyDown(KEY_ESCAPE)) {
            break;
        }

        // Update based on current screen
        switch (currentScreen) {
            case TITLE:
            {
                // Check button state
                if (CheckCollisionPointRec(mousePoint, btnBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
                }
                
                // Check if button was clicked to start the game
                if (btnAction) {
                    PlaySound(titleMooSound);
                    currentScreen = GAMEPLAY;
                    
                    // Initialize game only once
                    if (!gameInitialized) {
                        // Load TMX map using RayTMX
                        CreateMap(registry, "assets/tiled/stage1.tmx", music);
                        CreateCamera(registry, screenSize); 

                        // Player setup
                        // Create player entity
                        CreatePlayer(registry);

                        SpawnEnemies(registry);
                        
                        gameInitialized = true;
                    }
                }
            } break;
            
            case GAMEPLAY:
            {
                // Update Game State
                Update(registry, frameTime);
            } break;
            
            default: break;
        }

        // Render based on current screen
        switch (currentScreen) {
            case TITLE:
            {
                // Drawing title screen
                RenderTitleScreen(screenSize, buttonTexture, btnBounds, sourceRec, backgroundTexture, titleTexture);
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
    UnloadTexture(buttonTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(titleTexture);
    UnloadSound(titleMooSound);
    UnloadMusicStream(music);
    CloseAudioDevice();   
    CloseWindow();
    registry.view<HUDResources>().each([&](HUDResources &hud) {
        UnloadTexture(hud.heart);
    });

    return 0;
}