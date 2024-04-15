#pragma once

#include <iostream>
#include <string>
#include "raylib.h"

#include "Battle.h"
#include "allPokemons.h"

//Variables
const char* firstLine = "";
const char* secondLine = "";
const char* thirdLine = "";
const char* toChangeLine = "";

bool imageIsLoad = true, imageIsUnload = false, battleIsFinished = false;
bool isChangingPokemon = false, pokemonCanUseAbility = false, opponentPokemonIsDead = false, playerPokemonIsDead = false, pokemonIsLevelingUp = false, canLearnNewAbility = true;
int positionInCode = 0;

Rectangle captureAnswerBox { 780, 1060, 80, 70 };
int captureBoxInput = NULL;
int answerCapture = NULL;
int isCapturing = -1;
bool canCapture = true, hasManagedToCapture = true;

Image playerPokemonImage = LoadImage("resources/white.png");
Image opponentPokemonImage = LoadImage("resources/white.png");

Texture2D opponentPokemonTexture;
Texture2D playerPokemonTexture;

//Function
Battle::Battle(Trainer& thePlayer)
{
	mThePlayer = &thePlayer;
	mMaxAbilityCost = 5;
}

Battle::Battle(Trainer& thePlayer, Trainer& opponentTrainer)
{
	mThePlayer = &thePlayer;
	mOpponentTrainer = &opponentTrainer;
	mMaxAbilityCost = 5;
}


//AGAINST TRAINER
void Battle::BattleTrainerUpdate()
{
	mThePlayer->UpdateTrainer();
	mPlayerPokemon->UpdatePokemon();

	if (positionInCode == 2 && IsKeyReleased(KEY_SPACE))
	{
		firstLine = toChangeLine;
		secondLine = "";
		imageIsLoad = false;
	}

	if (positionInCode == 3)
	{
		firstLine = "";
		if (!imageIsUnload) 
		{
			UnloadTexture(opponentPokemonTexture);
			imageIsUnload = true;
		}
	}

 	if (IsKeyPressed(KEY_SPACE) && positionInCode != 3 && positionInCode != 4 && !pokemonCanUseAbility && !pokemonIsLevelingUp)
	{
		positionInCode++;
	}

	if (mThePlayer->GetAnswerTrainer() > 0 && positionInCode == 3)
	{
		positionInCode = 4;
	}

	if (positionInCode == 6)
	{
		if (mPlayerPokemon->GetAnswerPokemon() > 0)
		{
			positionInCode = 7;
		}
	}

	if (positionInCode == 13 && mPlayerPokemon->GetAnswerPokemon() > 0)
	{
		positionInCode = 14;
	}
}

