#pragma once

#include <iostream>
#include <vector>

#include "PokeType.h"

using namespace std;

class Ability
{
private:
	string mName;
	string mTypeName;
	PokeType mPoketype;
	int mDamage;
	int mNumberOfUse;
	int mMaxNumberOfUse;

public:
	Ability();
	Ability(string name, string typeName, int damage, PokeType poketype, int numberOfUse);

	void ResetAbilityUse();
	void UseAbility();

	int GetDamage() const;
	int GetTurnUse() const;
	string GetName() const;
	string GetTypeName() const;
	PokeType GetPoketype() const;

};

