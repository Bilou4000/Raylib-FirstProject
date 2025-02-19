using namespace std;
#include <algorithm>
#include <iostream>
#include <string>

#include "raylib.h"
#include "Pokemon.h"
#include "allAbilities.h"

//Variables
bool mouseOnBox;
bool canUseSkill = false, canAbilityBeUse = true, pokemonHasDoneDamage = false, isChoosingAbility = false, abilityIsTaken = false;

int keyInput = NULL;
int answerPokemon = NULL;
int letterCount = 0;

char name[2] = "\0";
const char* damageText = "";

Rectangle abilityBox { 1000, 550, 500, 500 };
Rectangle contourAbilityBox { 985, 535, 530, 530 };
Rectangle abilityAnswerBox { 780, 850, 80, 70 };
Rectangle allAbilityBox{ 0 , 55, 1600, 650 };

Pokemon::Pokemon()
{
	mName = "Minum";
	mDescription = "Promotes blood circulation and relieves muscular tension.";
	mTypeName = "Electric";
	mType = PokeType::Electric;
	mLevel = 1;
	mLife = 60;
	mMaxLife = mLife;
	mAbilities = { Thunder, Aeroblast };
}

Pokemon::Pokemon(Texture2D texturePokemon, string name, string description, string typeName, PokeType type, int life, vector<Ability> abilitie)
{
	mTexturePokemon = texturePokemon;
	mName = name;
	mDescription = description;
	mType = type;
	mTypeName = typeName;
	mLevel = 1;
	mLife = life;
	mMaxLife = mLife;
	mAbilities = abilitie;
}

void Pokemon::UpdatePokemon()
{
	if (canUseSkill)
	{

		mouseOnBox = true;

		if (mouseOnBox && GetKeyPressed())
		{
			keyInput = GetCharPressed();
		}

		if (IsKeyPressed(KEY_ENTER) && answerPokemon > 0 && answerPokemon <= mAbilities.size())
		{
			if (mAbilities[answerPokemon - 1].GetTurnUse() <= 0)
			{
				answerPokemon = NULL;
				mAnswerPokemon = NULL;

				canAbilityBeUse = false;
			}
			else
			{
				mAnswerPokemon = answerPokemon;
				cout << mAnswerPokemon << endl;
			}
		}

		if (IsKeyPressed(KEY_SPACE) && !canAbilityBeUse)
		{
			canAbilityBeUse = true;
		}
	}


	if (isChoosingAbility)
	{
		canUseSkill = false;

		mouseOnBox = true;

		if (mouseOnBox && GetKeyPressed())
		{
			keyInput = GetCharPressed();

			if (isdigit(keyInput) && letterCount < 2)
			{
				name[letterCount] = (char) keyInput;
				letterCount++;

			}
		}

		if (IsKeyPressed(KEY_BACKSPACE) && mouseOnBox)
		{
			letterCount--;
			if (letterCount < 0)
			{
				letterCount = 0;
			}
			name[letterCount] = '\0';		
		}


		if (IsKeyPressed(KEY_ENTER) && answerPokemon > 0 && answerPokemon <= allAbility.size())
		{
			string wantedAbilityName = allAbility[answerPokemon - 1].GetName();

			for (Ability abilities : mAbilities)
			{
				if (abilities.GetName() == allAbility[answerPokemon - 1].GetName())
				{
					abilityIsTaken = true;
					answerPokemon = NULL;
					mAnswerPokemon = NULL;
					break;
				}
				else
				{
					abilityIsTaken = false;
					mAnswerPokemon = answerPokemon;
					cout << mAnswerPokemon << endl;
				}
			}
		}

		if (IsKeyPressed(KEY_SPACE) && abilityIsTaken)
		{
			abilityIsTaken = false;
		}
	}
}

