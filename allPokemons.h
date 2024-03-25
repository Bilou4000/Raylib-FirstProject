#pragma once

#include "Pokemon.h"
#include "allAbilities.h"

#include <iostream>
#include <vector>
using namespace std;

static Pokemon Snorlax = Pokemon(LoadImage("resources/Ronflex.png"), "Snorlax", 
	" is only capable of sleeping", PokeType::Normal, 169, { BodySlam });
static Pokemon Darumaka = Pokemon(LoadImage("resources/Darumaka.png"), "Darumaka",
	" is a symbol of Goodluck", PokeType::Fire, 70, { FireSpin });
static Pokemon Magikarp = Pokemon(LoadImage("resources/Magikarp.png"), "Magikarp",
	" is only capable of flopping around", PokeType::Water, 20, { WaterShuriken });
static Pokemon Pansage = Pokemon(LoadImage("resources/Pansage.png"), "Pansage",
	" is a Pokemon that dwells deep in the forest", PokeType::Grass, 60, { GigaDrain });
static Pokemon Minun = Pokemon(LoadImage("resources/Minun.png"), "Minun",
	" promotes blood circulation and relieves muscular tension.", PokeType::Electric, 60, { Thunder });
static Pokemon Plusle = Pokemon(LoadImage("resources/Plusle.png"), "Plusle",
	" promotes blood circulation and relieves muscular tension.", PokeType::Electric, 60, { Thunder });
static Pokemon Vanillite = Pokemon(LoadImage("resources/Vanillite.png"), "Vanillite",
	" looks like an Ice cream", PokeType::Ice, 36, { IcyWind });
static Pokemon Pancham = Pokemon(LoadImage("resources/Pancham.png"), "Pancham",
	" does its best to be taken seriously by its enemies, but its glare is not sufficiently intimidating.", PokeType::Fighting, 67, { RollingKick });
static Pokemon Gulpin = Pokemon(LoadImage("resources/Gulpin.png"), "Gulpin",
	" has a stomach that comprises most of its body", PokeType::Poison, 70, { Acid });
static Pokemon Diglett = Pokemon(LoadImage("resources/Diglett.png"), "Diglett",
	" spends most of its time underground", PokeType::Ground, 38, { Dig });
static Pokemon Tornadus = Pokemon(LoadImage("resources/Tornadus.png"), "Tornadus",
	" considering every direction it flies, it will always stir up tremendous storms as it goes.", PokeType::Flying, 80, { Aeroblast });
static Pokemon Mewtwo = Pokemon(LoadImage("resources/Mewtwo.png"), "Mewtwo",
	" said that circumstances of one's birth is irrelevent", PokeType::Psychic, 106, { Confusion });
static Pokemon Caterpie = Pokemon(LoadImage("resources/Caterpie.png"), "Caterpie",
	" it may change into a Butterfree, but the Heart that beats inside remains the same.", PokeType::Bug, 45, { UTurn });
static Pokemon Sudowoodo = Pokemon(LoadImage("resources/Sudowoodo.png"), "Sudowoodo",
	" is a tree", PokeType::Rock, 70, { Accelerock });
static Pokemon Spectrier = Pokemon(LoadImage("resources/Spectrier.png"), "Spectrier",
	" kicks are said to separate soul from body.", PokeType::Ghost, 100, { MenacingMoonrazeMaelstrom });
static Pokemon Dragonair = Pokemon(LoadImage("resources/Dragonair.png"), "Dragonair",
	" is a mystical Pokemon that exudes a gentle aura", PokeType::Dragon, 61, { RoarOfTime });
static Pokemon Absol = Pokemon(LoadImage("resources/Absol.png"), "Absol",
	" senses coming disasters", PokeType::Dark, 65, { Pursuit });
static Pokemon Copperajah = Pokemon(LoadImage("resources/Copperajah.png"), "Copperajah",
	" could level mountains and change the landscape.", PokeType::Steel, 122, { MetalClaw });
static Pokemon Cleffa = Pokemon(LoadImage("resources/Cleffa.png"), "Cleffa",
	" is said to arrive riding on a shooting star", PokeType::Fairy, 50, { LetsSnuggleForever });

static vector<Pokemon> allPokemons = { Snorlax, Darumaka, Magikarp, Pansage, Minun, Plusle, Vanillite, Pancham,
Gulpin, Diglett, Tornadus, Mewtwo, Caterpie, Sudowoodo, Spectrier, Dragonair, Absol, Copperajah, Cleffa };
