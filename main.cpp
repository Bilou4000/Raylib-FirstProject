#include "raylib.h"
#include <iostream>

using namespace std;

//Screen
int screenWidth = 1600;
int screenHeight = 900;

//Ball
int xBall = 100;
int yBall = 150;
int ballSize = 64;

int speedXBall = 5;
int speedYBall = -5;

//Paddle
Rectangle leftPaddle { 0, 150, 55, 256 };
int speedLeftPaddle = 8;

void Load();
void Update();
void Draw();
void Unload();


int main()
{
    Load();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    Unload();
    return 0;
}


void Load() 
{
    InitWindow(screenWidth, screenHeight, "RAYLIB PROJECT");
    SetTargetFPS(60);
}

void Update() 
{
    //BALL
    xBall += speedXBall;
    yBall += speedYBall;

    if (yBall < 0) 
    {
        speedYBall = -speedYBall;
        yBall = 0;
    }
    if (yBall + ballSize > screenHeight) 
    {
        speedYBall = -speedYBall;
        yBall = screenHeight - ballSize;
    }

    if (xBall < 0)
    {
        speedXBall = -speedXBall;
        xBall = 0;
    }
    if (xBall + ballSize > screenWidth)
    {
        speedXBall = -speedXBall;
        xBall = screenWidth - ballSize;
    }

    //LEFT PADDLE
    if (IsKeyDown(KEY_S))
    {
        leftPaddle.y += speedLeftPaddle;
    }
    else if(IsKeyDown(KEY_W))
    {
        leftPaddle.y -= speedLeftPaddle;
    }

    if (leftPaddle.y < 0)
    {
        leftPaddle.y = 0;
    }
    if (leftPaddle.y + leftPaddle.height > screenHeight)
    {
        leftPaddle.y = screenHeight - leftPaddle.height;
    }
}

void Draw() 
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawRectangle(xBall, yBall, ballSize, ballSize, WHITE);
    DrawRectangleRec(leftPaddle, WHITE);

    EndDrawing();
}

void Unload() 
{
    CloseWindow();
}


