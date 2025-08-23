#include <stdexcept>
#include <iostream>

#include "Block.h"
#include "config.h"


constexpr char* WORLD_TILESET = R"(C:\Users\willi\source\repos\Raylib_2D_Game\Game\resources\assets\sprites\world_tileset.png)";


Block::Block(BlockType type, Vector2 pos) : position(pos)
{
	texture = LoadTexture(WORLD_TILESET);

	switch (type) 
	{
		case BlockType::DIRT: 
		{
			m_currentFrame = 16;
			break;
		}
		case BlockType::GRASS: 
		{
			m_currentFrame = 0;
			break;
		}
		default: 
		{
			throw std::invalid_argument("Invalid BlockType");
		}
	}

	m_frameWidth = texture.width / 16;
	m_frameHeight = texture.height / 16;

	int row = m_currentFrame / 16; 

	float x = (float)(m_currentFrame * m_frameWidth);
	float y = (float)(row * m_frameHeight);

	frameRec = { x, y, (float)m_frameWidth, (float)m_frameHeight };
}


Block::~Block() 
{
	UnloadTexture(texture);
}


void Block::draw() 
{
	DrawTextureRec(texture, frameRec, position, WHITE);
}
