#pragma once

#include <iostream>
#include "raylib.h"

#include "Battle.h"
#include "allPokemons.h"

//Variables
const char* firstLine = "";
const char* secondLine = "";
const char* thirdLine = "";

bool imageIsLoad = false;

Image playerPokemonImage = LoadImage("resources/white.png");
Image opponentPokemonImage = LoadImage("resources/white.png");

Texture2D opponentPokemonTexture;


Battle::Battle(Trainer& thePlayer)
{
	mThePlayer = &thePlayer;
	mMaxAbilityCost = 5;
}

Battle::Battle(Trainer& thePlayer, Trainer& opponentTrainer)
{
	mThePlayer = &thePlayer;
	mOpponentTrainer = &opponentTrainer;
	mMaxAbilityCost = 5;
}

void Battle::BattleUpdate()
{

}

void Battle::BattleDraw()
{
	DrawText(firstLine, 70, 775, 70, BLACK);
	DrawText(secondLine, 70, 870, 70, BLACK);
	DrawText(thirdLine, 70, 1050, 70, BLACK);

	if (!imageIsLoad)
	{
		ImageFormat(&opponentPokemonImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
		opponentPokemonTexture = LoadTextureFromImage(opponentPokemonImage);
		imageIsLoad = true;
	}

	DrawTexture(opponentPokemonTexture, 1080, 10, WHITE);
}

Pokemon Battle::ChooseOpponentPokemon()
{
	Pokemon* mPlayerPokemon = nullptr;
	Pokemon* mOpponnentPokemon = nullptr;

	firstLine = mOpponentTrainer->ChallengeTrainer();
	mMaxAbilityCost = 30;

	vector<Pokemon>& pokemonTeam = mOpponentTrainer->GetPokemonTeam();

	srand(time(NULL));
	int randomPokemon = rand() % pokemonTeam.size();
	mOpponnentPokemon = &pokemonTeam[randomPokemon];

	opponentPokemonImage = mOpponnentPokemon->GetPokemonImage();
	imageIsLoad = false;

	secondLine = mOpponentTrainer->Introduction();

	thirdLine = (char*) TextFormat("He is using %s to attack you", mOpponnentPokemon->GetPokemonName().c_str());

	return *mOpponnentPokemon;
}

void Battle::BattleAgainstTrainer(Pokemon& opponentPokemon)
{
	Pokemon* mPlayerPokemon = nullptr;
	Pokemon* mOpponnentPokemon = &opponentPokemon;

	return;

	//NEED TO REFACTOR SEND OR CHANGE PK
	mPlayerPokemon = &mThePlayer->SendOrChangePokemon();

	while (mOpponnentPokemon->GetPokemonLife() > 0 && mPlayerPokemon->GetPokemonLife() > 0)
	{
		//check attackotherpokemon if need to refactor
		if (mPlayerPokemon->AttackOtherPokemon(*mOpponnentPokemon))
		{
			//*************** TO REFACTOR ***************************************
			//cout << " damage to " << mOpponnentPokemon->GetPokemonName() << endl;
			//cout << "He now has " << mOpponnentPokemon->GetPokemonLife() << " pv\n" << endl;

			if (mOpponnentPokemon->GetPokemonLife() <= 0)
			{
				break;
			}

			srand(time(NULL));
			const vector<Ability>& abilities = mOpponnentPokemon->GetAbilities();
			int randomAbility = rand() % abilities.size();
			mOpponentPokemonAbility = abilities[randomAbility];

			//*************** TO REFACTOR ***************************************
			//cout << mOpponnentPokemon->GetPokemonName() << " used " << mOpponentPokemonAbility.GetName()
			//	<< ", it does " << mOpponnentPokemon->GetPokemonDamage() << " damage to your Pokemon" << endl;
			// You now have : pv

			mPlayerPokemon->TakeDamage(mOpponentPokemonAbility.GetDamage(), mOpponentPokemonAbility);

		}
		else
		{
			return BattleAgainstTrainer(*mOpponnentPokemon);
		}
	}

	if (mOpponnentPokemon->GetPokemonLife() <= 0)
	{
		//win fight check the refactor
		mThePlayer->WinFight();

		for (int i = 0; i < mThePlayer->GetPokemonTeam().size(); i++)
		{
			mThePlayer->GetPokemonTeam()[i].Rest();
		}

		if (mPlayerPokemon->GetAbilities().size() >= 4)
		{
			return;
		}

		//*************** TO REFACTOR ***************************************
		cout << "\nYour Pokemon is leveling up !!! \nYou can now learn a new ability !" << endl;
		mPlayerPokemon->LearnNewAbilities();
		//*************** TO REFACTOR ***************************************

		return;
	}

	if (mPlayerPokemon->GetPokemonLife() <= 0)
	{
		//*************** TO REFACTOR ***************************************
		//cout << "\nYour pokemon has been defeated, he now has " << mPlayerPokemon->GetPokemonLife() << "pv" << endl;

		if (mThePlayer->CheckIfTeamDead())
		{
			//you can maybe print the result here ?
			return;
		}
		if (!mThePlayer->CheckIfTeamDead())
		{
			//mDeadPlayerPokemon = *mPlayerPokemon;

			return BattleAgainstTrainer(*mOpponnentPokemon);
		}
	}
}



void Battle::BattleAgainstPokemon(bool firstTime)
{
	Pokemon* mPlayerPokemon = nullptr;
	Pokemon* mOpponnentPokemon = nullptr;

	if (firstTime == true)
	{
		mMaxAbilityCost = 30;

		int randomPokemon = rand() % allPokemons.size();
		mOpponnentPokemon = &allPokemons[randomPokemon];

		cout << "You have encounter a wild " << mOpponnentPokemon->GetPokemonName() << endl;

		mUsedOpponentPokemon = *mOpponnentPokemon;

		mPlayerPokemon = &mThePlayer->SendOrChangePokemon();
	}
	else
	{
		mPlayerPokemon = &mThePlayer->SendOrChangePokemon();

		if (mPlayerPokemon->GetPokemonLife() <= 0)
		{
			cout << "This pokemon is already dead, please choose an other pokemon" << endl;
			return BattleAgainstPokemon(false);
		}
	}


	mOpponnentPokemon = &mUsedOpponentPokemon;


	while (mOpponnentPokemon->GetPokemonLife() > 0 && mPlayerPokemon->GetPokemonLife() > 0)
	{
		cout << "Do you wish to try to capture " << mOpponnentPokemon->GetPokemonName() << " or attack it ?" << endl;
		cout << "1. Capture \n" << "2. Attack" << endl;
		int answer;
		cin >> answer;

		if (answer == 1)
		{
			if (mThePlayer->IsPokemonCaptured(*mOpponnentPokemon))
			{
				return;
			}

			const vector<Ability>& abilities = mOpponnentPokemon->GetAbilities();
			int randomAbility = rand() % abilities.size();
			mOpponentPokemonAbility = abilities[randomAbility];

			cout << mOpponnentPokemon->GetPokemonName() << " used " << mOpponentPokemonAbility.GetName()
				<< ", it does " << mOpponnentPokemon->GetPokemonDamage() << " damage to your Pokemon" << endl;
			// You now have : pv

			mPlayerPokemon->TakeDamage(mOpponentPokemonAbility.GetDamage(), mOpponentPokemonAbility);
		}
		else if (answer == 2)
		{
			if (mPlayerPokemon->AttackOtherPokemon(*mOpponnentPokemon) == true)
			{
				cout << " damage to " << mOpponnentPokemon->GetPokemonName() << endl;
				cout << "He now has " << mOpponnentPokemon->GetPokemonLife() << " pv\n" << endl;

				if (mOpponnentPokemon->GetPokemonLife() <= 0)
				{
					break;
				}

				const vector<Ability>& abilities = mOpponnentPokemon->GetAbilities();
				int randomAbility = rand() % abilities.size();
				mOpponentPokemonAbility = abilities[randomAbility];

				cout << mOpponnentPokemon->GetPokemonName() << " used " << mOpponentPokemonAbility.GetName()
					<< ", it does " << mOpponnentPokemon->GetPokemonDamage() << " damage to your Pokemon" << endl;
				// You now have : pv

				mPlayerPokemon->TakeDamage(mOpponentPokemonAbility.GetDamage(), mOpponentPokemonAbility);

			}
			else
			{
				return BattleAgainstPokemon(false);
			}
		}
	}

	if (mOpponnentPokemon->GetPokemonLife() <= 0)
	{
		mThePlayer->WinFight();

		for (int i = 0; i < mThePlayer->GetPokemonTeam().size(); i++)
		{
			mThePlayer->GetPokemonTeam()[i].Rest();
		}

		if (mPlayerPokemon->GetAbilities().size() >= 4)
		{
			return;
		}

		cout << "\nYour Pokemon is leveling up !!! \nYou can now learn a new ability !" << endl;
		mPlayerPokemon->LearnNewAbilities();

		return;
	}

	if (mPlayerPokemon->GetPokemonLife() <= 0)
	{
		cout << "\nYour pokemon has been defeated, he now has " << mPlayerPokemon->GetPokemonLife() << "pv" << endl;

		if (mThePlayer->CheckIfTeamDead())
		{
			return;
		}
		if (!mThePlayer->CheckIfTeamDead())
		{
			mDeadPlayerPokemon = *mPlayerPokemon;

			return BattleAgainstPokemon(false);
		}
	}
}
