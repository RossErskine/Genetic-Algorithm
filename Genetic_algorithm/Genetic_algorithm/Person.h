#ifndef PERSON_GUARD
#define PERSON_GUARD 1

#include <string>
#include <iostream>
#include <vector>
#include "Point.h"

namespace Individual
{
	
	class Person
	{
	public:
		// == constructor == //
		Person():mFitness(0),mDecodedInt(0),mFitnessRatio(0){}
		Person(std::string);

		// == non-modifying operations == //
		std::string getChromosome() const { return mChromosome; }
		int getChromosomeSize() const { return mChromosome.length(); }
		double getFitness() const { return mFitness; }
		double getDecodedInt() const { return mDecodedInt; }
		double getFitnessRatio() const { return mFitnessRatio; }
		std::vector<MyLib::Point> getCoordinates() const { return mCoordinates; }

		// == modifying operations == //
		void setChromosome(std::string chromosome) { mChromosome = chromosome; }
		void setFitness(double& fitness) { mFitness = fitness; }
		void setDecodedInt(double decodedInt) { mDecodedInt = decodedInt; }
		void setFitnessRatio(double fitnessRatio) { mFitnessRatio = fitnessRatio; }
		void addCoordinates(MyLib::Point p) { mCoordinates.push_back(p); }
		void createCoordinates();	//creates point coordinates from chromosome

	private:
		std::string mChromosome;
		double mFitness;
		double mDecodedInt;
		double mFitnessRatio;
		std::vector<MyLib::Point> mCoordinates;
	};

	// == helper functions == //
	bool is_chromosome(std::string);
	
	// == operators == //
	std::ostream& operator<<(std::ostream& os, Person& person); // writes person to console for debugging
	bool operator<(Person& p1, Person& p2);						// compares person for sorting

	// == test class == //
	void testPerson();
}
#endif
#pragma once
