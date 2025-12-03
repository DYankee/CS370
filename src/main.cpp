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

using namespace std;


void Update(entt::registry &registry, float dt, GameScreen &currentScreen) {
    TraceLog(LOG_INFO, "Entering main update function");
    UpdateProjectiles(registry, dt);
    PlayerInputSystem(registry, dt);
    UpdateEnemies(registry, dt);
    UpdateNPCs(registry, dt);
    UpdateProjectiles(registry, dt);
    PlayerEnemyCollisionSystem(registry, dt);
    CameraUpdate(registry, dt);
    SpikeCollision(registry, dt);
    CheckForMapChange(registry);
    UpdateMap(registry, dt);
    UpdateIFrames(registry, dt);
    UpdateHealthUpgrades(registry, dt);
    PlayerHealthCollisionSystem(registry, dt);
    UpdateDialogue(registry, dt);
    CheckForPlayerDeath(registry, currentScreen);
    TraceLog(LOG_INFO, "Exiting main update function");
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

void RenderDeathScreen(const Vector2 &screenSize, Texture2D backgroundTexture, Texture2D deathTexture, 
    Texture2D restartButtonTexture, Rectangle restartBounds, Rectangle restartSourceRec,
    Texture2D quitButtonTexture, Rectangle quitBounds, Rectangle quitSourceRec
){
    BeginDrawing();

    // Draw background
    Rectangle bgSource = { 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height };
    Rectangle bgDest = { 0, 0, screenSize.x, screenSize.y };
    Vector2 bgOrigin = { 0, 0 };
    DrawTexturePro(backgroundTexture, bgSource, bgDest, bgOrigin, 0.0f, WHITE);

    // Draw death texture
    Rectangle deathSource = { 0, 0, (float)deathTexture.width, (float)deathTexture.height };
    float deathScale = 1.0f;
    Rectangle deathDest = { 
        (screenSize.x - deathTexture.width * deathScale) / 2, 50.0f,
        deathTexture.width * deathScale, 
        deathTexture.height * deathScale 
    };
    Vector2 deathOrigin = { 0, 0 };
    DrawTexturePro(deathTexture, deathSource, deathDest, deathOrigin, 0.0f, WHITE);

    // Draw restart button
    Vector2 restartButtonPosition = { restartBounds.x, restartBounds.y };
    DrawTextureRec(restartButtonTexture, restartSourceRec, restartButtonPosition, WHITE);
    
    // Draw quit button
    Vector2 quitButtonPosition = { quitBounds.x, quitBounds.y };
    DrawTextureRec(quitButtonTexture, quitSourceRec, quitButtonPosition, WHITE);

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
    Music titleMusic = LoadMusicStream("assets/audio/acnhtitle.mp3");
    Music gameplayMusic = LoadMusicStream("assets/audio/stardewsummer.mp3");
    Music deathScreenMusic = LoadMusicStream("assets/audio/deathScreen.mp3");
    SetMusicVolume(titleMusic, 1.0f);
    SetMusicVolume(gameplayMusic, 1.0f);
    SetMusicVolume(deathScreenMusic, 1.0f);
    PlayMusicStream(titleMusic);

    // Load sound effects
    Sound titleMooSound = LoadSound("assets/audio/titleMoo.mp3");

    
    
    // Load assets for menu screens
    Texture2D titleTexture = LoadTexture("assets/graphics/title/milksong_logo.png");        // Load title texture
    Texture2D backgroundTexture = LoadTexture("assets/graphics/bgart/mainbackground.png");  // Load background texture
    Texture2D startButtonTexture = LoadTexture("assets/graphics/title/button.png");         // Load start button texture
    Texture2D restartButtonTexture = LoadTexture("assets/graphics/title/button.png");       // Load restart button texture
    Texture2D quitButtonTexture = LoadTexture("assets/graphics/title/button.png");          // Load quit button texture
    
    // Define source rectangles for buttons
    Rectangle startSourceRec = { 0, 0, (float)startButtonTexture.width, (float)startButtonTexture.height };
    Rectangle restartSourceRec = { 0, 0, (float)restartButtonTexture.width, (float)restartButtonTexture.height };
    Rectangle quitSourceRec = { 0, 0, (float)quitButtonTexture.width, (float)quitButtonTexture.height };
    
    // Define button bounds on screen
    Rectangle startBounds = { 
        screenSize.x/2.0f - startButtonTexture.width/2.0f, 
        screenSize.y/2.0f + 100.0f, 
        (float)startButtonTexture.width, 
        (float)startButtonTexture.height 
    };
    Rectangle restartBounds = { 
        screenSize.x/2.0f - restartButtonTexture.width/2.0f, 
        screenSize.y/2.0f + 100.0f, 
        (float)restartButtonTexture.width, 
        (float)restartButtonTexture.height 
    };
    Rectangle quitBounds = { 
        screenSize.x/2.0f - quitButtonTexture.width/2.0f, 
        screenSize.y/2.0f + 300.0f, 
        (float)quitButtonTexture.width, 
        (float)quitButtonTexture.height 
    };
   
    // Button states
    bool startButtonAction = false;
    bool restartButtonAction = false;
    bool quitButtonAction = false;

    // Mouse position
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
        startButtonAction = false;

        // Update music streams
        UpdateMusicStream(titleMusic);
        UpdateMusicStream(gameplayMusic);
        UpdateMusicStream(deathScreenMusic);

        // Handle ESC key to close
        if (IsKeyDown(KEY_ESCAPE)) {
            break;
        }

        // Update based on current screen
        TraceLog(LOG_INFO,"Main update loop: CurrentScreen()");
        switch (currentScreen) {
            case TITLE:
            {
                TraceLog(LOG_INFO, "Updating title screen");
                // Check button state
                if (CheckCollisionPointRec(mousePoint, startBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) startButtonAction = true;
                }
                
                // Check if button was clicked to start the game
                if (startButtonAction) {
                    PlaySound(titleMooSound);
                    StopMusicStream(titleMusic);
                    PlayMusicStream(gameplayMusic);
                    currentScreen = GAMEPLAY;
                    
                    // Initialize game only once
                    if (!gameInitialized) {
                        // Load TMX map using RayTMX
                        CreateMap(registry, "assets/tiled/stage1.tmx", gameplayMusic);
                        CreateCamera(registry, screenSize); 

                        // Player setup
                        // Create player entity
                        CreatePlayer(registry);

                        SpawnEnemies(registry);

                        SpawnNPCs(registry);

                        SpawnHealthUpgrades(registry);
                        
                        gameInitialized = true;
                    }
                }
            } break;
            
            case GAMEPLAY:
            {
                // Update Game State
                TraceLog(LOG_INFO, "Updating game state");
                Update(registry, frameTime, currentScreen);
            } break;

            case DEATH:
            {
                TraceLog(LOG_INFO, "Updating death screen");
                StopMusicStream(gameplayMusic);
                PlayMusicStream(deathScreenMusic);
                // Check button state
                if (CheckCollisionPointRec(mousePoint, restartBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) restartButtonAction = true;
                }
                if (CheckCollisionPointRec(mousePoint, quitBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) quitButtonAction = true;
                }

                if(quitButtonAction){
                    CloseWindow();
                    break;
                }

                if (restartButtonAction){
                    StopMusicStream(deathScreenMusic);
                    ChangeMap(registry, "assets/tiled/stage1.tmx");
                    currentScreen = GAMEPLAY;
                }
            } break;
            
            default: break;
        }

        // Render based on current screen
        switch (currentScreen) {
            case TITLE:
            {
                // Drawing title screen
                TraceLog(LOG_INFO, "Rendering title screen");
                RenderTitleScreen(screenSize, startButtonTexture, startBounds, startSourceRec, backgroundTexture, titleTexture);
            } break;
            
            case GAMEPLAY:
            {
                // Drawing gameplay
                Render(registry, frameTime);
            } break;

            case DEATH:
            {
                TraceLog(LOG_INFO, "Rendering death screen");
                RenderDeathScreen(screenSize, backgroundTexture, titleTexture,
                    restartButtonTexture, restartBounds, restartSourceRec,
                    quitButtonTexture, quitBounds, quitSourceRec
                );
            } break;
            
            default: break;
        }
    }
    
    // Cleanup
    UnloadTexture(startButtonTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(titleTexture);
    UnloadSound(titleMooSound);
    UnloadMusicStream(titleMusic);
    UnloadMusicStream(gameplayMusic);
    CloseAudioDevice();   
    CloseWindow();
    registry.view<HUDResources>().each([&](HUDResources &hud) {
        UnloadTexture(hud.heart);
    });

    return 0;
}