void Pokemon::DrawPokemon()
{
	if (canUseSkill)
	{
		DrawRectangleRec(contourAbilityBox, BLACK);
		DrawRectangleRec(abilityBox, WHITE);

		if (!canAbilityBeUse)
		{
			DrawText("NOT enough turn point to use that ability ", 70, 785, 40, BLACK);
			DrawText("Please use an other one.", 70, 860, 60, BLACK);
		}
		else
		{
			DrawText("Choose an ability : ", 70, 775, 70, BLACK);
			DrawText("Write the corresponding number :", 70, 870, 40, RED);
			DrawRectangleRec(abilityAnswerBox, LIGHTGRAY);

			if (mouseOnBox)
			{
				if (isdigit(keyInput))
				{
					string printAnswer { (char) keyInput };
					DrawText(TextFormat("%s", printAnswer.c_str()), 800, 855, 70, BLACK);

					answerPokemon = stoi(printAnswer);
				}
				else
				{
					DrawText("_", 800, 855, 70, BLACK);
				}
			}
		}

		float abilityPos = 600;
		for (int i = 0; i < mAbilities.size(); i++)
		{
			DrawText(TextFormat("%i. %s ", i + 1, mAbilities[i].GetName().c_str()), 1030, abilityPos, 35, BLACK);
			DrawText(TextFormat("(%s)", mAbilities[i].GetTypeName().c_str()), 1030, abilityPos + 40, 30, DARKGRAY);
			abilityPos += 100;
		}
	}


	if (isChoosingAbility)
	{
		DrawRectangleRec(allAbilityBox, WHITE);

		if (abilityIsTaken)
		{
			DrawText("You already have this ability. ", 70, 785, 60, BLACK);
			DrawText("Please choose an other one.", 70, 860, 60, BLACK);
		}
		else
		{
			DrawText("Choose an ability : ", 70, 775, 70, BLACK);
			DrawText("Write the corresponding number :", 70, 870, 40, RED);
			DrawRectangle(780, 850, 100, 70, LIGHTGRAY);

			if (mouseOnBox)
			{
				if (isdigit(name[0]))
				{
					string printAnswer { name };
					DrawText(TextFormat("%s", printAnswer.c_str()), 790, 855, 70, BLACK);

					answerPokemon = stoi(printAnswer);

					if (name[1] == '\0')
					{
						DrawText("_", 800 + MeasureText(name, 70), 855, 70, BLACK);
					}
					
				}
				else
				{
					DrawText("_", 800, 855, 70, BLACK);
				}
				
			}
		}

		float abilityYPos = 100;
		float abilityXPos = 0;
		int abilityNumber = 0;

		for (int i = 0; i < allAbility.size() / 3; i++)
		{
			abilityXPos = 80;
			for (int j = abilityNumber; j < 3 + abilityNumber; j++)
			{
				DrawText(TextFormat("%i. %s ", j + 1, allAbility[j].GetName().c_str()), abilityXPos, abilityYPos, 30, BLACK);
				DrawText(TextFormat("(%s)", allAbility[j].GetTypeName().c_str()), abilityXPos, abilityYPos + 35, 25, DARKGRAY);
				abilityXPos += 530;
			}
			abilityNumber += 3;
			abilityYPos += 100;
		}
	}
}

bool Pokemon::CheckIfCanUseAbility()
{
	for (int i = 0; i < mAbilities.size(); i++)
	{
		if (mAbilities[i].GetTurnUse() > 0)
		{
			canUseSkill = true;
			return true;
		}
	}
	return false;
}


void Pokemon::AttackOtherPokemon(Pokemon& pokemon)
{
	Ability* abilityBeingUsed = &mAbilities[mAnswerPokemon - 1];

	pokemon.TakeDamage(abilityBeingUsed->GetDamage(), *abilityBeingUsed);
	abilityBeingUsed->UseAbility();

	canUseSkill = false;

	mAnswerPokemon = NULL;
	answerPokemon = NULL;
	return;
}

void Pokemon::TakeDamage(int damage, Ability abilityAttack)
{
	float matrix[18][18] = {
		/* NORMAL   */ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0 },
		/* FIRE     */ { 1.0, 0.5, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0 },
		/* WATER    */ { 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
		/* GRASS    */ { 1.0, 0.5, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 0.5, 1.0 },
		/* ELECTRIC */ { 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
		/* ICE      */ { 1.0, 0.5, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0 },
		/* FIGHTING */ { 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5 },
		/* POISON   */ { 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 1.0, 0.5, 1.0, 1.0, 0.0, 2.0 },
		/* GROUND   */ { 1.0, 2.0, 1.0, 0.5, 2.0, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0 },
		/* FLYING   */ { 1.0, 1.0, 1.0, 2.0, 0.5, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0 },
		/* PSYCHIC  */ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0 },
		/* BUG      */ { 1.0, 0.5, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5 },
		/* ROCK     */ { 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 2.0, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0 },
		/* GHOST    */ { 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 1.0 },
		/* DRAGON   */ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0 },
		/* DARK     */ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5 },
		/* STEEL    */ { 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 2.0 },
		/* FAIRY    */ { 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 2.0, 2.0, 2.0, 1.0 } };

	int indexAbilityType = (int) abilityAttack.GetPoketype();
	int indexPokemonType = (int) mType;
	float resistance = matrix[indexAbilityType][indexPokemonType];
	float allDamage = damage * resistance;
	mDamageResistance = allDamage;

	mLife -= allDamage;
}

void Pokemon::Rest()
{
	mLife = mMaxLife;

	for (int i = 0; i < mAbilities.size(); i++)
	{
		mAbilities[i].ResetAbilityUse();
	}
}

void Pokemon::ChooseAbility()
{
	isChoosingAbility = true;
}

void Pokemon::LearnNewAbilities()
{
	mAbilities.push_back(allAbility[mAnswerPokemon - 1]);

	isChoosingAbility = false;

	letterCount = 0;
	name[0] = '\0';
	name[1] = '\0';

	mAnswerPokemon = NULL;
	answerPokemon = NULL;
	return;
}

string Pokemon::GetDescription() const
{
	return mDescription;
}

Texture2D* Pokemon::GetPokemonTexture()
{
	return &mTexturePokemon;
}

const vector<Ability>& Pokemon::GetAbilities() const
{
	return mAbilities;
}

string Pokemon::GetPokemonName() const
{
	return mName;
}

string Pokemon::GetPokemonTypeName() const
{
	return mTypeName;
}

float Pokemon::GetPokemonLife() const
{
	return mLife;
}

float Pokemon::GetPokemonMaxLife() const
{
	return mMaxLife;
}

float Pokemon::GetPokemonDamage() const
{
	return mDamageResistance;
}

int Pokemon::GetAnswerPokemon() const
{
	return mAnswerPokemon;
}

