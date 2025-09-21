// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"

#define CHAR_WIDTH 32
#define CHAR_HEIGHT 64

#define RAYTMX_IMPLEMENTATION
#include "../include/raytmx.h"

using namespace std;

/*
struct My_Transform {
	Vector2 position;
	Vector2 size;
	float rotation;
};
struct My_Texture {
	Texture2D texture;
   	Rectangle sourceRec;

	My_Texture(std::string filePath, int frameW, int frameH){
		// Default constructor
		texture = LoadTexture(filePath.c_str());
		sourceRec = { 0.0f, 0.0f, (float)frameW, (float)frameH};
	}
};
*/

void update(entt::registry& registry, float dt) {

	// Update all entities with Transform and Texture components
	registry.view<Transform>().each([dt](auto& transform) {
		// Example update logic: Move the entity to the right
		transform += 1.0f * dt; // Move right by 1 unit per update
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
	registry.view<Transform, Texture>().each([](auto& transform, auto& texture) {
		// Draw the texture at the entity's position
		DrawTexturePro(texture.texture,
			texture.sourceRec,
			Rectangle{
				transform.position.x, transform.position.y,
				transform.size.x, transform.size.y
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

    // Load TMX map
    TmxMap* stage1 = LoadTMX("../assets/tiled/stage1.tmx");
    if (!stage1) {
        cout << "Failed to load stage1.tmx" << endl;
        CloseWindow();
        return -1;
    }
	
	//init variables
	const float gravity = 1000.0f;

	 // Box properties
    Vector2 boxPosition = {400.0f, 300.0f};   // Start in middle
    Vector2 boxSize = {50, 50};         // Width & height
	Vector2 boxVol = {0.0f, 0.0f};      // Box Volocity
    float speed = 400.0f;               // Pixels per second
	float jumpStrength = -400.0f;       // Initial upward velocity

	// Load cow texture
	Texture2D cow = LoadTexture("../assets/sprites/cow.png");

	int frameWidth = cow.width;
    int frameHeight = cow.height;

	// Load background texture
	//Texture2D background = LoadTexture("../assets/sprites/bg.png");

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { boxPosition.x, boxPosition.y, (float)boxSize.x, (float)boxSize.y };

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin = { 0, 0 };

    int rotation = 0;
	*/

	// Main game loop
    SetTargetFPS(60);
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		float dt = GetFrameTime(); // Time since last frame

		update(registry, dt);

		float dt = GetFrameTime(); // Time since last frame

		boxVol.y += gravity * dt; // Update volocity based on gravity

		// Move box based on key input
		if (IsKeyPressed(KEY_SPACE)) // if player hits space jump 
		{
   			boxVol.y = jumpStrength; // player jumps using jump strength
		}

		if (IsKeyDown(KEY_D)) boxPosition.x += speed * dt; // move left
		if (IsKeyDown(KEY_A)) boxPosition.x -= speed * dt; // move right

		boxPosition.y += boxVol.y * dt; // update player position based on volocity

		// Constrain box to stay within screen bounds
		if (boxPosition.x < 0) boxPosition.x = 0;
		if (boxPosition.y < 0) boxPosition.y = 0;
		if (boxPosition.x > screenWidth - boxSize.x) boxPosition.x = screenWidth - boxSize.x;
		if (boxPosition.y > screenHeight - boxSize.y) boxPosition.y = screenHeight - boxSize.y;

		// Update cow texture position to follow the box
		destRec.x = boxPosition.x;
		destRec.y = boxPosition.y;

		BeginDrawing();
		ClearBackground(RAYWHITE);

		// Draw background texture scaled to screen size
		
		/*DrawTexturePro(background, 
			{0, 0, (float)background.width, (float)background.height}, 
			{0, 0, (float)screenWidth, (float)screenHeight}, 
			{0, 0}, 0, WHITE);*/

		// Draw the map
        DrawTMX(stage1, NULL, 0, 0, WHITE);

		//DrawRectangleV(boxPosition, boxSize, BLUE); // Draw the blue box

		 DrawTexturePro(cow, sourceRec, destRec, origin, (float)rotation, WHITE); // Draws cow

        // Draw text
         const char* instructionText = "Move with W A S D. Jump with SPACE";
         DrawRectangle(8, 8, MeasureText(instructionText, 20) + 4, 24, Fade(BLACK, 0.5f));
         DrawText(instructionText, 10, 10, 20, WHITE);

		EndDrawing();
	}

	// Cleanup
	UnloadTexture(cow);
	//UnloadTexture(background);
	UnloadTMX(stage1);
	CloseWindow();

	return 0;
}
