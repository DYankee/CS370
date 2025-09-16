// CS370.cpp : Defines the entry point for the application.
//

#include "CS370.h"
#include "raylib.h"

using namespace std;

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;
	// Create the main window
	
	InitWindow(screenWidth, screenHeight, "CS370");

	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
	}
	

	cout << "Hello CMake." << endl;
	return 0;
}
