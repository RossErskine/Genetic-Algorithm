#include "Population.h"
#include "ConVar.h"

#include <time.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>


namespace Population
{
	
	// =================================== helper functions ========================================= //

	/* =========================== randint =========================================//
	*   "random number engine  is a function that generates uniformly distributed
	*	sequence of integer values."
	*	"Distribution is a function that generates a sequence of values according 
	*	to a mathematical formaula given a sequence of value from an engine."
	*	Stroustrup (2014: p914)
	*///===========================================================================//
	double randDouble(double min, double max)// generates random number
	{
		static std::default_random_engine ran;
		return std::uniform_real_distribution<>{min, max}(ran);
	}
	int randint(int min, int max)// generates random number
	{
		static std::default_random_engine ran;
		return std::uniform_int_distribution<>{min, max}(ran);
	}

	/*===================== generatePopulation =====================================//
	*	creates chromosome useing char characters to desired size, decode_int works 
	*	the value the chromosome number represents, then generates fitness from that value. 
	*	after the whole population is completed the fitness ratio is worked out against the 
	*	sum of all fitness
	*///============================================================================//
	void generatePopulation(std::vector<Person>& population, const int& n)
	{
		
		ConVar::ConstVariables cv;
		char zero = '0', one = '1';			//chars to become chromosome
		std::string chromosome;
	
		bool has_zero_chromo = false;

		// == creates chromosomes == //
		for (int i = 0; i < n; ++i)				// outer loop generates population size
		{
			for (int j = 0; j < cv.getChromosomeSize(); ++j)	// inner loop generates chromosome
			{
				int chromo = randint(0, 1);
				switch (chromo)
				{
				case 0:
					chromosome += zero;
					has_zero_chromo = true;
					break;
				case 1:
					chromosome += one;
					break;
				default:
					throw "generatePopulation: not a chromosome!";
					break;
				}
			}
			
			// ===  create person add to population === // 
			//
			if (has_zero_chromo)		// stops chromosome having termination criteria
			{
				Person person = { chromosome };		// creates person adds new chromosome to it
				decode_int(person);
				generateFitness(person);
				population.push_back(person);		// adds person to population
				chromosome = "";		//reset chromosome
			}
			else
			{
				chromosome = "";		//reset chromosome
				--i;
			}
			has_zero_chromo = false;	// resets 
			
		}

		// == sets fitness ratio after population fills up as its an avg of whole poulation == //
		//
		for (int i = 0; i < population.size(); ++i)
		{
			double temp = fitness_ratio(population, population[i]);
			population[i].setFitnessRatio(temp);
		}
		
	}

	/*=========================== decoded_int ============================================//
	*	generates an int from the representation from chromosome i.e. 0101 = 5
	*///==================================================================================//
	void decode_int(Person& person)
	{
		ConVar::ConstVariables cv;
		double decoded_int = 0;
		double decoded = 0;
		double mean = cv.getPopulationSize() / cv.getTermination();
		double sum = 1;
		for (int i = cv.getChromosomeSize() -1; i >= 0; i--)
		{
			if (person.getChromosome()[i] == '1')
			{
				decoded_int += sum;
			}
			sum *= 2;
		}
		
		decoded = decoded_int * mean -3;
		
		person.setDecodedInt(decoded);
		
	}
	/* ================================generates fitness ==================== //
	*	generates fitness from decoded int 'x' based on formula f(x) = Tx - x2
	*	where 'T' is highest number possible so termination value is used
	*///==================================================================== //
	// == f(x) = Tx - x2	== //
	void generateFitness(Person& person)
	{
		ConVar::ConstVariables cv;
		double T = cv.getTermination();	
		double x = double(person.getDecodedInt());
		double fitness = T * x - x * x;
		
		person.setFitness(fitness);
	}

	/*======================== fitness_ratio =================================//
	* fitness ratio is worked out after population is filled based on formula 
	* fr = f / E(f) where f is personal fitness E(f) is the sum of all fitness
	*  and fr is ratio
	*///===================================================================== //
	double fitness_ratio(const std::vector<Person>& population, Person& person)
	{
		double sum_of_fitness = 0;
		double fitness_ratio = 0;

		for (Person p : population)	// computes sum of fitness
		{
			sum_of_fitness += p.getFitness();
		}
		sum_of_fitness /= 100;
		fitness_ratio =  person.getFitness()/sum_of_fitness ;
		return fitness_ratio;
	}

