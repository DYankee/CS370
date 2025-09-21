// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"


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
	InitWindow(screenWidth, screenHeight, "CS370");
	ToggleFullscreen();


	//init entt registry
	entt::registry registry;
	
	//init test entities
	for (size_t i = 0; i < 10; i++)
	{
		//create a new entity
		entt::entity entity = registry.create();
		//entity is a reference to the entity we just created
		//All other arguments are passed to the component constructor
		registry.emplace<Transform2D>(entity, Vector2{float(i * 50), float(i * 50)}, Vector2{CHAR_WIDTH, CHAR_HEIGHT}, 0.0f);
		registry.emplace<My_Texture>(entity, "../../../assets/advnt_full.png", CHAR_WIDTH, CHAR_HEIGHT);
		registry.emplace<Stats>(entity, 10.0f * i); //move speed increases with each entity
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

		// Update
		update(registry, dt);

		// Draw
		BeginDrawing();
		draw(registry);
		ClearBackground(RAYWHITE);
		//DrawRectangleV(boxPosition, boxSize, BLUE); // Draw the box
        //DrawText("Move with W A S D", 10, 10, 20, BLACK);
		//DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);
		EndDrawing();
	}
	return 0;
}
