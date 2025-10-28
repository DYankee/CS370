// CS370.cpp
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
#define GRAVITY 1000.0f          // Gravity strength 
#define SPEED 400.0f             // speed 
#define NUM_FRAMES  3            // Number of frames for button sprite (normal, hover, pressed)

typedef enum GameScreen { TITLE = 0, GAMEPLAY } GameScreen;

void Update(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: Update (main)");
    PlayerInputSystem(registry, dt);
    MovePlayer(registry, dt);
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
            registry.view<SpriteData, Player>().each([&transform](SpriteData &sprite) {
                Rectangle dstRec = {transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y};
                Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                TraceLog(LOG_INFO, "Drawing Player at: %f,%f", dstRec.x, dstRec.y);
                TraceLog(LOG_INFO, "Width/Height: %f,%f", dstRec.width, dstRec.height);
                DrawTexturePro(*sprite.curentTexture, sprite.srcRec, dstRec, origin, transform.rotation.x, sprite.color);
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

void RenderTitleScreen(const Vector2 &screenSize, Texture2D buttonTexture, Rectangle btnBounds, Rectangle sourceRec, Texture2D backgroundTexture) {
    BeginDrawing();

    // Draw background
    Rectangle bgSource = { 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height };
    Rectangle bgDest = { 0, 0, screenSize.x, screenSize.y };
    Vector2 bgOrigin = { 0, 0 };
    DrawTexturePro(backgroundTexture, bgSource, bgDest, bgOrigin, 0.0f, WHITE);
    
    // Draw title
    const char* title = "Milksong";
    int titleFontSize = 80;
    int titleWidth = MeasureText(title, titleFontSize);
    DrawText(title, (screenSize.x - titleWidth) / 2, screenSize.y / 3, titleFontSize, WHITE);
    
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
    // PlayMusicStream(music);

    // Load button texture
    Texture2D buttonTexture = LoadTexture("assets/graphics/testbutton.png");

    // Load background texture
    Texture2D backgroundTexture = LoadTexture("assets/graphics/bgart/mainbackground.png");
    
    // Define frame rectangle for drawing (assuming 3 frames: normal, hover, pressed)
    float frameHeight = (float)buttonTexture.height / NUM_FRAMES;
    Rectangle sourceRec = { 0, 0, (float)buttonTexture.width, frameHeight };
    
    // Define button bounds on screen
    Rectangle btnBounds = { 
        screenSize.x/2.0f - buttonTexture.width/2.0f, 
        screenSize.y/2.0f + 50, 
        (float)buttonTexture.width, 
        frameHeight 
    };
    
    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
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
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;  // PRESSED
                    else btnState = 1;  // MOUSE_HOVER

                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
                } else {
                    btnState = 0;  // NORMAL
                }

                // Calculate button frame rectangle to draw depending on button state
                sourceRec.y = btnState * frameHeight;
                
                // Check if button was clicked to start the game
                if (btnAction) {
                    currentScreen = GAMEPLAY;
                    
                    // Initialize game only once
                    if (!gameInitialized) {
                        // Load TMX map using RayTMX
                        CreateMap(registry, "assets/tiled/stage1.tmx", music);
                        CreateCamera(registry, screenSize); 

                        // Player setup
                        // Create player entity
                        CreatePlayer(registry);

                        CreateEnemy(registry);
                        
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
                // Drawing title screen with texture button
                RenderTitleScreen(screenSize, buttonTexture, btnBounds, sourceRec, backgroundTexture);
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
    UnloadMusicStream(music);
    CloseAudioDevice();   
    CloseWindow();
    registry.view<HUDResources>().each([&](HUDResources &hud) {
        UnloadTexture(hud.heart);
    });

    return 0;
}