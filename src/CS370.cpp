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
#define JUMP_STRENGTH -700.0f    // Negative because y-axis goes down



void Update(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: Update (main)");
    PlayerInputSystem(registry, dt);
    MovePlayer(registry, dt);
    CameraUpdate(registry, dt);
    // SpikeCollision(registry, dt);
    // CheckForMapChange(registry);
    UpdateMap(registry, dt);
};

void Render(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: Render (main)");
    // Update camera to follow the player
    registry.view<Transform, Player, PlayerStats>().each([&registry](Transform &transform, PlayerStats &stats) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw TMX map
        
        TraceLog(LOG_TRACE, "Drawing Map");
        registry.view<Camera2D, PlayerCamera>().each([&registry](Camera2D camera){
            BeginMode2D(camera);
            registry.view<TmxMap, Map>().each([&camera](TmxMap &map) {
                AnimateTMX(&map); // Update animated tiles
                DrawTMX(&map, &camera, 0, 0, WHITE); // Draw tile map with parallax support 
        });
        EndMode2D(); // End 2D camera mode
    });
        
        
        // Draw player
        TraceLog(LOG_TRACE, "Drawing Player");
        registry.view<SpriteData, Player>().each([&transform](SpriteData &sprite) {
            Rectangle dstRec = {transform.translation.x, transform.translation.y, transform.scale.x, transform.scale.y};
            Vector2 origin = {transform.translation.x, transform.translation.y}; // Top-left corner as origin
            DrawTexturePro(*sprite.curentTexture, sprite.srcRec, dstRec, origin, transform.rotation.x, sprite.color);
        });
        EndMode2D(); // End 2D camera mode
        
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
        DrawRectangle(8, 8, MeasureText(msg, 20) + 4, 24, Fade(BLACK, 0.5f));
        DrawText(msg, 10, 10, 20, WHITE);

        EndDrawing();
    });
}


int main() {
    // Set log level
    SetTraceLogLevel(LOG_ALL);


    // Create entt registry
    entt::registry registry = entt::registry();

    // Window setup
    float accumulator = 0.0f;             // Keeps track of leftover frame time
    const float dt = 1.0f / 60.0f;        // 60 FPS physics step

    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "CS370");
    // ToggleFullscreen();
 	SetTargetFPS(60);

    // Music setup
    InitAudioDevice();
    Music music = LoadMusicStream("assets/music/stardewsummer.mp3");
    SetMusicVolume(music, 1.0f);
    // PlayMusicStream(music);

    // Load TMX map using RayTMX
    CreateMap(registry, "assets/tiled/stage1.tmx", music);
    CreateCamera(registry); 

    // Player setup
    // Create player entity
    CreatePlayer(registry);

    // load health sprite 
    // Texture2D heart = LoadTexture("assets/sprites/CowFace.png");
    // Vector2 healthPos = { 20, 30 }; // top left
    // const int iconSpacing = 50;     // space between icons


    // Main game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        // Update Game State
        if (IsKeyDown(KEY_ESCAPE)) {
            CloseWindow();
        }
        Update(registry, dt);

            //if (iFrames > 0.0f) {
            //iFrames -= dt;
            //cowColor = Fade(RED, 0.5f);
            //}
            //else {
            //    cowColor = WHITE;
            //}

        // Drawing
        Render(registry, dt);
    }
    // Cleanup
    UnloadMusicStream(music);
    CloseAudioDevice();   
    CloseWindow();

    return 0;
}