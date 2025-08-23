#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "raylib.h"
#include "Player.h"
#include "Block.h"

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

	Block* block = new Block(BlockType::DIRT, { 0, GROUND_Y + 50 });
	int blockWidth = block->getFrameWidth();
	int blockHeight = block->getFrameHeight();
	delete block;

	Player* player = new Player({ 400, GROUND_Y });
	player->spawn();

	std::vector<Block*> grassBlocks = {};
	for (size_t i = 0; i < 50; i++)
	{
		int xPos = i * blockWidth;
		int yPos = (GROUND_Y + player->getFrameHeight()) - 5;
		Vector2 position = { xPos, yPos };
		Block* gb = new Block(BlockType::GRASS, position);
		grassBlocks.push_back(gb);
	}

	std::vector<Block*> dirtBlocks = {};
	for (size_t i = 0; i < 200; i++)
	{
		int xPos = i * blockWidth;
		int yPos = GROUND_Y + (blockHeight * 3) - 5;

		if (i >= 50 && i < 100) 
		{
			xPos = (i - 50) * blockWidth;
			yPos += blockHeight;
		}
		else if (i >= 100 && i < 150) 
		{
			xPos = (i - 100) * blockWidth;
			yPos += blockHeight * 2;
		}
		else if (i >= 150) 
		{
			xPos = (i - 150) * blockWidth;
			yPos += blockHeight * 3;
		}

		Vector2 position = { xPos, yPos };
		Block* db = new Block(BlockType::DIRT, position);
		dirtBlocks.push_back(db);
	}

	// Game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKBLUE);
		UpdateMusicStream(soundtrack);

		for (Block* grassBlock : grassBlocks)
		{
			grassBlock->draw();
		}

		for (Block* dirtBlock : dirtBlocks) 
		{
			dirtBlock->draw();
		}

		player->draw();

		if (SHOW_FPS)
		{
			int currentFps = GetFPS();
			DrawText(TextFormat("FPS: %d", currentFps), 10, 10, 20, WHITE);
		}

		float deltaTime = GetFrameTime();
		bool hasMoved = false;

		if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
		{
			player->moveRight(deltaTime);
			hasMoved = true;
		}
		if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
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

	for (Block* block : grassBlocks)
	{
		delete block;
	}

	for (Block* block : dirtBlocks) 
	{
		delete block;
	}

	delete player;
	UnloadMusicStream(soundtrack);
	UnloadSound(jumpSound);
	CloseAudioDevice();
	CloseWindow();

	return 0;
}