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
#include "systems/player_enemy_collision.hpp"
#include "systems/health_upgrade_controller.hpp"
#include "systems/player_health_upgrade_collision.hpp"
#include "systems/upgrade_controller.hpp"
#include "systems/upgrade_collision.hpp"

using namespace std;

void Update(entt::registry &registry, float dt) {
    CheckForDeath(registry);
    UpdateProjectiles(registry, dt);
    PlayerInputSystem(registry, dt);
    UpdateEnemies(registry, dt);
    PlayerEnemyCollisionSystem(registry, dt);
    CameraUpdate(registry, dt);
    SpikeCollision(registry, dt);
    CheckForMapChange(registry);
    UpdateMap(registry, dt);
    UpdateIFrames(registry, dt);
    UpdateHealthUpgrades(registry, dt);
    UpdateRangeUpgrades(registry, dt);
    PlayerHealthCollisionSystem(registry, dt);
    UpdateDialogue(registry, dt);
};

void Render(entt::registry &registry, float dt) {
    BeginDrawing();
    
    registry.view<Camera2D, PlayerCamera>().each([&registry](Camera2D camera){
        BeginMode2D(camera);
        registry.view<Transform, Player, PlayerStats>().each([&registry, &camera](Transform &transform, PlayerStats &stats) {
            ClearBackground(RAYWHITE);
        
            // Draw TMX map
            registry.view<TmxMap, Map>().each([&camera](TmxMap &map) {
                AnimateTMX(&map); // Update animated tiles
                DrawTMX(&map, &camera, 0, 0, WHITE); // Draw tile map with parallax support 
            });
            
            
            // Draw player
            registry.view<SpriteData, Player, Animation>().each([&transform](SpriteData &sprite, Animation &animation) {
                Rectangle srcRec = sprite.srcRec;
                
                // Use animation frame if animation exists and has frames
                if (!animation.sequences.empty() && animation.sequences.find(animation.currentSequence) != animation.sequences.end()) {
                    srcRec = animation.GetCurrentFrame();
                }
                
                Rectangle dstRec = {transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y};
                Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                DrawTexturePro(sprite.curentTexture, srcRec, dstRec, origin, transform.rotation.x, sprite.color);
            });

            // Draw Enemies
            registry.view<SpriteData, Transform, EnemyStats, Enemy>().each([&registry](entt::entity entity, SpriteData &sprite, Transform &pos, EnemyStats &enemyStats){
                Rectangle srcRec = sprite.srcRec;
                
                // Use animation frame if animation component exists
                if (registry.all_of<Animation>(entity)) {
                    Animation &animation = registry.get<Animation>(entity);
                    if (!animation.sequences.empty() && animation.sequences.find(animation.currentSequence) != animation.sequences.end()) {
                        srcRec = animation.GetCurrentFrame();
                    }
                }
                
                Rectangle dstRec = {pos.translation.x, pos.translation.y, pos.scale.x, pos.scale.y};
                Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                DrawTexturePro(sprite.curentTexture, srcRec, dstRec, origin, pos.rotation.x, sprite.color);

                // Render weapon if 
                if(registry.all_of<Weapon>(entity)){
                    Weapon &enemyWeapon = registry.get<Weapon>(entity);
                    Vector3 weaponPos = CalculateWeaponOffset(enemyWeapon.offset, pos.translation, enemyStats);
                    Rectangle dstRec = {weaponPos.x , weaponPos.y, float(enemyWeapon.sprite.curentTexture.width), float(enemyWeapon.sprite.curentTexture.height)};
                    Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                    TraceLog(LOG_TRACE, "Rendering enemy weapon at(%f,%f)", dstRec.x,dstRec.y);
                    DrawTexturePro(enemyWeapon.sprite.curentTexture, enemyWeapon.sprite.srcRec, dstRec, origin, 0, enemyWeapon.sprite.color);
                }
            });

            // Draw Projectiles
            registry.view<SpriteData, Transform, Projectile>().each([](SpriteData &sprite, Transform &pos){
                Rectangle dstRec = {pos.translation.x, pos.translation.y, pos.scale.x, pos.scale.y};
                Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                DrawTexturePro(sprite.curentTexture, sprite.srcRec, dstRec, origin, pos.rotation.x, sprite.color);
            });

            // Draw NPCs
            registry.view<SpriteData, Transform, NPC>().each([](SpriteData &sprite, Transform &transform){
                Rectangle dstRec = {transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y};
                Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
                DrawTexturePro(sprite.curentTexture, sprite.srcRec, dstRec, origin, transform.rotation.x, sprite.color);
            });

            // Draw Health Upgrades
    TraceLog(LOG_TRACE, "Drawing Health Upgrades");
    registry.view<SpriteData, Transform, HealthUpgrade>().each([](SpriteData &sprite, Transform &transform){
        Rectangle dstRec = {transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y};
        Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
        TraceLog(LOG_INFO, "Drawing Health Upgrade at: %f,%f", dstRec.x, dstRec.y);
        TraceLog(LOG_INFO, "Width/Height: %f,%f", dstRec.width, dstRec.height);
        DrawTexturePro(sprite.curentTexture, sprite.srcRec, dstRec, origin, transform.rotation.x, sprite.color);
    });

    TraceLog(LOG_TRACE, "Drawing Upgrades");
        registry.view<SpriteData, Transform, Upgrade>().each([](SpriteData &sprite, Transform &transform){
            Rectangle dstRec = {transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y};
            Vector2 origin = {0.0f, 0.0f}; // Top-left corner as origin
            TraceLog(LOG_INFO, "Drawing Upgrade at: %f,%f", dstRec.x, dstRec.y);
            DrawTexturePro(sprite.curentTexture, sprite.srcRec, dstRec, origin, transform.rotation.x, sprite.color);
        });


                
                // Draw text
                const char* msg = "Move A/D, Jump SPACE";
                //DrawRectangle(8, 8, MeasureText(msg, 20) + 4, 24, Fade(BLACK, 0.5f));
                //DrawText(msg, 10, 10, 20, WHITE);
                
                // Draw dialogue boxes for NPCs
                DrawDialogue(registry);
        
            });
            EndMode2D(); // End 2D camera mode
            // Draw HUD
            DrawHealthHUD(registry);
    });
    EndDrawing();
    TraceLog(LOG_TRACE, "Exiting Function: Render (main)");
}

