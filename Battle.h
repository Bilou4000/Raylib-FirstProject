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

	void BattleTrainerUpdate();
	void BattleTrainerDraw();

	void BattleCaptureUpdate();
	void BattleCaptureDraw();

	void DrawChooseIfCapture();
	void UpdateChooseIfCapture();

	Pokemon ChooseOpponentPokemon();
	Pokemon ChoosePokemonToCapture();
	void BattleAgainstTrainer(Pokemon& opponentPokemon);
	bool EndOfBattle();

	void BattleAgainstPokemon(Pokemon& opponentPokemon);
	void AttackPokemon();
	void CapturePokemon();
};

