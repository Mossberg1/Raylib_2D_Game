#pragma once

#include "raylib.h"

enum BlockType 
{
	DIRT,
	GRASS
};


class Block
{
public:
	Vector2 position;
	Texture2D texture;
	Rectangle frameRec;

	Block(BlockType type, Vector2 pos);

	~Block();

	void draw();
	int getFrameHeight() const { return m_frameHeight; }
	int getFrameWidth() const { return m_frameWidth; }

private:
	int m_frameWidth;
	int m_frameHeight;
	int m_currentFrame;
};