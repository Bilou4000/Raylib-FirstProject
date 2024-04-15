#pragma once

#include "Pokemon.h"
#include "allAbilities.h"

#include <iostream>
#include <vector>
using namespace std;

class AllPokemons
{
public:
	static Pokemon Snorlax;
	static Pokemon Darumaka;
	static Pokemon Magikarp;
	static Pokemon Pansage;
	static Pokemon Minun;
	static Pokemon Plusle;
	static Pokemon Vanillite;
	static Pokemon Pancham;
	static Pokemon Gulpin;
	static Pokemon Diglett;
	static Pokemon Tornadus;
	static Pokemon Mewtwo;
	static Pokemon Caterpie;
	static Pokemon Sudowoodo;
	static Pokemon Spectrier;
	static Pokemon Dragonair;
	static Pokemon Absol;
	static Pokemon Copperajah;
	static Pokemon Cleffa;

	static vector<Pokemon> allPokemons;

	static void Load();
};
