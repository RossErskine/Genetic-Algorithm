#include "Point.h"
#include "MyWindow.h"
#include "MyTools.h"
#include "Person.h"
#include "Population.h"
#include "GUI.h"

#include <vector>


namespace MyLib
{
	// == Ga_Window derived from base class MyWindow == //
	struct GA_window : MyWindow
	{
		// == constructor == //
		GA_window(int w, int h, const std::string& title);

		// == non-modifying operations == //
		int getGeneration() const { return mGeneration; }
		int getChromosomeCount() const { return mChromosomeCount; }
		void getPopulation();

		// == modifying operations == //
		void setGeneration(int generation) { mGeneration = generation; }
		void setChromosomeCount(int chromosomeCount) { mChromosomeCount = chromosomeCount; }
		void addChromosomeCount() { mChromosomeCount++; }

	private:

		Out_box gen_out;	// output box
		int mGeneration;
		int mChromosomeCount;

		Vector_ref<MyCircle> mHorde;
		std::vector<Individual::Person> currPopulation;

		// == callback and game loop == //
		bool start;
		static void cb_game_loop(Address pw);
		void game_loop();
		
	};
	
	
}
