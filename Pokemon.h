#pragma once
#include <iostream>
#include <vector>

#include "raylib.h"
#include "PokeType.h"
#include "Ability.h"

using namespace std;

class Pokemon
{
private:
	Image mImagePokemon;
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
	Pokemon(Image imagePokemon, string name, string description, PokeType type, int life, vector<Ability> abilitie);

	void UpdatePokemon();
	void DrawPokemon();

	const vector<Ability>& GetAbilities();
	string GetPokemonName();
	Image* GetPokemonImage();
	float GetPokemonLife();
	float GetPokemonMaxLife();
	float GetPokemonDamage();

	void TakeDamage(int damage, Ability abilityAttack);
	void Rest();

	bool CheckIfCanUseAbility();
	void AttackOtherPokemon(Pokemon& pokemon);
	void LearnNewAbilities();

	void GetDescription();
};

