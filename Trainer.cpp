#pragma once
#include <iostream>
#include <string>

#include "raylib.h"
#include "Trainer.h"
#include "allPokemons.h"
#include "Battle.h"

bool isInSendPokemon = false;
bool pokemonImageIsLoad = false;
bool mouseOnText = false;
bool isPokemonDead = false;

int key = NULL;
int answer = NULL;

Rectangle changePokemonBox { 0 , 55, 1600, 1200 / 2 };
Rectangle answerBox { 1300, 860, 80, 70 };

Trainer::Trainer()
{
	mFirstName = "Arthur";
	mLastName = "Cathelain";
	mCatchPhrase = "Nothing in life is equivalent to the beauty of splines";
	mPokemonTeam = { AllPokemons::Diglett };
	mPokemonTeam.reserve( 6 );
}

Trainer::Trainer(string firstName, string lastName, string CatchPhrase, vector<Pokemon> PokemonTeam)
{
	mFirstName = firstName;
	mLastName = lastName;
	mCatchPhrase = CatchPhrase;
	mPokemonTeam = PokemonTeam;
	mPokemonTeam.reserve( 6 );
}

void Trainer::UpdateTrainer()
{
	if (isInSendPokemon)
	{
		mouseOnText = true;

		if (mouseOnText && GetKeyPressed())
		{
			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_ENTER) && answer > 0 && answer <= mPokemonTeam.size())
		{
			if (mPokemonTeam[answer - 1].GetPokemonLife() <= 0)
			{
				answer = NULL;
				mAnswerTrainer = NULL;
				isPokemonDead = true;
			}
			else
			{
				mAnswerTrainer = answer;
			}
		}

		if (IsKeyPressed(KEY_SPACE) && isPokemonDead)
		{
			isPokemonDead = false;
		}
	}
}

void Trainer::DrawTrainer()
{
	if (isInSendPokemon) 
	{
		DrawRectangleRec(changePokemonBox, WHITE);

		if (isPokemonDead)
		{
			DrawText("This pokemon is already dead, ", 70, 775, 70, BLACK);
			DrawText("Please choose an other pokemon.", 70, 875, 70, BLACK);
		}
		else
		{
			DrawText("You have this pokemon team :", 70, 125, 70, BLACK);
			DrawText("Which Pokemon do you want to use ? ", 70, 775, 70, BLACK);
			DrawText("Write the corresponding number :", 70, 870, 70, RED);
			DrawRectangleRec(answerBox, LIGHTGRAY);

			if (mouseOnText)
			{
				if (isdigit(key))
				{
					string printAnswer { (char) key };
					DrawText(TextFormat("%s", printAnswer.c_str()), 1320, 870, 70, BLACK);

					answer = stoi(printAnswer);
				}
				else
				{
					DrawText("_", 1320, 870, 70, BLACK);
				}
			}
		}

		float pokemonPosition = 50;
		float pokemonNamePosition = 70;

		for (int i = 0; i < mPokemonTeam.size(); i++)
		{
			DrawTextureEx(*mPokemonTeam[i].GetPokemonTexture(), {pokemonPosition, 250}, 0, 0.6f, WHITE);
			DrawText(TextFormat("%i. %s ", i + 1, mPokemonTeam[i].GetPokemonName().c_str()), pokemonPosition, 550, 35, BLACK);
			DrawText(TextFormat("(%s)", mPokemonTeam[i].GetPokemonTypeName().c_str()), pokemonPosition, 600, 30, DARKGRAY);
			pokemonPosition += GetScreenWidth() / mPokemonTeam.size();
		}
	}
}

const char* Trainer::Introduction()
{
	return (char*) TextFormat("%s %s said : %s", mFirstName.c_str(), mLastName.c_str(), mCatchPhrase.c_str());
}

const char* Trainer::ChallengeTrainer()
{
	return (char*) TextFormat("You are challenging %s %s !!!", mFirstName.c_str(), mLastName.c_str());
}


bool Trainer::IsPokemonCaptured(Pokemon& pokemon)
{
	float captureRate = (((1.0f + (((pokemon.GetPokemonMaxLife() * 3.0f) - (pokemon.GetPokemonLife() * 2.0f)) * 256.0f))
		/ (pokemon.GetPokemonMaxLife() * 3.0f)) / 334.0f) * 100.0f;

	if (captureRate <= 50)
	{
		return false;
	}

	mPokemonTeam.push_back(pokemon);
	mPokeballs -= 1;
	return true;
}

bool Trainer::CheckIfTeamDead()
{
	for (int i = 0; i < mPokemonTeam.size(); i++)
	{
		if (mPokemonTeam[i].GetPokemonLife() > 0)
		{
			return false;
		}
	}

	mMoney -= 70;

	return true;
}

Pokemon& Trainer::SendOrChangePokemon()
{
	Pokemon& pokemonWantingToBeUse = mPokemonTeam[mAnswerTrainer - 1];
	mCurrentPokemonIndex = mAnswerTrainer - 1;

	isInSendPokemon = false;
	mAnswerTrainer = NULL;
	answer = NULL;
	return pokemonWantingToBeUse;
}

void Trainer::ChoosePokemonToUse()
{
	isInSendPokemon = true;
}

bool Trainer::WinFight()
{
	srand(time(NULL));
	int random = rand() % 101;

	if (random <= 50)
	{
		mMoney += 100;
		return true;
	}
	else if (random > 50)
	{
		mPokeballs += 2;
		return false;
	}
}

vector<Pokemon>& Trainer::GetPokemonTeam()
{
	return mPokemonTeam;
}

int Trainer::GetAnswerTrainer() const
{
	return mAnswerTrainer;
}

int Trainer::GetMoney() const
{
	return mMoney;
}

int Trainer::GetPokeballs() const
{
	return mPokeballs;
}