void RenderTitleScreen(const Vector2 &screenSize, Texture2D buttonTexture, Texture2D button2Texture, Rectangle btnBounds, Rectangle btn2Bounds, Rectangle sourceRec, Rectangle sourceRec2, Texture2D backgroundTexture, Texture2D titleTexture) {
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
    
    // Draw first button (Start Game)
    Vector2 btnPosition = { btnBounds.x, btnBounds.y };
    DrawTextureRec(buttonTexture, sourceRec, btnPosition, WHITE);
    
    // Draw second button (Controls)
    Vector2 btn2Position = { btn2Bounds.x, btn2Bounds.y };
    DrawTextureRec(button2Texture, sourceRec2, btn2Position, WHITE);
    
    EndDrawing();
}

void RenderControlsScreen(const Vector2 &screenSize, Texture2D controlsTexture) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    // Draw controls image centered on screen
    Rectangle controlsSource = { 0, 0, (float)controlsTexture.width, (float)controlsTexture.height };
    float scale = 1.0f;
    Rectangle controlsDest = { 
        (screenSize.x - controlsTexture.width * scale) / 2, 
        (screenSize.y - controlsTexture.height * scale) / 2,
        controlsTexture.width * scale, 
        controlsTexture.height * scale 
    };
    Vector2 controlsOrigin = { 0, 0 };
    DrawTexturePro(controlsTexture, controlsSource, controlsDest, controlsOrigin, 0.0f, WHITE);
    
    EndDrawing();
}

