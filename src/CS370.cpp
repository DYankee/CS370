// CS370.cpp
// CS370.cpp
#include <iostream>

// Include all ECS headers
#include "entities/entities.hpp"
#include "components/components.hpp"
#include "systems/systems.hpp"

#include "../include/raytmx.h"





using namespace std;

// Player and physics constants
#define CHAR_WIDTH 32
#define CHAR_HEIGHT 32
#define GRAVITY 1000.0f          // Gravity strength 
#define SPEED 400.0f             // speed 
#define JUMP_STRENGTH -700.0f    // Negative because y-axis goes down



void Update(entt::registry &registry, float dt) {
    PlayerMovementSystem(registry, dt);
    SpikeCollision(registry, dt);
    TileCollision(registry, dt);
    CheckForMapChange(registry);
    UpdateMap(registry, dt);
};

void Render(entt::registry &registry, float dt) {
    // Update camera to follow the player
    registry.view<Camera2D, Transform, Player, PlayerStats>().each([&registry](Camera2D &camera, Transform &transform, PlayerStats &stats) {
        camera.target.x = transform.translation.x + (transform.scale.x / 2.0f);
        camera.target.y = transform.translation.y + (transform.scale.y / 2.0f);
        
        BeginMode2D(camera); // Start 2D camera mode
        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw TMX map
        registry.view<TmxMap, Map>().each([&registry, &camera](TmxMap &map) {
            // Nothing needed here for now
            AnimateTMX(&map); // Update animated tiles
            DrawTMX(&map, &camera, 0, 0, WHITE); // Draw tile map with parallax support
        });
    
        
        // Draw player
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
    // Create entt registry
    entt::registry registry = entt::registry();

    // Window setup
    float accumulator = 0.0f;             // Keeps track of leftover frame time
    const float dt = 1.0f / 60.0f;        // 60 FPS physics step

    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "CS370");
    //ToggleFullscreen();
 	SetTargetFPS(60);

    // Music setup
    InitAudioDevice();
    Music music = LoadMusicStream("assets/music/stardewsummer.mp3");
    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    // player variables
    const int maxHealth = 3;
    int playerHealth = maxHealth;
    Color cowColor = WHITE;
    float flashTimer = 0.0f;   
    const float flashSpeed = 10.0f;

    // Load TMX map using RayTMX
    CreateMap(registry, "assets/tiled/stage1.tmx", music);
    
    // Camera setup
    // to be moved to separate file later
    Camera2D camera;
    registry.view<TmxMap, Map>().each([&camera](TmxMap &tmxMap) {
        camera.zoom = 2.0f; // Adjust zoom level as needed
        camera.target.x = (float)(tmxMap.width * tmxMap.tileWidth) / 2.0f;
        camera.target.y = (float)(tmxMap.height * tmxMap.tileHeight) / 2.0f;
        camera.offset.x = (float)screenWidth / 2.0f;
        camera.offset.y = (float)screenHeight / 2.0f;
        camera.rotation = 0.0f;
    });

    // Player setup
    // Create player entity
    CreatePlayer(registry, camera);

    // load health sprite 
    Texture2D heart = LoadTexture("assets/sprites/CowFace.png");
    Vector2 healthPos = { 20, 30 }; // top left
    const int iconSpacing = 50;     // space between icons


    // Main game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Update Game State
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