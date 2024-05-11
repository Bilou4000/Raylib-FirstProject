#include "Ability.h"

Ability::Ability()
{
	mName = "Thunder";
	mTypeName = "Electric";
	mDamage = 40;
	mPoketype = PokeType::Electric;
	mNumberOfUse = 3;
	mMaxNumberOfUse = 3;
}

Ability::Ability(string name, string typeName, int damage, PokeType poketype, int numberOfUse)
{
	mName = name;
	mTypeName = typeName;
	mDamage = damage;
	mPoketype = poketype;
	mNumberOfUse = numberOfUse;
	mMaxNumberOfUse = numberOfUse;
}

int Ability::GetDamage() const
{
	return mDamage;
}

int Ability::GetTurnUse() const
{
	return mNumberOfUse;
}

string Ability::GetName() const
{
	return mName;
}

string Ability::GetTypeName() const
{
	return mTypeName;
}

PokeType Ability::GetPoketype() const
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
