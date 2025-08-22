#include <iostream>
#include <string>

#include "raylib.h"
#include "Player.h"

constexpr char* GAME_NAME = "MyGame";
constexpr float GAME_MASTER_VOLUME = 0.3f;
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr bool SHOW_FPS = false;
constexpr bool USE_TARGET_FPS = false;
constexpr int TARGET_FPS = 60;
constexpr char* SOUNDTRACK = R"(C:\Users\willi\source\repos\Raylib_2D_Game\Game\resources\assets\music\time_for_adventure.mp3)";


int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);

	InitAudioDevice();
	SetMasterVolume(GAME_MASTER_VOLUME);

	Music soundtrack = LoadMusicStream(SOUNDTRACK);
	PlayMusicStream(soundtrack);


	if (USE_TARGET_FPS)
	{
		SetTargetFPS(TARGET_FPS);
	}

	Player* player = new Player({400, 400});

	// Game loop
	while (!WindowShouldClose()) 
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		UpdateMusicStream(soundtrack);

		player->draw();
		
		if (SHOW_FPS)
		{
			int currentFps = GetFPS();
			DrawText(TextFormat("FPS: %d", currentFps), 10, 10, 20, WHITE);
		}

		float deltaTime = GetFrameTime();
		bool hasMoved = false;

		if (IsKeyDown(KEY_RIGHT)) 
		{
			player->moveRight(deltaTime);
			hasMoved = true;
		}
		if (IsKeyDown(KEY_LEFT)) 
		{
			player->moveLeft(deltaTime);
			hasMoved = true;
		}

		if (!hasMoved) 
		{
			player->setState(AnimationState::IDLE);
		}

		EndDrawing();
	}

	delete player;
	UnloadMusicStream(soundtrack);
	CloseAudioDevice();
	CloseWindow();

	return 0;
}