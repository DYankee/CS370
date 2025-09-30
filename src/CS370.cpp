// CS370.cpp
#include <iostream>
#include "../include/raylib.h"

// Include RayTMX in C linkage
extern "C" {
    #define RAYTMX_IMPLEMENTATION
    #include "../include/raytmx.h"
}

using namespace std;

// Player and physics constants
#define CHAR_WIDTH 64
#define CHAR_HEIGHT 64
#define GRAVITY 1000.0f          // Gravity strength 
#define SPEED 400.0f             // speed 
#define JUMP_STRENGTH -500.0f    // Negative because y-axis goes down

int main() {
    // Window setup
   
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "CS370");
    ToggleFullscreen();
 	SetTargetFPS(60);
    // Load TMX map using RayTMX
    TmxMap* map = LoadTMX("../assets/tiled/stage1.tmx");
    if (!map) {
        cerr << "Failed to load TMX map" << endl;
        CloseWindow();
        return -1;
    }
    // Player setup
    Vector2 boxPosition = {400.0f, 300.0f}; // Start in middle
    Vector2 boxVel = {0.0f, 0.0f};     // Box Velocity
    Vector2 boxSize = {CHAR_WIDTH, CHAR_HEIGHT}; // Width & height

    // Load player sprites
    Texture2D cowR = LoadTexture("../assets/sprites/cowR.png"); 
    Texture2D cowL = LoadTexture("../assets/sprites/cowL.png"); 
    Texture2D currentCow = cowR;  // Default to right-facing cow

    // Define source and destination rectangles for drawing
    Rectangle srcRec = {0, 0, (float)cowR.width, (float)cowR.height};
    Rectangle dstRec = {boxPosition.x, boxPosition.y, boxSize.x, boxSize.y};
    Vector2 origin = {0, 0}; // Top-left origin

    // Main game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime(); // Time since last frame
		// Update velocity based on gravity
        boxVel.y += GRAVITY * dt;

        // Move box based on key input
        if (IsKeyDown(KEY_D)) {
            boxVel.x = SPEED;    // Move right
            currentCow = cowR;   // Use right-facing cow
        } else if (IsKeyDown(KEY_A)) {
            boxVel.x = -SPEED;   // Move left
            currentCow = cowL;   // Use left-facing cow
        } else {
            boxVel.x = 0;        // No horizontal movement
        }
        // Only allow jump if player is on the ground
        if (IsKeyPressed(KEY_SPACE)) {
            Rectangle testRec = { boxPosition.x, boxPosition.y + 1, boxSize.x, boxSize.y };
            TmxObject collidedObj;
            bool onGround = CheckCollisionTMXTileLayersRec(
                map, map->layers, map->layersLength, testRec, &collidedObj
            );
            if (onGround) {
                boxVel.y = JUMP_STRENGTH;
            }
        }
        // Calculate new position
        Vector2 nextPos = { boxPosition.x + boxVel.x * dt, boxPosition.y + boxVel.y * dt };
        Rectangle playerRec = { nextPos.x, nextPos.y, boxSize.x, boxSize.y };

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

        // Update destination rectangle for drawing
        dstRec.x = boxPosition.x;
        dstRec.y = boxPosition.y;

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        AnimateTMX(map); // Update animated tiles
        DrawTMX(map, NULL, 0, 0, WHITE); // Draw tile map
        DrawTexturePro(currentCow, srcRec, dstRec, origin, 0.0f, WHITE); // Draws cow

        // Draw text
        const char* msg = "Move A/D, Jump SPACE";
        DrawRectangle(8, 8, MeasureText(msg, 20) + 4, 24, Fade(BLACK, 0.5f));
        DrawText(msg, 10, 10, 20, WHITE);

        EndDrawing();
    }
    // Cleanup
    UnloadTexture(cowR);
    UnloadTexture(cowL);
    UnloadTMX(map);
    CloseWindow();

    return 0;
}
