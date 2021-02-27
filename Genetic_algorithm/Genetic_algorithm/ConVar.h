#include <string>

namespace ConVar
{
	class ConstVariables
	{
	public:

		// == non-modifying operations == //
		int getChromosomeSize() const { return mChromosome_size; }
		int getPopulationSize() const { return mPopulation_size; }
		double getTermination() const { return mTermination; }
		double getCrossoverRate() const { return mCrossover_rate; }
		double getMutationRate() const { return mMutation_rate; }
		std::string getGaDataFile() const { return mGaDataFile; }
		std::string getDotcsv() const { return mDotcsv; }
		int getInstructions() const { return mInstructions; }

	private:
		const int mChromosome_size = 8;
		const int mPopulation_size = 6;
		const double mTermination = 255;
		const double mCrossover_rate = 0.7;
		const double mMutation_rate = 0.001;
		const std::string mGaDataFile = "gaDataFile";
		const std::string mDotcsv = ".csv";
		const int mInstructions = 50;
	};
}
