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
	void Update();
	void Draw();

	void ChooseName();
	void ChoosePokemon();

	void DrawName();
	void DrawPokemon();

private:
	string mFirstName = "";
	string mLastName = "";

	Rectangle mNameAnswerBox {};
	char mName[MAX_INPUT_CHARS + 1] = "\0";
	int mNameLetterCount = 0;
	int mInput = 0;

	int mBoxInput = NULL;
	int mAnswerPk = NULL;

	Rectangle mPkAnswerBox { 780, 850, 80, 70 };

	Pokemon mPlayerPokemon;
	vector<Pokemon> mStarterPokemons {};
};

