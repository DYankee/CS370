// CS370.cpp
// CS370.cpp
#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"

// Include all ECS headers
#include "entities/entities.hpp"
#include "components/components.hpp"
#include "systems/systems.hpp"

// Include RayTMX in C linkage
extern "C" {
    #define RAYTMX_IMPLEMENTATION
    #include "../include/raytmx.h"
}

using namespace std;

// Player and physics constants
#define CHAR_WIDTH 32
#define CHAR_HEIGHT 32
#define GRAVITY 1000.0f          // Gravity strength 
#define SPEED 400.0f             // speed 
#define JUMP_STRENGTH -700.0f    // Negative because y-axis goes down

int main() {
    // Create entt registry
    entt::registry registry = entt::registry();

    // Window setup
    float accumulator = 0.0f;                     // Keeps track of leftover frame time
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
    TmxMap* map = LoadTMX("assets/tiled/stage1.tmx");
    if (!map) {
        cerr << "Failed to load TMX map" << endl;
        CloseWindow();
        return -1;
    }
    entt::entity mapEntity = registry.create();
    registry.emplace<TmxMap>(mapEntity, map);
    registry.emplace<Map>(mapEntity, Map());
    
    // Camera
    Camera2D camera;
    camera.zoom = 2.0f; // Adjust zoom level as needed
    camera.target.x = (float)(map->width * map->tileWidth) / 2.0f;
    camera.target.y = (float)(map->height * map->tileHeight) / 2.0f;
    camera.offset.x = (float)screenWidth / 2.0f;
    camera.offset.y = (float)screenHeight / 2.0f;
    camera.rotation = 0.0f;

    // Player setup
    // Create player entity
    createPlayer(registry, camera);

    // load health sprite 
    Texture2D heart = LoadTexture("assets/sprites/CowFace.png");
    Vector2 healthPos = { 20, 30 }; // top left
    const int iconSpacing = 50;     // space between icons

    // Define source and destination rectangles for drawing
    // camera.target = boxPosition;

    //collision settings
    float iFrames = 0.0f;        // remaining i frame
    const float maxIFrames = 1.0f; // 1 second of i frame
    float knockbackX = 200.0f;    // horizontal knockback
    float knockbackY = -300.0f;   // vertical knockback


    // Main game loop
    while (!WindowShouldClose()) {
        // Add frame time to accumulator
        accumulator += GetFrameTime();

        UpdateMusicStream(music); // Keep music playing
        while (accumulator >= dt) {
            // Check collisions with spike objects
            if (iFrames <= 0.0f) {
                
                // find object layer named "Spikes"
                TmxLayer* spikesLayer = FindLayerByName(map->layers, map->layersLength, "Spikes");
                if (spikesLayer != NULL && spikesLayer->type == LAYER_TYPE_OBJECT_GROUP) {
                    TmxObject hitObj;
                    bool hit = CheckCollisionTMXObjectGroupRec(spikesLayer->exact.objectGroup, playerRec, &hitObj);
                    if (hit) {
                        // handle damage/response
                        playerHealth -= 1;
                        // Apply knockback
                        if (boxVel.x >= 0) { 
                            boxVel.x = -knockbackX;
                        } else {              
                            boxVel.x = knockbackX;
                        }
                        boxVel.y = knockbackY;

                        // Start i frames
                        iFrames = maxIFrames;
                       
                        cout << "Ouch! Health: " << playerHealth << endl;
                    }
                }
            }
            }
            
            if (iFrames > 0.0f) {
            iFrames -= dt;
            cowColor = Fade(RED, 0.5f);
            }
            else {
                cowColor = WHITE;
            }

            // Check collisions against tile layers
            TmxObject hitObj;
            bool collided = CheckCollisionTMXTileLayersRec(
                map, map->layers, map->layersLength, playerRec, &hitObj
            );

            if (collided) {
                // Vertical collision only
                Vector2 vertPos = { boxPosition.x, nextPos.y };
                Rectangle vertRec = { vertPos.x, vertPos.y, boxSize.x, boxSize.y };
                if (!CheckCollisionTMXTileLayersRec(map, map->layers, map->layersLength, vertRec, &hitObj)) {
                    boxPosition.y = nextPos.y;
                } else {
                    boxVel.y = 0; // Stop vertical movement
                }

                // Horizontal collision only
                Vector2 horizPos = { nextPos.x, boxPosition.y };
                Rectangle horizRec = { horizPos.x, horizPos.y, boxSize.x, boxSize.y };
                if (!CheckCollisionTMXTileLayersRec(map, map->layers, map->layersLength, horizRec, &hitObj)) {
                    boxPosition.x = nextPos.x;
                } else {
                    boxVel.x = 0; // Stop horizontal movement
                }
            } else {
                // No collision: accept movement
                boxPosition = nextPos;
            }

            // Load new map if player walks out of bounds
		    if(boxPosition.x < 0.0f) {
			    UnloadTMX(map);
			    map = LoadTMX("assets/tiled/stage2.tmx");
    		    if (!map) {
        		    cerr << "Failed to load TMX map" << endl;
        		    CloseWindow();
        		    return -1;
    		    }
			    boxPosition = {400.0f, 300.0f}; // Start in middle
		    }
            if(boxPosition.y > screenWidth) {
                UnloadTMX(map);
			    map = LoadTMX("assets/tiled/stage1.tmx");
    		    if (!map) {
        		    cerr << "Failed to load TMX map" << endl;
        		    CloseWindow();
        		    return -1;
    		    }
			    boxPosition = {400.0f, 300.0f}; // Start in middle
            }
            // Decrease accumulator by one physics step
            accumulator -= dt;
        }

        // Update destination rectangle for drawing
        dstRec.x = boxPosition.x;
        dstRec.y = boxPosition.y;

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera); // Start 2D camera mode
        AnimateTMX(map); // Update animated tiles
        DrawTMX(map, &camera, 0, 0, WHITE); // Draw tile map with parallax support

        // Draw player
        auto cowSprite = registry.view<SpriteData, Player>();
        
        cowSprite.each([](auto entity, SpriteData sprite, Player&) {
            DrawTexturePro(*sprite.curentTexture, sprite.srcRec, dstRec, origin, 0.0f, cowColor);
        });

        
        EndMode2D(); // End 2D camera mode
        
        //show health
        for (int i = 0; i < maxHealth; i++) {
            Vector2 pos = { healthPos.x + i * iconSpacing, healthPos.y };
            if (i < playerHealth) {
                DrawTexture(heart, pos.x, pos.y, WHITE);
            } else {
                DrawTexture(heart, pos.x, pos.y, Fade(WHITE, 0.2f));
            }
        }

        // Draw text
        const char* msg = "Move A/D, Jump SPACE";
        DrawRectangle(8, 8, MeasureText(msg, 20) + 4, 24, Fade(BLACK, 0.5f));
        DrawText(msg, 10, 10, 20, WHITE);

        EndDrawing();
    }
    // Cleanup
    UnloadMusicStream(music);
    UnloadTMX(map);
    CloseAudioDevice();   
    CloseWindow();

    return 0;
}