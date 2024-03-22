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

vector<Texture2D> allPokemonsTexture;

Trainer::Trainer()
{
	mFirstName = "Arthur";
	mLastName = "Cathelain";
	mCatchPhrase = "Nothing in life is equivalent to the beauty of splines";
	mPokemonTeam = { Diglett };
}

Trainer::Trainer(string firstName, string lastName, string CatchPhrase, vector<Pokemon> PokemonTeam)
{
	mFirstName = firstName;
	mLastName = lastName;
	mCatchPhrase = CatchPhrase;
	mPokemonTeam = PokemonTeam;
}

void Trainer::UpdateTrainer()
{
	if (isInSendPokemon)
	{
		if (CheckCollisionPointRec(GetMousePosition(), answerBox))
		{
			if (IsMouseButtonPressed(0))
			{
				mouseOnText = true;
			}
		}

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

		if (!pokemonImageIsLoad) 
		{
			int spacing = 0;
			for (int i = 0; i < mPokemonTeam.size(); i++)
			{
				ImageFormat(mPokemonTeam[i].GetPokemonImage(), PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
				Texture2D onePokemonTexture = LoadTextureFromImage(*(mPokemonTeam[i].GetPokemonImage()));
				
				allPokemonsTexture.push_back(onePokemonTexture);
			}
			pokemonImageIsLoad = true;
		}

		for (int i = 0; i < mPokemonTeam.size(); i++)
		{
			DrawTextureEx(allPokemonsTexture[i], {pokemonPosition, 250}, 0, 0.6f, WHITE);
			DrawText(TextFormat("%i. %s ", i + 1, mPokemonTeam[i].GetPokemonName().c_str()), pokemonPosition, 550, 35, BLACK);
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

//*************** TO REFACTOR ***************************************
// 
// JUST PRINT the wild pokemon found in the main
// 
//const char* Trainer::ChallengePokemon()
//{
//	//*************** TO REFACTOR ***************************************
//	cout << "\nYou just found a wild pokemon !!" << endl;
//
//	//Battle theBattle = Battle(thePlayer);
//	//theBattle.BattleAgainstPokemon(true);
//}

bool Trainer::IsPokemonCaptured(Pokemon& pokemon)
{
	if (mPokemonTeam.size() < 6 && mPokeballs > 0)
	{
		//*************** TO REFACTOR ***************************************
		//cout << "\nYou are trying to capture " << pokemon.GetPokemonName() << endl;

		float captureRate = (((1.0f + (((pokemon.GetPokemonMaxLife() * 3.0f) - (pokemon.GetPokemonLife() * 2.0f)) * 256.0f)) 
			/ (pokemon.GetPokemonMaxLife() * 3.0f)) / 334.0f) * 100.0f;

		if (captureRate <= 50)
		{
			//*************** TO REFACTOR ***************************************
			cout << "You have failed to capture the pokemon" << endl;
			return false;
		}

		//*************** TO REFACTOR ***************************************
		//cout << "You have managed to capture " << pokemon.GetPokemonName() << " !!!!" << endl;

		mPokemonTeam.push_back(pokemon);
		mPokeballs -= 1;
		return true;
	}
	else if (mPokeballs <= 0)
	{
		//*************** TO REFACTOR ***************************************
		cout << "\nYou don't have enough Pokeballs, try an other time." << endl;

		return false;
	}
	//*************** TO REFACTOR ***************************************
	cout << "\nYou already have 6 pokemon and can't capture one anymore" << endl;

	return false;
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

	mMoney -= 10;

	//*************** TO REFACTOR ***************************************
	cout << "\nAll your Pokemon are dead, you have lost the fight " << endl;
	//cout << "You have lost 10 gold, you now have " << mMoney << " gold" << endl;

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

int Trainer::GetAnswer()
{
	return mAnswerTrainer;
}

void Trainer::WinFight()
{
	//*************** TO REFACTOR ***************************************
	cout << "You have won the Battle !!!!! " << endl;
	int random = rand() % 101;
	if (random <= 50)
	{
		mMoney += 10;
		cout << "You won 10 gold, you now have " << mMoney << " gold" << endl;
		return;
	}
	else if (random > 50)
	{
		mPokeballs += 2;
		cout << "You won 2 new Pokeballs, you now have " << mPokeballs << " Pokeballs" << endl;
		return;
	}
	//*************** TO REFACTOR ***************************************
}

vector<Pokemon>& Trainer::GetPokemonTeam()
{
	return mPokemonTeam;
}
