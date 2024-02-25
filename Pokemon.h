#pragma once
#include <iostream>
#include <vector>

#include "PokeType.h"
#include "Ability.h"

using namespace std;

class Pokemon
{
private:
	string mName;
	string mDescription;
	PokeType mType;
	int mLevel;
	float mLife;
	float mMaxLife;
	float mDamageResistance;
	vector<Ability> mAbilities;


public:
	Pokemon();
	Pokemon(string name, string description, PokeType type, int life, vector<Ability> abilitie);

	void Update();
	void Draw();

	const vector<Ability>& GetAbilities();
	string GetPokemonName();
	float GetPokemonLife();
	float GetPokemonMaxLife();
	float GetPokemonDamage();
	void TakeDamage(int damage, Ability abilityAttack);
	void Rest();

	bool AttackOtherPokemon(Pokemon& pokemon);
	void LearnNewAbilities();

	void GetDescription();
};

