#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

typedef enum GameScreen { MENU, START, STROLL, ATTACKPOKEMON, ATTACKTRAINER, ENDING } GameScreen;
GameScreen currentScreen;

//Screen
int screenWidth = 1600;
int screenHeight = 900;

//Function
void Load();
void Update();
void Draw();
void Unload();

void StrollingAround();

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
                //currentScreen = START;
                currentScreen = STROLL;
            }
        }
        break;
        case START:
        {
            //start of the game
        }
        case STROLL:
        {
            //ask if wants to discover pokemon or attack trainer
            StrollingAround();
        }
        break;
        case ATTACKPOKEMON:
        {
            //
        }
        break;
        case ATTACKTRAINER:
        {
            //
        }
        break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_R))
            {
                // restart
                currentScreen = START;
            }

            if (IsKeyPressed(KEY_SEMICOLON))
            {
                // go to menu
                currentScreen = MENU;
            }
        }
        break;
        default: break;
    }
}

void StrollingAround()
{
    //
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
        case START:
        {
            //choose pokemon
        }
        break;
        case STROLL:
        {
            //
        }
        break;
        case ATTACKPOKEMON:
        {
            //
        }
        break;
        case ATTACKTRAINER:
        {
            //
        }
        break;
        case ENDING:
        {
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


