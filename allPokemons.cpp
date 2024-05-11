#include "allPokemons.h"

Pokemon AllPokemons::Snorlax;
Pokemon AllPokemons::Darumaka;
Pokemon AllPokemons::Magikarp;
Pokemon AllPokemons::Pansage;
Pokemon AllPokemons::Minun;
Pokemon AllPokemons::Plusle;
Pokemon AllPokemons::Vanillite;
Pokemon AllPokemons::Pancham;
Pokemon AllPokemons::Gulpin;
Pokemon AllPokemons::Diglett;
Pokemon AllPokemons::Tornadus;
Pokemon AllPokemons::Mewtwo;
Pokemon AllPokemons::Caterpie;
Pokemon AllPokemons::Sudowoodo;
Pokemon AllPokemons::Spectrier;
Pokemon AllPokemons::Dragonair;
Pokemon AllPokemons::Absol;
Pokemon AllPokemons::Copperajah;
Pokemon AllPokemons::Cleffa;

vector<Pokemon> AllPokemons::allPokemons {};

void AllPokemons::Load()
{
	Snorlax = Pokemon( LoadTexture( "resources/Ronflex.png" ), "Snorlax", 
		" is only capable of sleeping", "Normal", PokeType::Normal, 169, {BodySlam});
	Darumaka = Pokemon( LoadTexture( "resources/Darumaka.png" ), "Darumaka", 
		" is a symbol of Goodluck", "Fire", PokeType::Fire, 70, { FireSpin } );
	Magikarp = Pokemon( LoadTexture( "resources/Magikarp.png" ), "Magikarp", 
		" is only capable of flopping around", "Water", PokeType::Water, 20, { WaterShuriken } );
	Pansage = Pokemon( LoadTexture( "resources/Pansage.png" ), "Pansage",
		" is a Pokemon that dwells deep in the forest", "Grass", PokeType::Grass, 60, { GigaDrain } );
	Minun = Pokemon( LoadTexture( "resources/Minun.png" ), "Minun",
		" promotes blood circulation and relieves muscular tension.", "Electric", PokeType::Electric, 60, { Thunder } );
	Plusle = Pokemon( LoadTexture( "resources/Plusle.png" ), "Plusle",
		" promotes blood circulation and relieves muscular tension.", "Electric", PokeType::Electric, 60, { Thunder } );
	Vanillite = Pokemon( LoadTexture( "resources/Vanillite.png" ), "Vanillite",
		" looks like an Ice cream", "Ice", PokeType::Ice, 36, { IcyWind } );
	Pancham = Pokemon( LoadTexture( "resources/Pancham.png" ), "Pancham",
		" does its best to be taken seriously by its enemies, but its glare is not sufficiently intimidating.", "Fighting", PokeType::Fighting, 67, { RollingKick } ); //Just RollingKick
	Gulpin = Pokemon( LoadTexture( "resources/Gulpin.png" ), "Gulpin",
		" has a stomach that comprises most of its body", "Poison", PokeType::Poison, 70, { Acid } );
	Diglett = Pokemon( LoadTexture( "resources/Diglett.png" ), "Diglett",
		" spends most of its time underground", "Ground", PokeType::Ground, 38, { Dig } );
	Tornadus = Pokemon( LoadTexture( "resources/Tornadus.png" ), "Tornadus",
		" considering every direction it flies, it will always stir up tremendous storms as it goes.", "Flying", PokeType::Flying, 80, { Aeroblast } );
	Mewtwo = Pokemon( LoadTexture( "resources/Mewtwo.png" ), "Mewtwo",
		" said that circumstances of one's birth is irrelevent", "Psychic", PokeType::Psychic, 106, { Confusion } );
	Caterpie = Pokemon( LoadTexture( "resources/Caterpie.png" ), "Caterpie",
		" it may change into a Butterfree, but the Heart that beats inside remains the same.", "Bug", PokeType::Bug, 45, { UTurn } );
	Sudowoodo = Pokemon( LoadTexture( "resources/Sudowoodo.png" ), "Sudowoodo",
		" is a tree", "Rock", PokeType::Rock, 70, { Accelerock } );
	Spectrier = Pokemon( LoadTexture( "resources/Spectrier.png" ), "Spectrier",
		" kicks are said to separate soul from body.", "Ghost", PokeType::Ghost, 100, { MenacingMoonrazeMaelstrom } );
	Dragonair = Pokemon( LoadTexture( "resources/Dragonair.png" ), "Dragonair",
		" is a mystical Pokemon that exudes a gentle aura", "Dragon", PokeType::Dragon, 61, { RoarOfTime } );
	Absol = Pokemon( LoadTexture( "resources/Absol.png" ), "Absol",
		" senses coming disasters", "Dark", PokeType::Dark, 65, { Pursuit } );
	Copperajah = Pokemon( LoadTexture( "resources/Copperajah.png" ), "Copperajah",
		" could level mountains and change the landscape.", "Steel", PokeType::Steel, 122, { MetalClaw } );
	Cleffa = Pokemon( LoadTexture( "resources/Cleffa.png" ), "Cleffa",
		" is said to arrive riding on a shooting star", "Fairy", PokeType::Fairy, 50, { LetsSnuggleForever } );

	allPokemons = { Snorlax, Darumaka, Magikarp, Pansage, Minun, Plusle, Vanillite, Pancham,
		Gulpin, Diglett, Tornadus, Mewtwo, Caterpie, Sudowoodo, Spectrier, Dragonair, Absol, Copperajah, Cleffa };
}
