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

	void ResetAbilityUse();
	void UseAbility();

	int GetDamage() const;
	int GetTurnUse() const;
	string GetName() const;
	PokeType GetPoketype() const;

};

