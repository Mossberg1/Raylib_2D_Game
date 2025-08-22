#include <iostream>
#include <string>

#include "Player.h"


constexpr char* KNIGHT_ASSET = R"(C:\Users\willi\source\repos\RaylibEngine\raylibCmakeSetup\resources\assets\sprites\knight.png)";
constexpr int DEFAULT_MOVEMENT_SPEED = 200;


Player::Player(Vector2 startPos) : position(startPos)
{
	texture = LoadTexture(KNIGHT_ASSET);

	speed = DEFAULT_MOVEMENT_SPEED;
	velocity = { speed, speed };

	m_frameWidth = texture.width / m_framesPerCol;
	m_frameHeight = texture.height / m_framesPerRow;
	frameRec = { 0.0f, 0.0f, (float)m_frameWidth, (float)m_frameHeight };

	m_currentState = AnimationState::IDLE;
}


Player::~Player() 
{
	UnloadTexture(texture);
}


void Player::draw()
{
	int numberOfFrames = 0;
	int row = 0;

	switch (m_currentState) 
	{
		case AnimationState::IDLE: 
		{
			numberOfFrames = m_numIdleFrames;
			row = 0;
			break;
		}
		case AnimationState::RUNNING:
		{
			numberOfFrames = m_numRunningFrames;
			row = 2;
			break;
		}
		default: // Använd Idle animation som default.
		{
			numberOfFrames = m_numIdleFrames;
			row = 0; 
		}
	}

	m_currentFrame = (int)(GetTime() * m_animationSpeed) % numberOfFrames; // Animerar i samma animations hastighet oberoende av FPS.

	frameRec.x = (float)(m_currentFrame * m_frameWidth);
	frameRec.y = (float)(row * m_frameHeight);

	Rectangle drawRect = frameRec;

	if (!m_movingRight) 
	{
		drawRect.width = -m_frameWidth;
		//drawRect.x += m_frameWidth;
	}

	DrawTextureRec(texture, drawRect, position, WHITE);
}


void Player::moveRight(float deltaTime) 
{
	m_currentState = AnimationState::RUNNING;
	m_movingRight = true;
	position.x += velocity.x * deltaTime;
}


void Player::moveLeft(float deltaTime) 
{
	m_currentState = AnimationState::RUNNING;
	m_movingRight = false;
	position.x -= velocity.x * deltaTime;
}


void Player::setState(AnimationState newState)
{
	if (m_currentState != newState) 
	{
		m_currentState = newState;
		m_currentFrame = 0;
	}
}