	/* ================== PopulationAvgFitness =================================//
	* works out average fitness on every generation used to compare geneations
	* on graph based on formula Pf = E(f) / Ps where P is population f is fitness 
	* E(f) is sum of all fitness P(s) is population size
	*/// ========================================================================//
	double populationAvgFitness(const std::vector<Person>& population)
	{
		double avgFitness = 0, sum_of_fitness = 0;;
		for (int i = 0; i < population.size(); ++i)
		{
			sum_of_fitness += population[i].getFitness();
		}
		avgFitness = sum_of_fitness / population.size();
		return avgFitness;
	}

	/*===================== print_population =================================== //
	* prints population on console mainly for testing and debugging 
	*/// ====================================================================== //
	void print_population(std::vector<Person>& population)
	{
		std::cout << '|' << std::setw(12) << "Chromosome"		//change w() when chromosomes increase
			<< '|' << std::setw(14) << "Decoded int" 
			<< '|' <<std::setw(10)<< "Fitness" 
			<< '|' <<std::setw(16)<< "Fitness ratio" << '|'
			<< "\n --------------------------------------------------------" << std::endl;
		for (Person p : population)
		{
			std::cout << '|' << std::setw(12) << p.getChromosome()		//change w() when chromosomes increase
				<< '|' << std::setw(14) << p.getDecodedInt()
				<< '|' << std::setw(10) <<std::fixed<< std::setprecision(0)<< p.getFitness()
				<< '|' << std::setw(16) << std::setprecision(4)<<p.getFitnessRatio() << '|' << std::endl;
		}
	}

	/* =========================== is_termination ============================= //
	*  looks for a chromosome in population equal to termination
	*  termination usually maximum chromosome can be
	*///======================================================================= //
	bool is_termination(const std::vector<Person>& population)
	{
		ConVar::ConstVariables cv;
		std::vector<Person> people = population;
		for (int i = 0; i < people.size(); ++i)
		{
			Person person = people[i];
			int DI = person.getDecodedInt();	//DI = decodedInt
			if (DI == cv.getTermination())return true;
		}
		return false;
	}

	/* ==================== highestFitness ==================================== //
	* returns highest fitness from a population from each generation 
	* for comparison of generations used in graphs 
	*/// ====================================================================== //
	double highestFitness(const std::vector<Person>& population)
	{
		double fitness = 0;
		for (int i = 0; i < population.size(); ++i)
		{
			if (population[i].getFitness() > fitness)
			{
				fitness = population[i].getFitness();
			}
		}
		return fitness;
	}

	// ============================= selection for mating ======================================= //
	//
	void swap(Person* a, Person* b)
	{
		Person temp = *a;
		*a = *b;
		*b = temp;
	}
	/* ==================== bubbleSort ==================================== //
	* sorts population based on fitness ratio 
	*/// ================================================================= //
	void bubbleSort(std::vector<Person>& population)
	{
		// =======  bubble sort algorithm	==========  //
		//
		for (int i = 0; i < population.size() - 1; ++i)
		{
			for (int j = 0; j < population.size() - i - 1; ++j)
			{
				
				// using overlaoding operator < of fitness ratio
				// see Person class operators
				if (population[j].getFitness() < population[j + 1].getFitness())
				{
					swap(&population[j], &population[j + 1]);
				}
			}
		}
	}
	/* ================= roulette_wheel ====================================== //
	* roulette wheel sorts the population by fitness ratio using bubblesort selects two 
	* random numbers for mum and dad from 1 to 100.
	* selection fitness ratio stacks proportional sections depending on size of ratio  
	* if the random numbers are in a persons section person is picked 
	*///====================================================================== //
	void roulette_wheel(std::vector<Person>& population, Person& mum, Person& dad)
	{
		bool mumPicked = false, dadPicked = false;
		while (mumPicked == false && dadPicked == false)
		{
			int selection_mum = 0;
			int selection_dad = 0;

			selection_mum = randint(0, 99);
			selection_dad = randint(0, 99);

			bubbleSort(population); // sort population

			// =============== picks mum and dad ================= //
			//

			double sumFitnessRatio = 0;
			for (int i = population.size() - 1; i >= 0; --i)	// loops backwards as vector sorted that way
			{
				sumFitnessRatio += population[i].getFitnessRatio();		// sums up ratio's gives each Person a slot in pie

				if (!mumPicked)											// to stop picking more than one of each
				{
					if (selection_mum < sumFitnessRatio)
					{
						mum = population[i];
						
						mumPicked = true;
						//population.erase(population.begin() + i); // erases mum from population
					}
				}

				if (!dadPicked)											// to stop picking more than one of each
				{
					if (selection_dad < sumFitnessRatio)
					{
						dad = population[i];
						
						dadPicked = true;
						//population.erase(population.begin() + i); // erases dad from population
					}
				}
			}
			
								
		}
		population.clear();// clears poulation ready to be repopulated
	}