void Battle::BattleTrainerDraw()
{
	mThePlayer->DrawTrainer();
	mPlayerPokemon->DrawPokemon();

	DrawText(firstLine, 70, 775, 70, BLACK);
	DrawText(secondLine, 70, 870, 70, BLACK);
 	DrawText(thirdLine, 70, 1050, 70, BLACK);

	if (!imageIsLoad)
	{
		ImageFormat(&opponentPokemonImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
		ImageFormat(&playerPokemonImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

		opponentPokemonTexture = LoadTextureFromImage(opponentPokemonImage);
		playerPokemonTexture = LoadTextureFromImage(playerPokemonImage);

		imageIsLoad = true;
	}

	if (positionInCode == 2)
	{
		DrawTexture(opponentPokemonTexture, 1080, 30, WHITE);
	}

	if (positionInCode == 4)
	{
		imageIsLoad = false;
	}

	if (positionInCode >= 5 && (positionInCode != 13 || !opponentPokemonIsDead))
	{
		DrawTexture(opponentPokemonTexture, 1080, 30, WHITE);
		DrawTexture(playerPokemonTexture, 50, 200, WHITE);

		DrawText(TextFormat("%s", mOpponnentPokemon->GetPokemonName().c_str()), 700, 150, 60, BLACK);
		DrawText(TextFormat("%i / %i", int(mOpponnentPokemon->GetPokemonLife()), int(mOpponnentPokemon->GetPokemonMaxLife())), 800, 250, 50, RED);

		DrawText(TextFormat("%s", mPlayerPokemon->GetPokemonName().c_str()), 500, 500, 60, BLACK);
		DrawText(TextFormat("%i / %i", int(mPlayerPokemon->GetPokemonLife()), int(mPlayerPokemon->GetPokemonMaxLife())), 500, 600, 50, RED);		
	}

	if (positionInCode == 5)
	{
		firstLine = TextFormat("GO ! %s !", mPlayerPokemon->GetPokemonName().c_str());
	}

	if (positionInCode == 15)
	{
		const Ability& newAbility = mPlayerPokemon->GetAbilities()[mPlayerPokemon->GetAbilities().size() - 1];
		firstLine = TextFormat("%s has now learned", mPlayerPokemon->GetPokemonName().c_str());
		DrawText(TextFormat("%s", newAbility.GetName().c_str()), 70, 900, 90, RED);
		return;
	}
}


Pokemon Battle::ChooseOpponentPokemon()
{
	Pokemon* mOpponnentPokemon = nullptr;

	battleIsFinished = false;
	opponentPokemonIsDead = false;
	pokemonCanUseAbility = false;
	pokemonIsLevelingUp = false;
	canLearnNewAbility = true;

	positionInCode = 0;

	firstLine = mOpponentTrainer->ChallengeTrainer();
	mMaxAbilityCost = 30;

	vector<Pokemon>& pokemonTeam = mOpponentTrainer->GetPokemonTeam();

	srand(time(NULL));
	int randomPokemon = rand() % pokemonTeam.size();
	mOpponnentPokemon = &pokemonTeam[randomPokemon];

	opponentPokemonImage = *(mOpponnentPokemon->GetPokemonImage());

	secondLine = mOpponentTrainer->Introduction();

	positionInCode = 1;
	toChangeLine = TextFormat("He is using %s to attack you", mOpponnentPokemon->GetPokemonName().c_str());

	return *mOpponnentPokemon;
}


void Battle::BattleAgainstTrainer(Pokemon& opponentPokemon)
{
	mOpponnentPokemon = &opponentPokemon;

	if (positionInCode == 3)
	{
		firstLine = "";
		secondLine = "";
		mThePlayer->ChoosePokemonToUse();
	}

	if (positionInCode == 4)
	{
		mPlayerPokemon = &mThePlayer->SendOrChangePokemon();
		playerPokemonImage = *(mPlayerPokemon->GetPokemonImage());
		positionInCode = 5;
	}
	
	if (positionInCode == 6)
	{
		if(mOpponnentPokemon->GetPokemonLife() > 0 && mPlayerPokemon->GetPokemonLife() > 0)
		{
			if (mPlayerPokemon->CheckIfCanUseAbility())
			{
				firstLine = "";
				secondLine = "";

				pokemonCanUseAbility = true;
			}
			else
			{
				pokemonCanUseAbility = false;

				firstLine = "Your pokemon can't use any more skill, ";
				secondLine = "Please change it.";
			}
		}
	}

 	if (positionInCode == 7 && !pokemonCanUseAbility)
	{
		positionInCode = 3;
		return BattleAgainstTrainer(*mOpponnentPokemon);
	}
	else if (positionInCode == 7 && pokemonCanUseAbility)
	{
		mPlayerPokemon->AttackOtherPokemon(*mOpponnentPokemon);

		positionInCode = 8;
	}

	if (positionInCode == 8) 
	{
		firstLine = TextFormat("You did %i damage to %s", (int) mOpponnentPokemon->GetPokemonDamage(), mOpponnentPokemon->GetPokemonName().c_str());
		pokemonCanUseAbility = false;
	}

	if (positionInCode == 9 && mOpponnentPokemon->GetPokemonLife() <= 0)
	{
		opponentPokemonIsDead = true;
		firstLine = "YOU HAVE WON THE FIGHT !!";
	}
	else if (positionInCode == 9 && mOpponnentPokemon->GetPokemonLife() > 0)
	{
		srand(time(NULL));
		const vector<Ability>& abilities = mOpponnentPokemon->GetAbilities();
		int randomAbility = rand() % abilities.size();
		mOpponentPokemonAbility = abilities[randomAbility];

		mPlayerPokemon->TakeDamage(mOpponentPokemonAbility.GetDamage(), mOpponentPokemonAbility);
		positionInCode = 10;
	}

	if (positionInCode == 10 && !opponentPokemonIsDead)
	{
		firstLine = TextFormat("%s used %s", mOpponnentPokemon->GetPokemonName().c_str(), mOpponentPokemonAbility.GetName().c_str());
		secondLine = TextFormat("it did %i damage to you", ( int )mPlayerPokemon->GetPokemonDamage());
	}

	if (positionInCode == 11 && !opponentPokemonIsDead)
	{
		if (mThePlayer->CheckIfTeamDead())
		{
			firstLine = "All your pokemons are dead";
			secondLine = "You have lost the fight";

			positionInCode = 12;
		}
		else
		{
			firstLine = "Your pokemon just died.";
			secondLine = "Please change it";

			positionInCode = 6;
			return BattleAgainstTrainer(*mOpponnentPokemon);
		}
	}

	if (opponentPokemonIsDead && positionInCode == 10)
	{
		if (mThePlayer->WinFight())
		{
			firstLine = "You won 100 gold";

			string* temp = new string(TextFormat("you now have %i gold", mThePlayer->GetMoney()));
			secondLine = temp->c_str();
			positionInCode = 11;
		}
		else
		{
			firstLine = "You won 2 new Pokeballs";

			string* temp = new string(TextFormat("you now have %i Pokeballs", mThePlayer->GetPokeballs()));
			secondLine = temp->c_str();
			positionInCode = 11;
		}

		for (int i = 0; i < mThePlayer->GetPokemonTeam().size(); i++)
		{
			mThePlayer->GetPokemonTeam()[i].Rest();
		}
	}

	if (positionInCode == 12 && opponentPokemonIsDead)
	{
		if (mPlayerPokemon->GetAbilities().size() >= 4)
		{
			canLearnNewAbility = false;
			battleIsFinished = true;
			return;
		}

		firstLine = "Your Pokemon is leveling up !!!";
		secondLine = "You can now learn a new ability";
	}

	if (positionInCode >= 13) 
	{
		for (int i = 0; i < mThePlayer->GetPokemonTeam().size(); i++)
		{
			mThePlayer->GetPokemonTeam()[i].Rest();
		}
	}


	if (positionInCode == 13 && !opponentPokemonIsDead)
	{
		firstLine = "You just lost 70 gold,";

		string* temp = new string(TextFormat("you now have %i gold", mThePlayer->GetMoney()));
		secondLine = temp->c_str();
	}
	else if (positionInCode == 13 && opponentPokemonIsDead && canLearnNewAbility)
	{
		firstLine = "";
		secondLine = "";

		pokemonIsLevelingUp = true;

		mPlayerPokemon->ChooseAbility();
	}
	else if(positionInCode == 13)
	{
		firstLine = "";
		secondLine = "";
		battleIsFinished = true;
		return;
	}


	if (positionInCode == 14 && !opponentPokemonIsDead)
	{
		firstLine = "";
		secondLine = "";
		battleIsFinished = true;
		return;
	}

	if (positionInCode == 14 && opponentPokemonIsDead)
	{
		mPlayerPokemon->LearnNewAbilities();
		pokemonIsLevelingUp = false;
		positionInCode = 15;
	}

	if (positionInCode == 16)
	{
		firstLine = "";
		secondLine = "";
		battleIsFinished = true;
		return;
	}

	return; 
}

bool Battle::EndOfBattle()
{
	return battleIsFinished;
}



//AGAINST POKEMON
void Battle::BattleCaptureUpdate()
{
	mThePlayer->UpdateTrainer();
	mPlayerPokemon->UpdatePokemon();

	if (positionInCode == 2 && IsKeyReleased(KEY_SPACE))
	{
		firstLine = toChangeLine;
		secondLine = "";
		imageIsLoad = false;
	}

	if (positionInCode == 3)
	{
		firstLine = "";
		if (!imageIsUnload)
		{
			UnloadTexture(opponentPokemonTexture);
			imageIsUnload = true;
		}
	}

	if (IsKeyPressed(KEY_SPACE) && positionInCode != 3 && positionInCode != 4 && positionInCode != 6 &&
		!pokemonCanUseAbility && !pokemonIsLevelingUp)
	{
		positionInCode++;
	}

	if (mThePlayer->GetAnswerTrainer() > 0 && positionInCode == 3)
	{
		positionInCode = 4;
	}

	if (positionInCode == 6)
	{
		UpdateChooseIfCapture();

		if (isCapturing != -1)
		{
			positionInCode = 7;
		}
	}

	if (positionInCode == 7)
	{
		if (mPlayerPokemon->GetAnswerPokemon() > 0)
		{
			positionInCode = 8;
		}
	}

	if (positionInCode == 12 && mPlayerPokemon->GetAnswerPokemon() > 0 && !isCapturing)
	{
		positionInCode = 13;
	}
}


void Battle::BattleCaptureDraw()
{
	mThePlayer->DrawTrainer();
	mPlayerPokemon->DrawPokemon();

	DrawText(firstLine, 70, 775, 70, BLACK);
	DrawText(secondLine, 70, 870, 70, BLACK);
	DrawText(thirdLine, 70, 1050, 70, BLACK);

	if (!imageIsLoad)
	{
		ImageFormat(&opponentPokemonImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
		ImageFormat(&playerPokemonImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

		opponentPokemonTexture = LoadTextureFromImage(opponentPokemonImage);
		playerPokemonTexture = LoadTextureFromImage(playerPokemonImage);

		imageIsLoad = true;
	}

	if (positionInCode == 2)
	{
		DrawTexture(opponentPokemonTexture, 1080, 30, WHITE);
	}

	if (positionInCode == 4)
	{
		imageIsLoad = false;
	}

	if (positionInCode >= 5 && (positionInCode != 12 || !opponentPokemonIsDead))
	{
		DrawTexture(opponentPokemonTexture, 1080, 30, WHITE);
		DrawTexture(playerPokemonTexture, 50, 200, WHITE);

		DrawText(TextFormat("%s", mOpponnentPokemon->GetPokemonName().c_str()), 700, 150, 60, BLACK);
		DrawText(TextFormat("%i / %i", int(mOpponnentPokemon->GetPokemonLife()), int(mOpponnentPokemon->GetPokemonMaxLife())), 800, 250, 50, RED);

		DrawText(TextFormat("%s", mPlayerPokemon->GetPokemonName().c_str()), 500, 500, 60, BLACK);
		DrawText(TextFormat("%i / %i", int(mPlayerPokemon->GetPokemonLife()), int(mPlayerPokemon->GetPokemonMaxLife())), 500, 600, 50, RED);
	}

	if (positionInCode == 5)
	{
		firstLine = TextFormat("GO ! %s !", mPlayerPokemon->GetPokemonName().c_str());
	}

	if (positionInCode == 6)
	{
		DrawChooseIfCapture();
	}

	if (positionInCode == 14 && opponentPokemonIsDead && !isCapturing)
	{
		const Ability& newAbility = mPlayerPokemon->GetAbilities()[mPlayerPokemon->GetAbilities().size() - 1];
		firstLine = TextFormat("%s has now learned", mPlayerPokemon->GetPokemonName().c_str());
		DrawText(TextFormat("%s", newAbility.GetName().c_str()), 70, 900, 90, RED);
		return;
	}
}

void Battle::DrawChooseIfCapture()
{
	firstLine = "Do you wish to try to :";
	secondLine = TextFormat("1. Capture %s ", mOpponnentPokemon->GetPokemonName().c_str());
	DrawText(TextFormat("2. Attack %s", mOpponnentPokemon->GetPokemonName().c_str()), 70, 970, 70, BLACK);
	DrawText("Write the corresponding number :", 70, 1070, 40, RED);

	DrawRectangleRec(captureAnswerBox, LIGHTGRAY);

	if (isdigit(captureBoxInput))
	{
		string printAnswer { (char) captureBoxInput };
		DrawText(TextFormat("%s", printAnswer.c_str()), 800, 1065, 70, BLACK);

		answerCapture = stoi(printAnswer);
	}
	else
	{
		DrawText("_", 800, 1065, 70, BLACK);
	}
}

void Battle::UpdateChooseIfCapture()
{
	if (GetKeyPressed())
	{
		captureBoxInput = GetCharPressed();
	}

	if (IsKeyPressed(KEY_ENTER) && answerCapture > 0 && answerCapture <= 2)
	{
		if (answerCapture == 1)
		{
			isCapturing = true;
		}
		else if (answerCapture == 2)
		{
			isCapturing = false;
		}
	}
}


Pokemon Battle::ChoosePokemonToCapture()
{
	Pokemon* mOpponnentPokemon = nullptr;

	mMaxAbilityCost = 30;

	battleIsFinished = false;
	opponentPokemonIsDead = false;
	pokemonCanUseAbility = false;
	pokemonIsLevelingUp = false;
	canLearnNewAbility = true;

	positionInCode = 0;
	firstLine = "You stumble in a battle !";


	srand(time(NULL));
	int randomPokemon = rand() % allPokemons.size();
	mOpponnentPokemon = &allPokemons[randomPokemon];

	//*************************************************************TO ERASE******************************************************
	//mOpponnentPokemon = &allPokemons[9];

	opponentPokemonImage = *(mOpponnentPokemon->GetPokemonImage());

	positionInCode = 1;
	toChangeLine = TextFormat("You have encounter a wild %s", mOpponnentPokemon->GetPokemonName().c_str());

	return *mOpponnentPokemon;
}

void Battle::BattleAgainstPokemon(Pokemon& opponentPokemon)
{
	//********************************************************************************************************************
	cout << positionInCode << endl;

	mOpponnentPokemon = &opponentPokemon;

	if (positionInCode == 3)
	{
		firstLine = "";
		secondLine = "";
		mThePlayer->ChoosePokemonToUse();
	}

	if (positionInCode == 4)
	{
		mPlayerPokemon = &mThePlayer->SendOrChangePokemon();
		playerPokemonImage = *(mPlayerPokemon->GetPokemonImage());
		positionInCode = 5;
	}

	if (positionInCode >= 7 && !isCapturing)
	{
		AttackPokemon();
	}

	if (positionInCode >= 7 && isCapturing)
	{
		CapturePokemon();
	}

	//return;
}

void Battle::AttackPokemon()
{
	if (positionInCode == 7)
	{
		if (mOpponnentPokemon->GetPokemonLife() > 0 && mPlayerPokemon->GetPokemonLife() > 0)
		{
			if (mPlayerPokemon->CheckIfCanUseAbility())
			{
				firstLine = "";
				secondLine = "";

				pokemonCanUseAbility = true;
			}
			else
			{
				pokemonCanUseAbility = false;

				firstLine = "Your pokemon can't use any more skill, ";
				secondLine = "Please change it.";
			}
		}
	}

	if (positionInCode == 8 && !pokemonCanUseAbility)
	{
		positionInCode = 3;
		captureBoxInput = NULL;
		answerCapture = NULL;
		isCapturing = -1;

		return BattleAgainstPokemon(*mOpponnentPokemon);
	}
	else if (positionInCode == 8 && pokemonCanUseAbility)
	{
		mPlayerPokemon->AttackOtherPokemon(*mOpponnentPokemon);

		positionInCode = 9;
	}

	if (positionInCode == 9)
	{
		firstLine = TextFormat("You did %i damage to %s", (int) mOpponnentPokemon->GetPokemonDamage(), mOpponnentPokemon->GetPokemonName().c_str());
		pokemonCanUseAbility = false;
	}

	if (positionInCode == 10 && mOpponnentPokemon->GetPokemonLife() <= 0)
	{
		opponentPokemonIsDead = true;
		firstLine = "YOU HAVE WON THE FIGHT !!";
	}
	else if (positionInCode == 10 && mOpponnentPokemon->GetPokemonLife() > 0)
	{
		srand(time(NULL));
		const vector<Ability>& abilities = mOpponnentPokemon->GetAbilities();
		int randomAbility = rand() % abilities.size();
		mOpponentPokemonAbility = abilities[randomAbility];

		mPlayerPokemon->TakeDamage(mOpponentPokemonAbility.GetDamage(), mOpponentPokemonAbility);
		positionInCode = 11;
	}

	if (positionInCode == 11 && !opponentPokemonIsDead)
	{
		firstLine = TextFormat("%s used %s", mOpponnentPokemon->GetPokemonName().c_str(), mOpponentPokemonAbility.GetName().c_str());
		secondLine = TextFormat("it did %i damage to you", (int) mPlayerPokemon->GetPokemonDamage());
	}

	if (positionInCode == 11 && opponentPokemonIsDead)
	{
		if (mPlayerPokemon->GetAbilities().size() >= 4)
		{
			canLearnNewAbility = false;
			battleIsFinished = true;
			return;
		}

		firstLine = "Your Pokemon is leveling up !!!";
		secondLine = "You can now learn a new ability";
	}

	if (positionInCode == 12 && !opponentPokemonIsDead)
	{
		if (mThePlayer->CheckIfTeamDead())
		{
			positionInCode = 14;
		}
		else
		{
			if (mPlayerPokemon->GetPokemonLife() > 0)
			{
				positionInCode = 7;
			}
			else
			{
				firstLine = "Your pokemon just died.";
				secondLine = "Please change it";
			}
		}
	}

	if (positionInCode == 12 && opponentPokemonIsDead)
	{
		for (int i = 0; i < mThePlayer->GetPokemonTeam().size(); i++)
		{
			mThePlayer->GetPokemonTeam()[i].Rest();
		}
	}
	
	if (positionInCode == 12 && opponentPokemonIsDead && canLearnNewAbility)
	{
		firstLine = "";
		secondLine = "";
		pokemonIsLevelingUp = true;

		mPlayerPokemon->ChooseAbility();
	}
	else if (positionInCode == 12 && opponentPokemonIsDead)
	{
		firstLine = "";
		secondLine = "";
		battleIsFinished = true;
		return;
	}

	if (positionInCode == 13 && !opponentPokemonIsDead)
	{
		positionInCode = 3;
		pokemonCanUseAbility = false;
		captureBoxInput = NULL;
		answerCapture = NULL;
		isCapturing = -1;

		return BattleAgainstPokemon(*mOpponnentPokemon);
	}

	if (positionInCode == 13 && opponentPokemonIsDead)
	{
		mPlayerPokemon->LearnNewAbilities();
		pokemonIsLevelingUp = false;
		positionInCode = 14;
	}

	if (positionInCode == 14 && !opponentPokemonIsDead)
	{
		firstLine = "All your pokemons are dead";
		secondLine = "You have lost the fight !";

		for (int i = 0; i < mThePlayer->GetPokemonTeam().size(); i++)
		{
			mThePlayer->GetPokemonTeam()[i].Rest();
		}
	}

	if (positionInCode == 15)
	{
		firstLine = "";
		secondLine = "";
		battleIsFinished = true;
		return;
	}

	return;
}

void Battle::CapturePokemon()
{
	if (positionInCode == 7)
	{
 		if (mThePlayer->GetPokeballs() > 0 && mThePlayer->GetPokemonTeam().size() < 6)
		{
			firstLine = TextFormat("You are trying to capture %s", mOpponnentPokemon->GetPokemonName().c_str());
			secondLine = "";
			canCapture = true;
		}
		else if (mThePlayer->GetPokemonTeam().size() >= 6)
		{
			firstLine = "Your team is already full.";
			secondLine = "You can't capture any more pokemon";
			canCapture = false;
		}
		else if (mThePlayer->GetPokeballs() <= 0)
		{
			firstLine = "You don't have enough Pokeballs.";
			secondLine = "Go win against a Trainer to have more.";
			canCapture = false;
		}
	}

	if (positionInCode == 8 && !canCapture)
	{
		positionInCode = 6;
		pokemonCanUseAbility = false;
		captureBoxInput = NULL;
		answerCapture = NULL;
		isCapturing = -1;

		return BattleAgainstPokemon(*mOpponnentPokemon);
	}

	if (positionInCode == 8 && canCapture)
	{
		if (mThePlayer->IsPokemonCaptured(*mOpponnentPokemon))
		{
			cout << mPlayerPokemon->GetPokemonName() << endl;
			//mPlayerPokemon = 
			firstLine = TextFormat("You have managed to capture %s !!!", mOpponnentPokemon->GetPokemonName().c_str());
			secondLine = TextFormat("%s is now part of your team !", mOpponnentPokemon->GetPokemonName().c_str());

			hasManagedToCapture = true;
		}
		else
		{
			firstLine = TextFormat("You have failed to capture %s...", mOpponnentPokemon->GetPokemonName().c_str());
			secondLine = "Damage it to be able to capture it !";
			hasManagedToCapture = false;
		}
	}

	if (positionInCode == 9 && hasManagedToCapture)
	{
		firstLine = "";
		secondLine = "";
		battleIsFinished = true;
		return;
	}

	else if (positionInCode == 9 && !hasManagedToCapture)
	{
		srand(time(NULL));
		const vector<Ability>& abilities = mOpponnentPokemon->GetAbilities();
		int randomAbility = rand() % abilities.size();
		mOpponentPokemonAbility = abilities[randomAbility];

		mPlayerPokemon->TakeDamage(mOpponentPokemonAbility.GetDamage(), mOpponentPokemonAbility);
		positionInCode = 10;
	}

	if (positionInCode == 10)
	{
		firstLine = TextFormat("%s used %s", mOpponnentPokemon->GetPokemonName().c_str(), mOpponentPokemonAbility.GetName().c_str());
		secondLine = TextFormat("it did %i damage to you", (int) mPlayerPokemon->GetPokemonDamage());
	}

	if (positionInCode == 11)
	{
		if (mThePlayer->CheckIfTeamDead())
		{
			positionInCode = 13;
		}
		else
		{
			if (mPlayerPokemon->GetPokemonLife() > 0)
			{
				positionInCode = 6;
				pokemonCanUseAbility = false;
				captureBoxInput = NULL;
				answerCapture = NULL;
				isCapturing = -1;

				return BattleAgainstPokemon(*mOpponnentPokemon);
			}
			else
			{
				firstLine = "Your pokemon just died.";
				secondLine = "Please change it";
			}
		}
	}

	if (positionInCode == 12)
	{
		positionInCode = 3;
		pokemonCanUseAbility = false;
		captureBoxInput = NULL;
		answerCapture = NULL;
		isCapturing = -1;

		return BattleAgainstPokemon(*mOpponnentPokemon);
	}

	if (positionInCode == 13)
	{
		firstLine = "All your pokemons are dead";
		secondLine = "You have lost the fight !";

		for (int i = 0; i < mThePlayer->GetPokemonTeam().size(); i++)
		{
			mThePlayer->GetPokemonTeam()[i].Rest();
		}
	}

	if (positionInCode == 14)
	{
		firstLine = "";
		secondLine = "";
		battleIsFinished = true;
		return;
	}
}
