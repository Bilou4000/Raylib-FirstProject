#pragma once

#include <iostream>
#include <vector>

#include "Pokemon.h"

using namespace std;


class Trainer
{
private:
	string mFirstName;
	string mLastName;
	string mCatchPhrase;
	int mMoney = 1000;
	int mLifePoints = 100;
	vector<Pokemon> mPokemonTeam;
	int mPokeballs = 10;
	int mCurrentPokemonIndex = 0;

	int mAnswerTrainer = NULL;

public:
	Trainer();
	Trainer(string firstName, string lastName, string CatchPhrase, vector<Pokemon> PokemonTeam);

	void UpdateTrainer();
	void DrawTrainer();

	void ChoosePokemonToUse();

	const char* Introduction();
	const char* ChallengeTrainer();
	bool IsPokemonCaptured(Pokemon& pokemon);
	bool CheckIfTeamDead();
	Pokemon& SendOrChangePokemon();
	bool WinFight();

	vector<Pokemon>& GetPokemonTeam();
	int GetAnswerTrainer() const;
	int GetMoney() const;
	int GetPokeballs() const;
};

