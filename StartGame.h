#pragma once

#include <iostream>
#include <string>

#include "raylib.h"
#include "allPokemons.h"

#define MAX_INPUT_CHARS  9

using namespace std;

class StartGame
{
public:
	void Init();
	bool Update();
	void Draw();

	void ChooseName();
	bool ChoosePokemon();

	void DrawName();
	void DrawPokemon();

public:
	string mFirstName = "";
	string mLastName = "";

	Pokemon mPlayerPokemon;

private:
	char mName[MAX_INPUT_CHARS + 1] = "\0";
	int mNameLetterCount = 0;
	int mInput = 0;

	int mBoxInput = NULL;
	int mAnswerPk = NULL;

	Rectangle mNameAnswerBox {};

	Rectangle mPkAnswerBox { 780, 950, 80, 70 };
	vector<Pokemon> mStarterPokemons;
};

