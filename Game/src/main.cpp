#include <iostream>
#include <string>

#include "config.h"
#include "raylib.h"
#include "Player.h"

constexpr char* GAME_NAME = "MyGame";
constexpr float MASTER_VOLUME = 0.3f;

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr bool SHOW_FPS = true;
constexpr bool USE_TARGET_FPS = false;
constexpr int TARGET_FPS = 60;

constexpr char* SOUNDTRACK = R"(C:\Users\willi\source\repos\Raylib_2D_Game\Game\resources\assets\music\time_for_adventure.mp3)";
constexpr char* JUMP_SOUND = R"(C:\Users\willi\source\repos\Raylib_2D_Game\Game\resources\assets\sounds\jump.wav)";


int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);

	InitAudioDevice();
	SetMasterVolume(MASTER_VOLUME);

	Music soundtrack = LoadMusicStream(SOUNDTRACK);
	Sound jumpSound = LoadSound(JUMP_SOUND);

	PlayMusicStream(soundtrack);


	if (USE_TARGET_FPS)
	{
		SetTargetFPS(TARGET_FPS);
	}

	Player* player = new Player({400, GROUND_Y});
	player->spawn();

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
		if (IsKeyPressed(KEY_SPACE)) 
		{
			player->jump();
			PlaySound(jumpSound);
		}

		if (!hasMoved) 
		{
			player->setState(AnimationState::IDLE);
		}

		EndDrawing();
	}

	delete player;
	UnloadMusicStream(soundtrack);
	UnloadSound(jumpSound);
	CloseAudioDevice();
	CloseWindow();

	return 0;
}