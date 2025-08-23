#pragma once

#include "raylib.h"


enum AnimationState
{
	IDLE,
	RUNNING,
	ROLLING,
	DEATH
};


class Player 
{
public:
    Vector2 position;
    Texture2D texture;
    float speed;
    Vector2 velocity;
    Rectangle frameRec;
    bool onGround = true;

    Player(Vector2 startPos);
    ~Player();

    void despawn();
    void draw();
    void jump();
    void moveRight(float deltaTime);
    void moveLeft(float deltaTime);
    void setState(AnimationState newState);
    void spawn();

private:
    int m_framesPerCol = 8;
    int m_framesPerRow = 8;
    int m_frameWidth;
    int m_frameHeight;
    int m_numIdleFrames = 4;
	int m_numRunningFrames = 16;
    int m_currentFrame = 0;
    int m_animationSpeed = 8;
    AnimationState m_currentState;
    bool m_movingRight = true;
    bool m_isSpawned = false;

    void addGravity();
    void animate();
};