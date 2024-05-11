#include "allTrainers.h"

Trainer allTrainer::Marie;
Trainer allTrainer::Sylvain;
Trainer allTrainer::Fred;
Trainer allTrainer::Henri;
Trainer allTrainer::Thomas;
Trainer allTrainer::Nicolas;
Trainer allTrainer::Gaetan;
Trainer allTrainer::Franck;
Trainer allTrainer::Marc;
Trainer allTrainer::Kevin;
Trainer allTrainer::Florence;
Trainer allTrainer::Mathieu;
Trainer allTrainer::Felix;
Trainer allTrainer::Anthony;
Trainer allTrainer::Dominique;
Trainer allTrainer::Julien;
Trainer allTrainer::Benoit;
Trainer allTrainer::Carole;
Trainer allTrainer::Colette;

vector<Trainer> allTrainer::mAllTrainers {};

void allTrainer::Init()
{
	Marie = Trainer("Marie", "LEGRAND", "You shall code more !!", std::vector<Pokemon> { AllPokemons::Dragonair });
	Sylvain = Trainer("Sylvain", "BLANCHOT", "Make your USP * shine *", std::vector<Pokemon> { AllPokemons::Pansage });
	Fred = Trainer("Fred", "AUDOUARD", "I hope you burn in hell !", std::vector<Pokemon> { AllPokemons::Plusle });
	Henri = Trainer("Henri", "BESSOU", "I'll be nice !", std::vector<Pokemon> { AllPokemons::Minun });
	Thomas = Trainer("Thomas", "VINADELLE", "Check the Viewport Workflow.", std::vector<Pokemon> { AllPokemons::Tornadus });
	Nicolas = Trainer("Nicolas", "COUNIL", "Happy Birthday !!", std::vector<Pokemon> { AllPokemons::Gulpin });
	Gaetan = Trainer("Gaëtan", "BLAISE-CAZALET", "MORE COOODE", std::vector<Pokemon> { AllPokemons::Copperajah });
	Franck = Trainer("Franck", "BASSET", "I'm in a hurry", std::vector<Pokemon> { AllPokemons::Darumaka });
	Marc = Trainer("Marc", "LAMBERT", "Draw everyday !", std::vector<Pokemon> { AllPokemons::Vanillite });
	Kevin = Trainer("Kevin", "LIEBER", "Let's have fun !", std::vector<Pokemon> { AllPokemons::Sudowoodo });
	Florence = Trainer("Florence", "GUY", "Don't be late.", std::vector<Pokemon> { AllPokemons::Spectrier });
	Mathieu = Trainer("Mathieu", "SANCHO", "More anatomy.", std::vector<Pokemon> { AllPokemons::Pancham });
	Felix = Trainer("Felix", "MAZARD", "Travel and discover !", std::vector<Pokemon> { AllPokemons::Magikarp });
	Anthony = Trainer("Anthony", "FRISTOT", "NO TRIANGLE !!!", std::vector<Pokemon> { AllPokemons::Snorlax });
	Dominique = Trainer("Dominique", "PEYRONNET", "Concept art has no future.", std::vector<Pokemon> { AllPokemons::Mewtwo });
	Julien = Trainer("Julien", "REVENU", "Just enjoy !", std::vector<Pokemon> { AllPokemons::Cleffa });
	Benoit = Trainer("Benoit", "COSSE", "Have fun sculpting.", std::vector<Pokemon> { AllPokemons::Diglett });
	Carole = Trainer("Carole", "MACCOTTA", "PRO-NUN-CIA-TION", std::vector<Pokemon> { AllPokemons::Caterpie });
	Colette = Trainer("Colette", "TRAINOR", "I'll kick you out", std::vector<Pokemon> { AllPokemons::Absol });

	mAllTrainers = { Marie, Sylvain, Fred, Henri, Thomas, Nicolas, Gaetan, Franck, Marc, Kevin,
		Florence, Mathieu, Felix, Anthony, Dominique, Julien, Benoit, Carole, Colette };
}
