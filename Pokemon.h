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
	Texture2D mTexturePokemon;
	string mName;
	string mDescription;
	string mTypeName;
	PokeType mType;
	int mLevel;
	float mLife;
	float mMaxLife;
	float mDamageResistance;
	vector<Ability> mAbilities;

	int mAnswerPokemon = NULL;

public:
	Pokemon();
	Pokemon(Texture2D texturePokemon, string name, string description, string typeName, PokeType type, int life, vector<Ability> abilitie);

	void UpdatePokemon();
	void DrawPokemon();

	void TakeDamage(int damage, Ability abilityAttack);
	void Rest();
	bool CheckIfCanUseAbility();
	void AttackOtherPokemon(Pokemon& pokemon);
	void ChooseAbility();
	void LearnNewAbilities();

	const vector<Ability>& GetAbilities() const;
	string GetDescription() const;
	string GetPokemonName() const;
	string GetPokemonTypeName() const;
	Texture2D* GetPokemonTexture();
	float GetPokemonLife() const;
	float GetPokemonMaxLife() const;
	float GetPokemonDamage() const;
	int GetAnswerPokemon() const;
};

