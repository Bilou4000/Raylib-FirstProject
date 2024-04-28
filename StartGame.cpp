#include "StartGame.h"

void StartGame::Init()
{
    mNameAnswerBox = { GetScreenWidth() / 2.0f - 262.5f, 250, 525, 100 };
	mInput = 0;
	mNameLetterCount = 0;

    mAnswerPk = NULL;
    mBoxInput = NULL;

    mStarterPokemons = { AllPokemons::Cleffa, AllPokemons::Vanillite, AllPokemons::Magikarp };
}

bool StartGame::Update()
{
    if (mInput < 3)
    {
        ChooseName();
    }
    else
    {
        ChoosePokemon();
        if (ChoosePokemon())
        {
            return true;
        }
    }

    return false;
}

void StartGame::Draw()
{
    if (mInput < 3)
    {
        DrawName();
    }
    else
    {
        DrawPokemon();
    }

}

void StartGame::ChooseName()
{
    if (mInput == 1)
    {
        mFirstName = mName;
        mNameLetterCount = 0;
        mName[mNameLetterCount] = '\0';
        mInput = 2;
    }
    if (mInput == 3)
    {
        mLastName = mName;
        mNameLetterCount = 0;
        mName[mNameLetterCount] = '\0';
        mInput = 4;
    }

    int key = GetCharPressed();

    while (key > 0)
    {
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (mNameLetterCount < MAX_INPUT_CHARS))
        {
            mName[mNameLetterCount] = (char) key;
            mName[mNameLetterCount + 1] = '\0';
            mNameLetterCount++;
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        mNameLetterCount--;
        if (mNameLetterCount < 0)
        {
            mNameLetterCount = 0;
        }
        mName[mNameLetterCount] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER) && mNameLetterCount > 0)
    {
        mInput++;
    }
}

bool StartGame::ChoosePokemon()
{
    if (GetKeyPressed())
    {
        mBoxInput = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER) && mAnswerPk > 0 && mAnswerPk <= 3)
    {
        if (mAnswerPk == 1)
        {
            mPlayerPokemon = mStarterPokemons[0];
            return true;
        }
        else if (mAnswerPk == 2)
        {
            mPlayerPokemon = mStarterPokemons[1];
            return true;
        }
        else if (mAnswerPk == 3)
        {
            mPlayerPokemon = mStarterPokemons[2];
            return true;
        }
    }

    return false;
}

void StartGame::DrawName()
{
    if (mInput <= 1)
    {
        DrawText("Welcome to this wonderful adventure !! ", 70, 775, 70, BLACK);
        DrawText("Please choose your FIRST name. ", 70, 875, 70, BLACK);
        DrawText("Put 9 characters maximum.", 70, 970, 40, RED);


        DrawText("FIRST NAME", GetScreenWidth() / 2.0f - MeasureText("FIRST NAME", 60) / 2.0f, 150, 60, BLACK);
    }
    else if (mInput == 2)
    {
        DrawText(TextFormat("Welcome %s !!!", mFirstName.c_str()), 70, 775, 70, BLACK);
        DrawText("What about your LAST name ? ", 70, 875, 70, BLACK);
        DrawText("Put 9 characters maximum.", 70, 970, 40, RED);

        DrawText("LAST NAME", GetScreenWidth() / 2.0f - MeasureText("LAST NAME", 60) / 2.0f, 150, 60, BLACK);
    }


    DrawRectangleRec(mNameAnswerBox, WHITE);
    DrawText(mName, (int) mNameAnswerBox.x + 15, (int) mNameAnswerBox.y + 8, 80, RED);
    DrawText(TextFormat("Max input : %i/%i", mNameLetterCount, MAX_INPUT_CHARS), GetScreenWidth() / 2.0f - 170, 370, 40, DARKGRAY);


    if (mNameLetterCount < MAX_INPUT_CHARS)
    {
        DrawText("_", (int) mNameAnswerBox.x + 15 + MeasureText(mName, 80), (int) mNameAnswerBox.y + 20, 80, RED);
    }
}

void StartGame::DrawPokemon()
{
    DrawText(TextFormat("Hello to you, %s %s !!!", mFirstName.c_str(), mLastName.c_str()), 70, 775, 70, BLACK);
    DrawText("Choose your starter Pokemon now. ", 70, 875, 70, BLACK);
    DrawText("Write the corresponding number :", 70, 970, 40, RED);

    DrawRectangleRec(mPkAnswerBox, LIGHTGRAY);

    if (isdigit(mBoxInput))
    {
        string printAnswer { (char) mBoxInput };
        DrawText(TextFormat("%s", printAnswer.c_str()), 800, 955, 70, BLACK);

        mAnswerPk = stoi(printAnswer);
    }
    else
    {
        DrawText("_", 800, 955, 70, BLACK);
    }


    float pokemonPosition = 50;
    float pokemonNamePosition = 70;

    for (int i = 0; i < mStarterPokemons.size(); i++)
    {
        DrawTextureEx(*mStarterPokemons[i].GetPokemonTexture(), { pokemonPosition, 250 }, 0, 0.6f, WHITE);
        DrawText(TextFormat("%i. %s ", i + 1, mStarterPokemons[i].GetPokemonName().c_str()), pokemonPosition, 550, 35, BLACK);
        pokemonPosition += GetScreenWidth() / mStarterPokemons.size();
    }
}
