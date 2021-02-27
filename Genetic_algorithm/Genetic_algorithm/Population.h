#ifndef POPULATION_GUARD
#define POPULATION_GUARD 1

#include <string>
#include <vector>
#include "Person.h"

/*====================================================
*	Population is an interface for a genetic algorithm
*	based on Person class 
* ====================================================
*/
namespace Population
{
	using namespace Individual;
	
	// == helper functions == //
	void generatePopulation(std::vector<Person>& population, const int&);
	void decode_int(Person&);
	void generateFitness(Person&);
	double populationAvgFitness(const std::vector<Person>&);
	double fitness_ratio(const std::vector<Person>&, Person&);
	void print_population(const std::vector<Person>&);
	bool is_termination(const std::vector<Person>&);
	double highestFitness(const std::vector<Person>&);
	// == selection == //
	void bubbleSort(std::vector<Person>&);
	void roulette_wheel(std::vector<Person>& ,Person&,Person&);
	void tournament(std::vector<Person>&, Person&, Person&);
	void rankSelection(std::vector<Person>& population, Person& mum, Person& dad);

	void crossover(std::vector<Person>&, Person&, Person&);
	void mutation(Person&);
	void rePopulate(std::vector<Person>&);
	bool is_n_population(const std::vector<Person>&);
	void getGA(int&, std::vector<Person>&, bool&);
	void gaOutData(const int&, const long long int&,
		const double&, const std::string&, const bool&, const std::string& );



}
#endif
#pragma once
