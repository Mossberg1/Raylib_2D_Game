#include <iostream>
#include <string>

#include "Player.h"
#include "config.h"


constexpr char* KNIGHT_ASSET = R"(C:\Users\willi\source\repos\Raylib_2D_Game\Game\resources\assets\sprites\knight.png)";
constexpr int DEFAULT_MOVEMENT_SPEED = 200;


Player::Player(Vector2 startPos) : position(startPos)
{
	texture = LoadTexture(KNIGHT_ASSET);

	speed = DEFAULT_MOVEMENT_SPEED;
	velocity = { speed, 0.0f };

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
	addGravity();
	animate();
}


void Player::jump() 
{
	if (onGround) 
	{
		velocity.y = JUMP_FORCE;
		onGround = false;
	}
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


void Player::addGravity() 
{
	float deltaTime = GetFrameTime();

	if (!onGround || velocity.y < 0) 
	{
		velocity.y += GRAVITY * deltaTime;
	}

	position.y += velocity.y * deltaTime;

	if (position.y >= GROUND_Y) 
	{
		position.y = GROUND_Y;
		velocity.y = 0;
		onGround = true;
	}
	else
	{
		onGround = false;
	}
}


void Player::animate() 
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
	}

	DrawTextureRec(texture, drawRect, position, WHITE);
}