	/* ====================== tournament =========================================== //
	* picks top 4 Persons based on fitness ratio puts them a semi finalist conatianer
	* then randomly selects two from that pot
	* mum and dad cannot be same
	*/// ========================================================================== //
	void tournament(std::vector<Person>& population, Person& mum, Person& dad)
	{
		bubbleSort(population);
		int selection_mum = 0;
		int selection_dad = 0;
		// so mum and dad are different
		while (selection_mum == selection_dad)
		{
			selection_mum = randint(0, 3);
			selection_dad = randint(0, 3);
		}
		
		std::vector<Person> semi_finalists;
		// == pick semi finalists == //
		for (int i = 0; i != 4; i++)
		{
			semi_finalists.push_back(population[i]);
		}
		mum = semi_finalists[selection_mum];
		dad = semi_finalists[selection_dad];

		population.clear();						// clears poulation ready to be repopulated
		
	}
	/* ======================== Rank selection ==================================== //
	*	ranks persons in order of fitness, then selection is random but, probability
	*	is equal
	*/// ========================================================================= //
	void rankSelection(std::vector<Person>& population, Person& mum, Person& dad)
	{
		bubbleSort(population);
		int selection_mum = 0;
		int selection_dad = 0;
		// so mum and dad are different
		while (selection_mum == selection_dad)
		{
			selection_mum = randint(0, population.size() - 1);
			selection_dad = randint(0, population.size() - 1);
		}
		mum = population[selection_mum];
		dad = population[selection_dad];

		population.clear();

	}
	/* ================================== crossover =============================== //
	* splits parent chromosome up to create child chromosome 
	* only splits with a probabilty of 0.7 known as crossover rate (Pc)
	* or just replace child with copy of mum and dad
	* any split is random generated by a number between 0 and 1 * chromosome size (cb)
	* all child are handed to mutation function 
	*///=========================================================================== //
	void crossover(std::vector<Person>& population, Person& mum, Person& dad)
	{
		ConVar::ConstVariables cv;
		double randSplit = randDouble(0,1);		// random split 
		int cb = cv.getChromosomeSize() * randSplit;	//truncates randSplit represented as fraction into int	
		double Pc = randDouble(0,1);					 //crossover probability
		if (Pc < cv.getCrossoverRate())
		{
			
			std::string newChromosome1,newChromosome2;
			for (int i = 0; i < cb;++i)	// first half chromosome split
			{
				newChromosome1 += mum.getChromosome()[i];
				newChromosome2 += dad.getChromosome()[i];
			}
			for (int i = cb; i < mum.getChromosomeSize(); ++i)	// second half chromosome split 
			{
				newChromosome2 += mum.getChromosome()[i];
				newChromosome1 += dad.getChromosome()[i];
			}
			Person child1 = { newChromosome1 };
			mutation(child1);						// mutation
			child1.createCoordinates();				// creates coordinates after mutation
			population.push_back(child1);			// child1 repopulates
			Person child2 = { newChromosome2 };
			mutation(child2);						// mutation
			child2.createCoordinates();
			population.push_back(child2);			// child2 repopulates
			
		}
		else 
		{
			mutation(mum);
			population.push_back(mum);			// copy of put back in population
			mutation(dad);
			population.push_back(dad);
		}
		
		
	}

