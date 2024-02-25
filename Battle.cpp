#pragma once

#include <iostream>
#include "Battle.h"
#include "allPokemons.h"

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

void Battle::BattleAgainstTrainer(bool firstTime)
{
	Pokemon* mPlayerPokemon = nullptr;
	Pokemon* mOpponnentPokemon = nullptr;

	if (firstTime)
	{
		mMaxAbilityCost = 30;

		vector<Pokemon>& pokemonTeam = mOpponentTrainer->GetPokemonTeam();
		int randomPokemon = rand() % pokemonTeam.size();
		mOpponnentPokemon = &pokemonTeam[randomPokemon];

		//mOpponentTrainer->Introduction();
		//*************** TO REFACTOR ***************************************
		//std::cout << "He is using " << mOpponnentPokemon->GetPokemonName() << " to attack you" << endl;

		mUsedOpponentPokemon = *mOpponnentPokemon;

		mPlayerPokemon = &mThePlayer->SendOrChangePokemon();
	}
	else
	{
		mPlayerPokemon = &mThePlayer->SendOrChangePokemon();

		if (mPlayerPokemon->GetPokemonLife() <= 0)
		{
			//*************** TO REFACTOR ***************************************
			cout << "This pokemon is already dead, please choose an other pokemon" << endl;

			return BattleAgainstTrainer(false);
		}
	}

	mOpponnentPokemon = &mUsedOpponentPokemon;

	while (mOpponnentPokemon->GetPokemonLife() > 0 && mPlayerPokemon->GetPokemonLife() > 0)
	{
		if (mPlayerPokemon->AttackOtherPokemon(*mOpponnentPokemon))
		{
			//*************** TO REFACTOR ***************************************
			//cout << " damage to " << mOpponnentPokemon->GetPokemonName() << endl;
			//cout << "He now has " << mOpponnentPokemon->GetPokemonLife() << " pv\n" << endl;

			if (mOpponnentPokemon->GetPokemonLife() <= 0)
			{
				break;
			}

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
			return BattleAgainstTrainer(false);
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

		//*************** TO REFACTOR ***************************************
		cout << "\nYour Pokemon is leveling up !!! \nYou can now learn a new ability !" << endl;
		mPlayerPokemon->LearnNewAbilities();

		return;
	}

	if (mPlayerPokemon->GetPokemonLife() <= 0)
	{
		//*************** TO REFACTOR ***************************************
		//cout << "\nYour pokemon has been defeated, he now has " << mPlayerPokemon->GetPokemonLife() << "pv" << endl;

		if (mThePlayer->CheckIfTeamDead())
		{
			return;
		}
		if (!mThePlayer->CheckIfTeamDead())
		{
			mDeadPlayerPokemon = *mPlayerPokemon;

			return BattleAgainstTrainer(false);
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
