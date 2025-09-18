// CS370.cpp
#include <iostream>
#include "../include/raylib.h"

#define CHAR_WIDTH 32.0f
#define CHAR_HEIGHT 64.0f

using namespace std;

struct My_Texture {
	Texture2D texture;
	float width;
	float height;
   	Rectangle sourceRec;

	My_Texture(std::string filePath, float frameW, float frameH){
		// Default constructor
		texture = LoadTexture(filePath.c_str());
		width = frameW;
		height = frameH;
		sourceRec = { 0.0f, 0.0f, frameW, frameH};
	}
};

struct Transform2D {
	Vector2 translation;    // Translation
	Vector2 scale;          // Scale
	float rotation;			// Rotation

	Transform2D(Vector2 pos, Vector2 scl, float rot) {
		translation = pos;
		scale = scl;
		rotation = rot;
	}
};

struct Stats{
	float moveSpeed = 0;

	Stats(float speed) {
		moveSpeed = speed;
	}
};

void update(entt::registry& registry, float dt) {

	// Update all entities with Transform and Texture components
	registry.view<Transform2D, Stats>().each([dt](auto& transform, auto& stats) {
		// Example update logic: Move the entity to the right
		transform.translation.x += stats.moveSpeed * dt; // Move right by 1 unit per update
	});

	// Move box based on key input
	/*
	if (IsKeyDown(KEY_D)) boxPosition.x += speed * dt;
	if (IsKeyDown(KEY_A)) boxPosition.x -= speed * dt;
	if (IsKeyDown(KEY_W)) boxPosition.y -= speed * dt;
	if (IsKeyDown(KEY_S)) boxPosition.y += speed * dt;
	
	// Constrain box to stay within screen bounds
	if (boxPosition.x < 0) boxPosition.x = 0;
	if (boxPosition.y < 0) boxPosition.y = 0;
	if (boxPosition.x > screenWidth - boxSize.x) boxPosition.x = screenWidth - boxSize.x;
	if (boxPosition.y > screenHeight - boxSize.y) boxPosition.y = screenHeight - boxSize.y;
	*/
}

void draw(entt::registry& registry) {
	// Draw all entities with Transform and Texture components
	registry.view<Transform2D, My_Texture>().each([](auto& transform, auto& texture) {
		// Draw the texture at the entity's position
		DrawTexturePro(texture.texture,
			texture.sourceRec,
			Rectangle{
				transform.translation.x, transform.translation.y,
				texture.width, texture.height
			},
			{0.0f, 0.0f},
			transform.rotation,
			BLACK);
	});
}



int main()
{
	// Create the main window	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "CS370");
	ToggleFullscreen();

	
	//init variables
	const float gravity = 1000.0f;

	 // Box properties
    Vector2 boxPosition = {400.0f, 300.0f};   // Start in middle
    Vector2 boxSize = {50, 50};         // Width & height
	Vector2 boxVol = {0.0f, 0.0f};      // Box Volocity
	 // Box properties
    Vector2 boxPosition = {400.0f, 300.0f};   // Start in middle
    Vector2 boxSize = {50, 50};         // Width & height
	Vector2 boxVol = {0.0f, 0.0f};      // Box Volocity
    float speed = 400.0f;               // Pixels per second
	float jumpStrength = -400.0f;       // Initial upward velocity


	/* ball
	Texture2D ball = LoadTexture("../assets/cool-sports-ball.png");

    int frameWidth = ball.width;
    int frameHeight = ball.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { screenWidth/2.0f, screenHeight/2.0f, frameWidth/2.0f, frameHeight/2.0f };

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin = { destRec.width/2, destRec.height/2 };

    int rotation = 0;
	*/

	// Main game loop
    SetTargetFPS(60);
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{

		// Update
		rotation++;

		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);

		EndDrawing();
	}

	// Cleanup
	UnloadTexture(cow);
	UnloadTexture(background);
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