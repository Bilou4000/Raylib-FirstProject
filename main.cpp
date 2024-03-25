#include <iostream>
#include <string>

#include "raylib.h"
#include "allPokemons.h"
#include "Trainer.h"
#include "Battle.h"

using namespace std;

typedef enum GameScreen { MENU, START, STROLL, ATTACKPOKEMON, ATTACKTRAINER, ENDING } GameScreen;
GameScreen currentScreen;

//Screen
int screenWidth = 1600; //1600
int screenHeight = 1200; //1200

//text Box
Rectangle TextBox { screenWidth - 1550, screenHeight - 425 - 20, 1500, 400 };

//--------------------------------------TO CHANGE -------------------------------------------------------------------
vector<Pokemon> firstTeam = { Pansage, Minun, Vanillite, Snorlax, Magikarp, Pancham };
vector<Pokemon> secondTeam = { Snorlax };

Trainer firstTrainer = Trainer("Claire", "Benes", "As the wind continues to blow, so too shall I continue to fight !", firstTeam);
Trainer secondTrainer = Trainer("Jean", "Louis", "OHOHOHOHOHOH !!!", secondTeam);
//--------------------------------------TO CHANGE -------------------------------------------------------------------

Battle theBattle = Battle(firstTrainer, secondTrainer);
Pokemon opponentPokemon = Pokemon();
bool isInCombat = false;

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
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
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
                currentScreen = ATTACKTRAINER;
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
            if (!isInCombat)
            {
                opponentPokemon = theBattle.ChooseOpponentPokemon();
                isInCombat = true;
            }

            theBattle.BattleAgainstTrainer(opponentPokemon);
            theBattle.BattleUpdate();
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
    ClearBackground(LIGHTGRAY);

    switch (currentScreen)
    {
        case MENU:
        {
            DrawText("POKEMON", 450, 150, 150, RED);
            DrawText("Press ENTER to PLAY", 350, 400, 80, BLACK);
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
            DrawRectangleRec(TextBox, WHITE);
        }
        break;
        case ATTACKTRAINER:
        {
            DrawRectangleRec(TextBox, WHITE);
            theBattle.BattleDraw();
            //firstTrainer.DrawTrainer();
        }
        break;
        case ENDING:
        {
            DrawText("Press R to PLAY AGAIN", 350, 400, 80, BLACK);
            DrawText("Or Press M to go back to MENU", 150, 500, 80, BLACK);
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


