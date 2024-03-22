#pragma once

#include "Trainer.h"
#include "Pokemon.h"
#include "Ability.h"

class Battle
{
private:
	Trainer* mThePlayer;
	Trainer* mOpponentTrainer;
	Ability mOpponentPokemonAbility;
	Pokemon* mOpponnentPokemon = nullptr;
	Pokemon* mPlayerPokemon = nullptr;
	int mMaxAbilityCost;
	int mNuberOfTimeAbiityWasUsed = 0;

public:
	Battle(Trainer& thePlayer);
	Battle(Trainer& thePlayer, Trainer& opponentTrainer);

	void BattleUpdate();
	void BattleDraw();

	Pokemon ChooseOpponentPokemon();
	void BattleAgainstTrainer(Pokemon& opponentPokemon);
	void BattleAgainstPokemon(bool firstTime);
};

