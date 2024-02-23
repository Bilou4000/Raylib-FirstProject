#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

typedef enum GameScreen { MENU, GAMEPLAY, ENDING } GameScreen;
GameScreen currentScreen;

//Screen
int screenWidth = 1600;
int screenHeight = 900;

//Ball
Rectangle ball { 100, 150, 64, 64 };

int speedXBall = 6;
int speedYBall = -6;


//Paddle
Rectangle leftPaddle { 0, 150, 55, 256 };
int speedLeftPaddle = 8;

Rectangle rightPaddle { screenWidth - 55, 150, 55, 256 };
int speedRightPaddle = 5;


//Score
int leftScore = 0;
int rightScore = 0;
//EndOfGame
string textResult;
bool resultVisible = false;

//Function
void Load();
void Update();
void Draw();
void Unload();

void Gameplay();
bool Collision(Rectangle a, Rectangle b);
void BounceOnPaddle(bool playerSide);
void PlaceBall(bool playerSide);


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
    currentScreen = MENU;
    SetTargetFPS(60);
}

void Update() 
{
    switch (currentScreen)
    {
        case MENU:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            Gameplay();
        }
        break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_R))
            {
                textResult = "";
                leftScore = 0;
                rightScore = 0;

                currentScreen = GAMEPLAY;
            }

            if (IsKeyPressed(KEY_SEMICOLON))
            {
                textResult = "";
                leftScore = 0;
                rightScore = 0;

                currentScreen = MENU;
            }
        }
        break;
        default: break;
    }
}

void Gameplay()
{
    //BALL
    ball.x += speedXBall;
    ball.y += speedYBall;

    if (ball.y < 0)
    {
        speedYBall = -speedYBall;
        ball.y = 0;
    }
    if (ball.y + ball.height > screenHeight)
    {
        speedYBall = -speedYBall;
        ball.y = screenHeight - ball.height;
    }

    if (ball.x < 0)
    {
        ++rightScore;
        PlaceBall(true);

        if (rightScore >= 3)
        {
            textResult = "Defeat";
            currentScreen = ENDING;
        }
    }
    if (ball.x + ball.width > screenWidth)
    {
        ++leftScore;
        PlaceBall(false);

        if (leftScore >= 3)
        {
            textResult = "Victory";
            currentScreen = ENDING;
        }
    }

    //LEFT PADDLE
    if (IsKeyDown(KEY_S))
    {
        leftPaddle.y += speedLeftPaddle;
    }
    else if (IsKeyDown(KEY_W))
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

    if (rightPaddle.y < 0)
    {
        rightPaddle.y = 0;
    }
    if (rightPaddle.y + rightPaddle.height > screenHeight)
    {
        rightPaddle.y = screenHeight - rightPaddle.height;
    }

    //COLLISION
    if (Collision(leftPaddle, ball))
    {
        BounceOnPaddle(true);
    }
    else if (Collision(rightPaddle, ball))
    {
        BounceOnPaddle(false);
    }

    //IA Right Paddle
    if (ball.y < rightPaddle.y + rightPaddle.height / 4)
    {
        rightPaddle.y -= speedRightPaddle;
    }
    else if (ball.y > rightPaddle.y + rightPaddle.height * 3 / 4)
    {
        rightPaddle.y += speedRightPaddle;
    }
}

bool Collision(Rectangle a, Rectangle b)
{
    int xMinA = a.x;
    int yMinA = a.y;
    int xMaxA = a.x + a.width;
    int yMaxA = a.y + a.height;

    int xMinB = b.x;
    int yMinB = b.y;
    int xMaxB = b.x + b.width;
    int yMaxB = b.y + b.height;

    return ( !(xMinB > xMaxA || yMinB > yMaxA
        || xMaxB < xMinA || yMaxB < yMinA) );
}

void BounceOnPaddle(bool playerSide)
{
    speedXBall = -speedXBall;
    if (playerSide)
    {
        ball.x = leftPaddle.x + 64;
    }
    else
    {
        ball.x = rightPaddle.x - 64;
    }
}

void PlaceBall(bool playerSide)
{
    if (playerSide)
    {
        ball.x = ball.width * 4;
    }
    else
    {
        ball.x = screenWidth - ball.width * 4;
    }

    ball.y = 150;
    speedXBall = -speedXBall;
}

void Draw() 
{
    BeginDrawing();
    ClearBackground(BLACK);

    switch (currentScreen)
    {
        case MENU:
        {
            DrawText("PONG", 580, 150, 150, RED);
            DrawText("Press ENTER to PLAY", 350, 400, 80, LIGHTGRAY);
        }
        break;
        case GAMEPLAY:
        {
            int rectY = -5;
            for (int i = 0; i < 12; i++)
            {
                DrawRectangle(810, rectY, 20, 35, WHITE);
                rectY += 80;
            }


            DrawRectangleRec(ball, WHITE);
            DrawRectangleRec(leftPaddle, BLUE);
            DrawRectangleRec(rightPaddle, RED);

            DrawText(to_string(leftScore).c_str(), 600, 50, 60, BLUE);
            DrawText(to_string(rightScore).c_str(), 1000, 50, 60, RED);
        }
        break;
        case ENDING:
        {
            DrawText(textResult.c_str(), 680, 200, 80, LIGHTGRAY);
            DrawText("Press R to PLAY AGAIN", 350, 400, 80, LIGHTGRAY);
            DrawText("Or Press M to go back to MENU", 150, 500, 80, LIGHTGRAY);
        }
        break;
        default: break;
    }

    EndDrawing();
}

void Unload() 
{
    CloseWindow();
}


