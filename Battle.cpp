#pragma once

#include <iostream>
#include "raylib.h"

#include "Battle.h"
#include "allPokemons.h"

//Variables
const char* firstLine = "";
const char* secondLine = "";
const char* thirdLine = "";
const char* toChangeLine = "";

bool imageIsLoad = true, imageIsUnload = false;
bool isChangingPokemon = false, pokemonCanUseAbility = false;
int positionInCode = 0;

Image playerPokemonImage = LoadImage("resources/white.png");
Image opponentPokemonImage = LoadImage("resources/white.png");

Texture2D opponentPokemonTexture;
Texture2D playerPokemonTexture;

//Function
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
	mThePlayer->UpdateTrainer();
	mPlayerPokemon->UpdatePokemon();

	if (positionInCode == 2 && IsKeyReleased(KEY_SPACE))
	{
		firstLine = toChangeLine;
		secondLine = "";
		imageIsLoad = false;
	}

	if (positionInCode == 3)
	{
		firstLine = "";
		if (!imageIsUnload) 
		{
			UnloadTexture(opponentPokemonTexture);
			imageIsUnload = true;
		}
	}

 	if (IsKeyPressed(KEY_SPACE) && positionInCode != 3 && positionInCode != 4 && !pokemonCanUseAbility)
	{
		positionInCode++;
	}

	if (mThePlayer->GetAnswerTrainer() > 0 && positionInCode == 3)
	{
		positionInCode = 4;
	}

	if (positionInCode == 6)
	{
		if (mPlayerPokemon->GetAnswerPokemon() > 0)
		{
			positionInCode = 7;
		}
	}
}

void Battle::BattleDraw()
{
	mThePlayer->DrawTrainer();
	mPlayerPokemon->DrawPokemon();

	DrawText(firstLine, 70, 775, 70, BLACK);
	DrawText(secondLine, 70, 870, 70, BLACK);
	DrawText(thirdLine, 70, 1050, 70, BLACK);

	if (!imageIsLoad)
	{
		ImageFormat(&opponentPokemonImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
		ImageFormat(&playerPokemonImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

		opponentPokemonTexture = LoadTextureFromImage(opponentPokemonImage);
		playerPokemonTexture = LoadTextureFromImage(playerPokemonImage);

		imageIsLoad = true;
	}

	if (positionInCode < 3)
	{
		DrawTexture(opponentPokemonTexture, 1080, 30, WHITE);
	}

	if (positionInCode == 4)
	{
		imageIsLoad = false;
	}

	if (positionInCode >= 5)
	{
		DrawTexture(opponentPokemonTexture, 1080, 30, WHITE);
		DrawTexture(playerPokemonTexture, 50, 200, WHITE);

		DrawText(TextFormat("%s", mOpponnentPokemon->GetPokemonName().c_str()), 800, 150, 60, BLACK);
		DrawText(TextFormat("%i / %i", int(mOpponnentPokemon->GetPokemonLife()), int(mOpponnentPokemon->GetPokemonMaxLife())), 800, 250, 50, RED);

		DrawText(TextFormat("%s", mPlayerPokemon->GetPokemonName().c_str()), 500, 500, 60, BLACK);
		DrawText(TextFormat("%i / %i", int(mPlayerPokemon->GetPokemonLife()), int(mPlayerPokemon->GetPokemonMaxLife())), 500, 600, 50, RED);		
	}

	if (positionInCode == 5)
	{
		firstLine = TextFormat("GO ! %s !", mPlayerPokemon->GetPokemonName().c_str());
	}
}

Pokemon Battle::ChooseOpponentPokemon()
{
	Pokemon* mOpponnentPokemon = nullptr;

	positionInCode = 0;

	firstLine = mOpponentTrainer->ChallengeTrainer();
	mMaxAbilityCost = 30;

	vector<Pokemon>& pokemonTeam = mOpponentTrainer->GetPokemonTeam();

	srand(time(NULL));
	int randomPokemon = rand() % pokemonTeam.size();
	mOpponnentPokemon = &pokemonTeam[randomPokemon];

	opponentPokemonImage = *(mOpponnentPokemon->GetPokemonImage());

	secondLine = mOpponentTrainer->Introduction();

	positionInCode = 1;
	toChangeLine = TextFormat("He is using %s to attack you", mOpponnentPokemon->GetPokemonName().c_str());

	return *mOpponnentPokemon;
}

void Battle::BattleAgainstTrainer(Pokemon& opponentPokemon)
{
	mOpponnentPokemon = &opponentPokemon;

	if (positionInCode == 3)
	{
		firstLine = "";
		secondLine = "";
		mThePlayer->ChoosePokemonToUse();
	}

	if (positionInCode == 4)
	{
		mPlayerPokemon = &mThePlayer->SendOrChangePokemon();
		playerPokemonImage = *(mPlayerPokemon->GetPokemonImage());
		positionInCode = 5;
	}
	
	if (positionInCode == 6)
	{
		if(mOpponnentPokemon->GetPokemonLife() > 0 && mPlayerPokemon->GetPokemonLife() > 0)
		{
			if (mPlayerPokemon->CheckIfCanUseAbility())
			{
				firstLine = "";
				secondLine = "";

				pokemonCanUseAbility = true;
			}
			else
			{
				pokemonCanUseAbility = false;

				firstLine = "Your pokemon can't use any more skill, ";
				secondLine = "Please change it.";
			}
		}
	}

 	if (positionInCode == 7 && !pokemonCanUseAbility)
	{
		positionInCode = 3;
		return BattleAgainstTrainer(*mOpponnentPokemon);
	}
	else if (positionInCode == 7 && pokemonCanUseAbility)
	{
		mPlayerPokemon->AttackOtherPokemon(*mOpponnentPokemon);
		positionInCode = 8;
		return; //TO ERASE
		//*************** TO REFACTOR ***************************************
		//cout << " damage to " << mOpponnentPokemon->GetPokemonName() << endl;
		//cout << "He now has " << mOpponnentPokemon->GetPokemonLife() << " pv\n" << endl;

		//if (mOpponnentPokemon->GetPokemonLife() <= 0)
		//{
		//	break;
		//}

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

	return; //TO ERASE

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

		//mUsedOpponentPokemon = *mOpponnentPokemon;

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


	//mOpponnentPokemon = &mUsedOpponentPokemon;


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
			//if (mPlayerPokemon->AttackOtherPokemon(*mOpponnentPokemon) == true)
			//{
			//	cout << " damage to " << mOpponnentPokemon->GetPokemonName() << endl;
			//	cout << "He now has " << mOpponnentPokemon->GetPokemonLife() << " pv\n" << endl;

			//	if (mOpponnentPokemon->GetPokemonLife() <= 0)
			//	{
			//		break;
			//	}

			//	const vector<Ability>& abilities = mOpponnentPokemon->GetAbilities();
			//	int randomAbility = rand() % abilities.size();
			//	mOpponentPokemonAbility = abilities[randomAbility];

			//	cout << mOpponnentPokemon->GetPokemonName() << " used " << mOpponentPokemonAbility.GetName()
			//		<< ", it does " << mOpponnentPokemon->GetPokemonDamage() << " damage to your Pokemon" << endl;
			//	// You now have : pv

			//	mPlayerPokemon->TakeDamage(mOpponentPokemonAbility.GetDamage(), mOpponentPokemonAbility);

			//}
			//else
			//{
			//	return BattleAgainstPokemon(false);
			//}
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
			//mDeadPlayerPokemon = *mPlayerPokemon;

			return BattleAgainstPokemon(false);
		}
	}
}
