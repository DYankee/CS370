// CS370.cpp
// CS370.cpp
#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"

// Include RayTMX in C linkage
extern "C" {
    #define RAYTMX_IMPLEMENTATION
    #include "../include/raytmx.h"
}

using namespace std;

//DEFINES
//player stats
#define START_POS_X 400.0f
#define START_POS_Y 300.0f
#define PLAYER_WIDTH 32.0f
#define PLAYER_HEIGHT 32.0f
#define PLAYER_SPEED 400.0f
#define JUMP_STRENGTH -400.0f
#define GRAVITY 1000.0f
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

struct IsPlayer{};

struct My_Texture {
	Texture2D texture;
	Vector2 frameSize;
   	Rectangle sourceRec;
	My_Texture(std::string filePath) {
		// Default constructor
		texture = LoadTexture(filePath.c_str());
		sourceRec = { 0.0f, 0.0f, float(texture.width), float(texture.height)};
	}
};

struct Transform2D {
	Vector2 translation;    // Translation
	Vector2 size;          	// Scale
	float rotation;			// Rotation

	Transform2D(Vector2 position, Vector2 scale, float rotation) {
		this->translation = position;
		this->size = scale;
		this->rotation = rotation;
	}
};
struct physicsObject {
	Vector2 velocity;      // Velocity

	physicsObject(Vector2 velocity) {
		this->velocity = velocity;
	}
};

struct Stats{
	float moveSpeed = 0;
	float jumpStrength = 0;

	Stats(float moveSpeed, float jumpStrength){
		this->moveSpeed = moveSpeed;
		this->jumpStrength = jumpStrength;
	}
};

struct Map{
	TmxMap* map;
	
	Map(std::string filePath){
		map = LoadTMX(filePath.c_str());
		if (!map) {
			TraceLog(LOG_ERROR, "Failed to load map: %s", filePath.c_str());
			exit(1);
		}	
	}
};

struct IsMap{};

void PlayerMovement(entt::registry& registry, float dt) {
	// Get the player entity and necessary components
	auto playerView = registry.view<IsPlayer, Transform2D, Stats, physicsObject>();
	auto entity = playerView.front();
	auto& transform = playerView.get<Transform2D>(entity);
	auto& stats = playerView.get<Stats>(entity);
	auto& physicsObj = playerView.get<physicsObject>(entity);

	transform.rotation += 100.0f * dt;
	if (transform.rotation > 360.0f) transform.rotation -= 360.0f;
	// Apply gravity to box velocity
	physicsObj.velocity.y += GRAVITY * dt; // Update velocity based on gravity

	// Move box based on key input
	if (IsKeyPressed(KEY_SPACE)) // if player hits space jump 
	{
  			physicsObj.velocity.y = stats.jumpStrength; // player jumps using jump strength
	}

	if (IsKeyDown(KEY_D)) transform.translation.x += stats.moveSpeed * dt; // move left
	if (IsKeyDown(KEY_A)) transform.translation.x -= stats.moveSpeed * dt; // move left

	transform.translation.y += physicsObj.velocity.y * dt; // update player position based on velocity

	// Constrain box to stay within screen bounds
	if (transform.translation.x < 0) transform.translation.x = 0;
	if (transform.translation.y < 0) transform.translation.y = 0;
	if (transform.translation.x > SCREEN_WIDTH - transform.size.x) transform.translation.x = SCREEN_WIDTH - transform.size.x;
	if (transform.translation.y > SCREEN_HEIGHT - transform.size.y) transform.translation.y = SCREEN_HEIGHT - transform.size.y;

}

void Update(entt::registry& registry, float dt) {
	//Update the player
	PlayerMovement(registry, dt);
}

void Draw(entt::registry& registry) {
	//Clear the background and begin drawing
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	//get the stage map
	auto mapView = registry.view<IsMap, Map>();
	auto mapEntity = mapView.front();
	auto& stageMap = mapView.get<Map>(mapEntity);

	//draw the stage map
	DrawTMX(stageMap.map, NULL, 0, 0, WHITE);

	// Draw all entities with Transform and Texture components
	registry.view<Transform2D, My_Texture>().each([](auto& transform, auto& texture) {
		// Draw the texture at the entity's position
		TraceLog(LOG_INFO, "Drawing entity at position (%f, %f) Rotation (%f)",
			transform.translation.x,
			transform.translation.y,
			transform.rotation);
		DrawTexturePro(texture.texture,
			texture.sourceRec,
			Rectangle{
				transform.translation.x,
				transform.translation.y,
				transform.size.x,
				transform.size.y
			},
			{0.0f, 0.0f},
			transform.rotation,
			WHITE);
	});

    //Draw UI
    const char* instructionText = "Move with W A S D. Jump with SPACE";
    DrawRectangle(8, 8, MeasureText(instructionText, 20) + 4, 24, Fade(BLACK, 0.5f));
	DrawText(instructionText, 10, 10, 20, WHITE);

	//End drawing
	EndDrawing();
}

// Player and physics constants
#define CHAR_WIDTH 32
#define CHAR_HEIGHT 32
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
    TmxMap* map = LoadTMX("../assets/tiled/stage2.tmx");
    if (!map) {
        cerr << "Failed to load TMX map" << endl;
        CloseWindow();
        return -1;
    }

    // Camera
    Camera2D camera;
    camera.zoom = 3.5f; // Adjust zoom level as needed -- 3.5 is zoomed enough to hide the empty bottom tiles
    camera.target.x = (float)(map->width * map->tileWidth) / 2.0f;
    camera.target.y = (float)(map->height * map->tileHeight) / 2.0f;
    camera.offset.x = (float)screenWidth / 2.0f;
    camera.offset.y = (float)screenHeight / 2.0f;
    camera.rotation = 0.0f;

    // Player setup
    Vector2 boxPosition = {400.0f, 300.0f}; // Start in middle
    Vector2 boxVel = {0.0f, 0.0f};     // Box Velocity
    Vector2 boxSize = {CHAR_WIDTH, CHAR_HEIGHT}; // Width & height
    camera.target = boxPosition; // Center camera on player

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

        // Update camera to follow the player
        camera.target = boxPosition;

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera); // Start 2D camera mode
        AnimateTMX(map); // Update animated tiles
        DrawTMX(map, NULL, 0, 0, WHITE); // Draw tile map
        DrawTexturePro(currentCow, srcRec, dstRec, origin, 0.0f, WHITE); // Draws cow
        EndMode2D(); // End 2D camera mode

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