#pragma once
#include <iostream>

#include "raylib.h"
#include "Trainer.h"
#include "allPokemons.h"
#include "Battle.h"

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
	//
}

void Trainer::DrawTrainer()
{
	DrawText(mFirstLine, 70, 775, 35, BLACK);
	DrawText(mSecondLine, 70, 775 + 60, 35, BLACK);
}

const char* Trainer::Introduction()
{
	return (char*) TextFormat("%s %s said : %s", mFirstName.c_str(), mLastName.c_str(), mCatchPhrase.c_str());
}

const char* Trainer::ChallengeTrainer()
{
	return (char*) TextFormat("You are challenging %s %s !!!", mFirstName.c_str(), mLastName.c_str());
}

void Trainer::ChallengePokemon(Trainer& thePlayer)
{
	//*************** TO REFACTOR ***************************************
	cout << "\nYou just found a wild pokemon !!" << endl;

	//Battle theBattle = Battle(thePlayer);
	//theBattle.BattleAgainstPokemon(true);
}

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
	int pokemonIndex = 0;
	//int answer;

	//*************** TO REFACTOR ***************************************
	//cout << "\nYou have this Pokemon team, please choose one to use" << endl;
	//for (int i = 1; i < mPokemonTeam.size() + 1; i++)
	//{
	//	//add type ?
	//	cout << i << ". " << mPokemonTeam[i - 1].GetPokemonName() << endl;
	//}

	//cout << "Which Pokemon do you want to use ? (write the corresponding number) : " << endl;
	//cin >> pokemonIndex;
	//*************** TO REFACTOR ***************************************

	Pokemon& pokemonWantingToBeUse = mPokemonTeam[pokemonIndex - 1];

	mCurrentPokemonIndex = pokemonIndex - 1;
	return pokemonWantingToBeUse;
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
