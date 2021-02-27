#include "Person.h"
#include "ConVar.h"


namespace Individual
{
	// == constructor == //
	Person::Person(std::string chromosome)
		:mDecodedInt(0),mFitness(0),mFitnessRatio(0)
	{
		if (is_chromosome(chromosome))mChromosome = chromosome;
		else throw "person cosntructor: not a chromosome!";
		createCoordinates();
	}

	// ========================= member functions ======================================= //

	/*	================createCoordinates()==================================================
	*	creates points x and y for every two chromosomes
	*	starting Point is x = 100, y = 100
	*	00 = no change (stay same position)
	*	11 = starting Point x + 100, y + 100 ( move straight forward(diagonal accross screen))
	*	01 = starting Point x + 100 (move right(vertical on screen))
	*	10 = starting Point y + 100 (move left (horizontal on screen)) 
	*	=====================================================================================
	*/
	void Person::createCoordinates()
	{
		MyLib::Point start{ 10,10 };
		addCoordinates(start);
		MyLib::Point last = start;
		
		int count = 1;
		int move = 100;

		for (int i = 0; i < mChromosome.length()-1; i++)  //loops through chromosome
		{
			count++;
			if (count == 2)								// every two chromosomes goes to inner loop
			{				
				if (mChromosome[i] == '1' && mChromosome[i + 1] == '1')
				{
					MyLib::Point p = { last.x + move,last.y + move };
					addCoordinates(p);
					last = p;
					count = 0;
				}
				else if (mChromosome[i] == '1' && mChromosome[i + 1] == '0')
				{
					MyLib::Point p = { last.x + move,last.y };
					addCoordinates(p);
					last = p;
					count = 0;
				}
				else if (mChromosome[i] == '0' && mChromosome[i + 1] == '1')
				{
					MyLib::Point p = { last.x,last.y + move };
					addCoordinates(p);
					last = p;
					count = 0;
				}
				else
				{
					addCoordinates(last);
					count = 0;
				}
			}
		}
	}

	// ====================================== helper functions ============================ //

	/* =================is_chromosome()======================
	*	checks whether chromosome is correct length and format
	*	======================================================
	*/
	bool is_chromosome(std::string chromosome)
	{
		ConVar::ConstVariables cv;
		if (chromosome.length() != cv.getChromosomeSize())return false;
		for (char ch : chromosome)
		{
			if (ch != '0' && ch != '1')
			{
				return false;
			}
			return true;
		}
	}

	

	// ======================================== operators ================================= //
	//=== output operator == //
	std::ostream& operator<<(std::ostream& os, Person& person)
	{
		const char colon = ':';
		return os << person.getChromosome() << colon << person.getDecodedInt()
			<< colon << person.getFitness() << colon << person.getFitnessRatio() << std::endl;
	}

	// == comparison operator used in roulette wheel == //
	bool operator<(Person& p1, Person& p2)	// compares Person for sorting vector against fitness ratio
	{
		return (p1.getFitnessRatio() < p2.getFitnessRatio());
	}

	// ============================== Test class ====================================== //
	// == for debugging == //
	void testPerson()
	{
		
		std::cout << "Test: 01=> ";	// test constructor & operator
		Person testPerson_1 = { "0101" };
		std::cout << "test person(1) chromosome=> " << testPerson_1
			<< " : " << "fitness=> " << testPerson_1.getFitness() << std::endl;

		//std::cout << "Test: 02=> ";	// test is_chromosome not binary
		//Person testPerson_2 = { "2120" };

		std::cout << "Test: 03=> ";	// test is_chromosome range
		Person testPerson_3 = { "11011" };

		std::cout << "Test: 04 => ";
		Person testPerson_4 = { "0101110011100001" };
		
	}
}