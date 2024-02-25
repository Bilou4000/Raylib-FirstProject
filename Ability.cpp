#include "Ability.h"

Ability::Ability()
{
	mName = "Thunder";
	mDamage = 40;
	mPoketype = PokeType::Electric;
	mNumberOfUse = 3;
	mMaxNumberOfUse = 3;
}

Ability::Ability(string name, int damage, PokeType poketype, int numberOfUse)
{
	mName = name;
	mDamage = damage;
	mPoketype = poketype;
	mNumberOfUse = numberOfUse;
	mMaxNumberOfUse = numberOfUse;
}

int Ability::GetDamage()
{
	return mDamage;
}

int Ability::GetTurnUse()
{
	return mNumberOfUse;
}

string Ability::GetName()
{
	return mName;
}

PokeType Ability::GetPoketype()
{
	return mPoketype;
}

void Ability::ResetAbilityUse()
{
	mNumberOfUse = mMaxNumberOfUse;
}

void Ability::UseAbility()
{
	mNumberOfUse -= 1;
}