	/* ============================ mutation =================================== //
	*  only mutates child with a probability represented as (Pm) random number generated 
	* between 0.001 and 1 ( called by crossover())
	*///======================================================================= //
	void mutation(Person& child)
	{
		ConVar::ConstVariables cv;
		char zero = '0', one = '1';
		double Pm = randDouble(0,1);
		if (Pm <= cv.getMutationRate())
		{
			
			int r = randint(0, child.getChromosomeSize()-1);
			std::string newChromosome = child.getChromosome();
			switch (newChromosome[r])
			{
			case '1':
				newChromosome[r] == '0';
				break;
			case '0':
				newChromosome[r] == '1';
				break;
			default:
				throw "mutation: not recognised chromosome!";
				break;
			}
			child.setChromosome(newChromosome);
		}
	}

	/* ========================= rePopulate ========================================== //
	* re generates numbers for population and repopulates remaining population after 
	* new child is added and decoded int and fitness added to child
	* rest of population is then regenerated to get population back to size n
	*/// ============================================================================ //
	void rePopulate(std::vector<Person>& population)
	{
		ConVar::ConstVariables cv;
		for (int i = 0; i <population.size(); ++i)	//re generates numbers 
		{
			decode_int(population[i]);
			generateFitness(population[i]);
		}
		int newSize = cv.getPopulationSize() - population.size();	// size needed to get population back to n
		generatePopulation(population, newSize);				// generate population back to n

		for (int i = 0; i <population.size(); ++i)				// works out fitness ratio after population is full
		{
			double temp = fitness_ratio(population,population[i]);
			population[i].setFitnessRatio(temp);
		}
	}
	

	/* ========================== gaOutData ====================================== //
	* csv file upload with data: generation, average fitness, highest fitness and 
	* if termination has been reached for each generation
	*/// ========================================================================= //
	void gaOutData(const int& generation, const long long int& averageFitness,
		const double& highest_fitness, const std::string& filename, const bool& termination,
		const std::string& test_num)
	{
		ConVar::ConstVariables cv;
		std::ofstream ost{ filename, std::ios_base::app}; // app = append to end of data
		if (!ost) throw " cannot open output file ", filename;

		if (generation != 1) 
		{
			// == prints data to file csv == //
		//
			ost << generation << ", " << averageFitness << ", " << highest_fitness << ", " << termination << std::endl;
		}
		else
		{
			// == prints titles of table to csv file == //
		//
			ost << "Generation Test id #" << test_num << '\n'
				<< "Generation, " << "Avearge Fitness, " << "Highest Fitness, " << "termination" << '\n'			// newline seperates data rows
				<< generation << ", " << averageFitness << ", " << highestFitness << ", " << termination << std::endl;
		}
		

		ost.close(); // close file after use 
	}

	/* ============================= getGA =============================================== //
	* creates initial population and loops through instructions of generations
	* or finds termination criteria. main purpose so draw loop creates
	* the loop of generations
	*/// ================================================================================ //
	void getGA(int& generation, std::vector<Person>& population, bool& start)
	{
		// == Variables == //
		//
		ConVar::ConstVariables cv;
		
		long long int average_Fitness;	//truncates to stop irational fitness 
		double highest_Fitness = 0;
		bool termination = false;
		
		std::string test_num = "20";
		std::string filename = cv.getGaDataFile() + test_num + cv.getDotcsv();
		
		if (start) {
			// == generate initial poulation == //
			generatePopulation(population, cv.getPopulationSize());
			
			start = false;
			generation++;
			print_population(population);
		}
		else {

			Person mum, dad;
			
			
			roulette_wheel(population, mum, dad);
			//tournament(population, mum, dad);
			//rankSelection(population, mum, dad);

			crossover(population, mum, dad);
			rePopulate(population);
			generation++;
			average_Fitness = populationAvgFitness(population);		// initial generation fitness
			highest_Fitness = highestFitness(population);
			print_population(population);
			termination = is_termination(population);
			if (termination) throw "termination found!";
			
			gaOutData(generation, average_Fitness, highest_Fitness, filename, termination, test_num);
			
		}
		
		
		
			
	}
	
}