int main() {
    // Set log level
    SetTraceLogLevel(LOG_NONE);

    // Window setup
    float accumulator = 0.0f;             // Keeps track of leftover frame time
    const float dt = 1.0f / 60.0f;        // 60 FPS physics step

    const Vector2 screenSize { 1920, 1080};
    InitWindow(screenSize.x, screenSize.y, "CS370");
    // ToggleFullscreen();
 	SetTargetFPS(60);
    SetExitKey(KEY_NULL);  // Disable ESC from closing the window



    // Load title texture
    Texture2D titleTexture = LoadTexture("assets/graphics/title/milksong_logo.png");

    // Load button textures
    Texture2D buttonTexture = LoadTexture("assets/graphics/title/button.png");
    Texture2D button2Texture = LoadTexture("assets/graphics/title/button2.png");

    // Load background texture
    Texture2D backgroundTexture = LoadTexture("assets/graphics/bgart/mainbackground.png");
    
    // Load controls texture
    Texture2D controlsTexture = LoadTexture("assets/graphics/bgart/controls.png");
    
    // Define source rectangle for button
    Rectangle sourceRec = { 0, 0, (float)buttonTexture.width, (float)buttonTexture.height };
    Rectangle sourceRec2 = { 0, 0, (float)button2Texture.width, (float)button2Texture.height };
    
    // Define button bounds on screen
    Rectangle btnBounds = { 
        screenSize.x/2.0f - buttonTexture.width/2.0f, 
        screenSize.y/2.0f + 100.0f, 
        (float)buttonTexture.width, 
        (float)buttonTexture.height 
    };
    
    Rectangle btn2Bounds = { 
        screenSize.x/2.0f - button2Texture.width/2.0f, 
        screenSize.y/2.0f + 250.0f, 
        (float)button2Texture.width, 
        (float)button2Texture.height 
    };
    
    bool btnAction = false;         // Button action should be activated
    bool btn2Action = false;        // Second button action
    Vector2 mousePoint = { 0.0f, 0.0f };


    // Create entt registry
    entt::registry registry = entt::registry();

    // init game state
    CreateGameState(registry);
    // get Game state
    entt::entity gameState = registry.view<GameState>().front();
    GameScreen &currentScreen = registry.get<GameScreen>(gameState);

    bool gameInitialized = false;

    // Main game loop
    while (!WindowShouldClose()) {
        float frameTime = GetFrameTime();
        mousePoint = GetMousePosition();
        btnAction = false;
        btn2Action = false;


        // Update music streams
        UpdateMusic(registry);

        // Handle ESC key - return to title screen
        if (IsKeyDown(KEY_ESCAPE)) {
            if (currentScreen != TITLE) {
                // Stop gameplay music and restart title music if coming from gameplay
                if (currentScreen == GAMEPLAY) {
                    StopMusicStream(gameplayMusic);
                    PlayMusicStream(titleMusic);
                }
                currentScreen = TITLE;
            }
        }

        // Update based on current screen
        switch (currentScreen) {
            case TITLE:
            {
                // Check button states
                if (CheckCollisionPointRec(mousePoint, btnBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
                }
                
                if (CheckCollisionPointRec(mousePoint, btn2Bounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btn2Action = true;
                }
                
                // Check if start button was clicked
                if (btnAction) {
                    PlaySound(titleMooSound);
                    StopAllMusic(registry);
                    StartSong(registry, "gameplay");
                    currentScreen = GAMEPLAY;
                    
                    // Initialize game only once
                    if (!gameInitialized) {
                        // Load TMX map using RayTMX
                        CreateMap(registry, "assets/tiled/stage1.tmx");
                        CreateCamera(registry, screenSize); 

                        // Player setup
                        // Create player entity
                        CreatePlayer(registry);

                        SpawnEnemies(registry);

                        SpawnNPCs(registry);

                        SpawnHealthUpgrades(registry);

                        SpawnUpgrades(registry);
                        
                        gameInitialized = true;
                    }
                }
                
                // Check if controls button was clicked
                if (btn2Action) {
                    currentScreen = CONTROLS;
                }
            } break;
            
            case CONTROLS:
            {
                // No update logic needed for controls screen
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
                RenderTitleScreen(screenSize, buttonTexture, button2Texture, btnBounds, btn2Bounds, sourceRec, sourceRec2, backgroundTexture, titleTexture);
            } break;
            
            case CONTROLS:
            {
                // Drawing controls screen
                RenderControlsScreen(screenSize, controlsTexture);
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
    UnloadTexture(button2Texture);
    UnloadTexture(controlsTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(titleTexture);
    UnloadSound(titleMooSound);
    CloseAudioDevice();   
    CloseWindow();
    registry.view<HUDResources>().each([&](HUDResources &hud) {
        UnloadTexture(hud.heart);
    });

    return 0;
}