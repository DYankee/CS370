// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"

using namespace std;

//DEFINES
//player stats
#define START_POS_X 400.0f
#define START_POS_Y 300.0f
#define PLAYER_WIDTH 50.0f
#define PLAYER_HEIGHT 50.0f
#define PLAYER_SPEED 400.0f
#define JUMP_STRENGTH -400.0f
#define GRAVITY 1000.0f
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

enum EntityType{ PLAYER, ENEMY};

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
struct EntityInfo {
	EntityType type = PLAYER;

	EntityInfo(EntityType type) {
		this->type = type;
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

void Update(entt::registry& registry, float dt) {
	//Update the player
	registry.view<Transform2D, Stats, physicsObject, EntityInfo>().each([dt](
		auto& transform, auto& stats, auto& physicsObj, auto& entityInfo) {
			if (entityInfo.type == PLAYER) {
				PlayerMovement(transform, stats, physicsObj, dt);
			}
			std::string logInfo = "Player Position: x=" +
			to_string(transform.translation.x) + ", y=" + 
			to_string(transform.translation.y);
			TraceLog(LOG_INFO, logInfo.c_str()); 
		}
		//update other entities
	);
}

void Draw(entt::registry& registry) {

	// Draw all entities with Transform and Texture components
	registry.view<Transform2D, My_Texture>().each([](auto& transform, auto& texture) {
		// Draw the texture at the entity's position
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
}

void PlayerMovement(Transform2D& transform, Stats& stats, physicsObject& physicsObj, float dt) {

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

int main()
{
	// Create entt registry
	entt::registry registry = entt::registry();
	
	// Create the main window	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "CS370");
	ToggleFullscreen();
	
	//init variables
	const float gravity = 1000.0f;

	//init player
	entt::entity entity = registry.create();
	registry.emplace<EntityInfo>(entity, EntityInfo(PLAYER));
	registry.emplace<Transform2D>(entity, Transform2D({START_POS_X, START_POS_Y}, {PLAYER_WIDTH, PLAYER_HEIGHT}, 0.0f));
	registry.emplace<My_Texture>(entity, My_Texture("../assets/cow.png"));
	registry.emplace<Stats>(entity, Stats(PLAYER_SPEED, JUMP_STRENGTH));
	registry.emplace<physicsObject>(entity, physicsObject({ 0.0f, 0.0f }));

	// Load background texture
	Texture2D background = LoadTexture("../assets/bg.png");

    // Source rectangle (part of the texture to use for drawing)
    //Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    // Destination rectangle (screen rectangle where drawing part of texture)
    //Rectangle destRec = { boxPosition.x, boxPosition.y, (float)boxSize.x, (float)boxSize.y };

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    //Vector2 origin = { 0, 0 };

    //int rotation = 0;

	// Main game loop
    SetTargetFPS(60);
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{

		float dt = GetFrameTime(); // Time since last frame

		Update(registry, dt);		
		

		// Draw
		BeginDrawing();
		DrawTexturePro(background, 
			{0, 0, (float)background.width, (float)background.height}, 
			{0, 0, (float)screenWidth, (float)screenHeight}, 
			{0, 0}, 0, WHITE);
        DrawText("Move with W A S D", 10, 10, 20, BLACK);
		Draw(registry);
		//DrawTexturePro(cow, sourceRec, destRec, origin, (float)rotation, WHITE); // Draw cow over the box
		//DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);
		EndDrawing();
	}

	// Cleanup
	UnloadTexture(background);
	CloseWindow();

	return 0;
}
