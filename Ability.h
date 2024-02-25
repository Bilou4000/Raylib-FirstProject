#pragma once

#include <iostream>
#include <vector>

#include "PokeType.h"

using namespace std;

class Ability
{
private:
	string mName;
	int mDamage;
	PokeType mPoketype;
	int mNumberOfUse;
	int mMaxNumberOfUse;

public:
	Ability();
	Ability(string name, int damage, PokeType poketype, int numberOfUse);

	int GetDamage();
	int GetTurnUse();
	string GetName();
	PokeType GetPoketype();
	void ResetAbilityUse();
	void UseAbility();
};

