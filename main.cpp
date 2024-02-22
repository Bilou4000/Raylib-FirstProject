#include "raylib.h"
#include <iostream>

using namespace std;

int screenWidth = 1600;
int screenHeight = 900;

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
    //
}


void Draw() 
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    EndDrawing();
}

void Unload() 
{
    CloseWindow();
}


