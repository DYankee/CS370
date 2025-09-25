// CS370.cpp
#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"


#define CHAR_WIDTH 32
#define CHAR_HEIGHT 64

using namespace std;

int main()
{
	// Create the main window	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "CS370");
	ToggleFullscreen();


	//init entt registry
	entt::registry registry;
	Texture texture();

	


	//init test entities
	for (size_t i = 0; i < 10; i++)
	{
		//create a new entity
		entt::entity entity = registry.create();
		registry.emplace<Transform>(entity, Vector2{float(i * 50), float(i * 50)}, Vector2{CHAR_WIDTH, CHAR_HEIGHT}, 0.0f);
		registry.emplace<Texture>(entity, "../../../assets/advnt_full.png", CHAR_WIDTH, CHAR_HEIGHT);
	}


	// Box properties
	/*
	Vector2 boxPosition = {400, 300};   // Start in middle
    Vector2 boxSize = {32, 64};         // Width & height
    float speed = 400.0f;               // Pixels per second
	*/

	
	// Main game loop
    SetTargetFPS(60);
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		float dt = GetFrameTime(); // Time since last frame

		// Move box based on key input
		if (IsKeyDown(KEY_D)) boxPosition.x += speed * dt;
		if (IsKeyDown(KEY_A)) boxPosition.x -= speed * dt;
		if (IsKeyDown(KEY_W)) boxPosition.y -= speed * dt;
		if (IsKeyDown(KEY_S)) boxPosition.y += speed * dt;

		// Constrain box to stay within screen bounds
		if (boxPosition.x < 0) boxPosition.x = 0;
		if (boxPosition.y < 0) boxPosition.y = 0;
		if (boxPosition.x > screenWidth - boxSize.x) boxPosition.x = screenWidth - boxSize.x;
		if (boxPosition.y > screenHeight - boxSize.y) boxPosition.y = screenHeight - boxSize.y;

		// Update cow texture position to follow the box
		destRec.x = boxPosition.x;
		destRec.y = boxPosition.y;

		BeginDrawing();
		DrawTexturePro(background, 
			{0, 0, (float)background.width, (float)background.height}, 
			{0, 0, (float)screenWidth, (float)screenHeight}, 
			{0, 0}, 0, WHITE);

		 DrawTexturePro(cow, sourceRec, destRec, origin, (float)rotation, WHITE); // Draw cow over the box

         DrawText("Move with W A S D", 10, 10, 20, BLACK);

		EndDrawing();
	}

	// Cleanup
	UnloadTexture(cow);
	//UnloadTexture(background);
	UnloadTMX(stage1);
	CloseWindow();

	return 0;
>>>>>>> 3e558d3 (added test ui elements to draw over the background and cube)
}

int main() {
    // Window setup
    float accumulator = 0.0f;                     // Keeps track of leftover frame time
    const float dt = 1.0f / 60.0f;        // 60 FPS physics step

    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "CS370");
    ToggleFullscreen();
 	SetTargetFPS(60);

    // Music setup
    InitAudioDevice();
    Music music = LoadMusicStream("../assets/music/stardewsummer.mp3");
    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    // player variables
    const int maxHealth = 3;
    int playerHealth = maxHealth;
    Color cowColor = WHITE;
    float flashTimer = 0.0f;   
    const float flashSpeed = 10.0f;

    // Load TMX map using RayTMX
    TmxMap* map = LoadTMX("../assets/tiled/stage1.tmx");
    if (!map) {
        cerr << "Failed to load TMX map" << endl;
        CloseWindow();
        return -1;
    }

    // Camera
    Camera2D camera;
    camera.zoom = 2.0f; // Adjust zoom level as needed
    camera.target.x = (float)(map->width * map->tileWidth) / 2.0f;
    camera.target.y = (float)(map->height * map->tileHeight) / 2.0f;
    camera.offset.x = (float)screenWidth / 2.0f;
    camera.offset.y = (float)screenHeight / 2.0f;
    camera.rotation = 0.0f;

    // Player setup
    Vector2 boxPosition = {400.0f, 300.0f}; // Start in middle
    Vector2 boxVel = {0.0f, 0.0f};     // Box Velocity
    Vector2 boxSize = {CHAR_WIDTH, CHAR_HEIGHT}; // Width & height

    // Load player sprites
    Texture2D cowR = LoadTexture("../assets/sprites/cowR.png"); 
    Texture2D cowL = LoadTexture("../assets/sprites/cowL.png"); 
    Texture2D currentCow = cowR;  // Default to right-facing cow
    // load health sprite 
    Texture2D heart = LoadTexture("../assets/sprites/CowFace.png");
    Vector2 healthPos = { 20, 30 }; // top left
    const int iconSpacing = 50;     // space between icons

    // Define source and destination rectangles for drawing
    Rectangle srcRec = {0, 0, (float)cowR.width, (float)cowR.height};
    Rectangle dstRec = {boxPosition.x, boxPosition.y, boxSize.x, boxSize.y};
    Vector2 origin = {0, 0}; // Top-left origin
    camera.target = boxPosition;

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
        // Gravity
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

            if (iFrames <= 0.0f) {
            // Check collisions with spike objects
            {
                

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
			    map = LoadTMX("../assets/tiled/stage2.tmx");
    		    if (!map) {
        		    cerr << "Failed to load TMX map" << endl;
        		    CloseWindow();
        		    return -1;
    		    }
			    boxPosition = {400.0f, 300.0f}; // Start in middle
		    }
            if(boxPosition.y > screenWidth) {
                UnloadTMX(map);
			    map = LoadTMX("../assets/tiled/stage1.tmx");
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

        // Update camera to follow the player
        camera.target = boxPosition;

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera); // Start 2D camera mode
        AnimateTMX(map); // Update animated tiles
        DrawTMX(map, &camera, 0, 0, WHITE); // Draw tile map with parallax support
        DrawTexturePro(currentCow, srcRec, dstRec, origin, 0.0f, cowColor); // Draws cow
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
    UnloadTexture(cowR);
    UnloadTexture(cowL);
    UnloadMusicStream(music);
    UnloadTMX(map);
    CloseAudioDevice();   
    CloseWindow();

    return 0;
}