// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"


#define RAYTMX_IMPLEMENTATION
#include "../include/raytmx.h"

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

int main()
{
	// Create entt registry
	entt::registry registry = entt::registry();
	
	// Create the main window	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "CS370");
	ToggleFullscreen();

    // Load TMX map
	entt::entity stage1 = registry.create();
	registry.emplace<IsMap>(stage1, IsMap{});
	registry.emplace<Map>(stage1, Map("../assets/tiled/stage1.tmx"));
	
	//init player
	entt::entity player = registry.create();
	registry.emplace<IsPlayer>(player, IsPlayer{});
	registry.emplace<Transform2D>(player, Transform2D({START_POS_X, START_POS_Y}, {PLAYER_WIDTH, PLAYER_HEIGHT}, 0.0f));
	registry.emplace<My_Texture>(player, My_Texture("../assets/sprites/cow.png"));
	registry.emplace<Stats>(player, Stats(PLAYER_SPEED, JUMP_STRENGTH));
	registry.emplace<physicsObject>(player, physicsObject({ 0.0f, 0.0f }));

	// Main game loop
    SetTargetFPS(60);
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		//Get Delta Time
		float dt = GetFrameTime(); // Time since last frame

		//Update game state
		Update(registry, dt);

		//Draw game 
		Draw(registry);
	}

	//UnloadTexture(background);
	CloseWindow();

	return 0;
}