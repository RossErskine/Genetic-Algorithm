#include "Horde.h"
#include "ConVar.h"
#include <iostream>

namespace MyLib
{
	// == constructor == //
	GA_window::GA_window(int w, int h, const std::string& title)
		: MyWindow{w,h,title }, mGeneration{0}, mChromosomeCount{0},
		gen_out{ Point{280,100},100,20,"Generation:" }, start(true)
	{
		attach(gen_out);
		
		Population::getGA(mGeneration, currPopulation,start); // create initial population
		for (int i = 0; i < currPopulation.size(); i++)	// adds circle to mHorde for every Person in population
		{
			mHorde.push_back(new MyCircle{ Point{currPopulation[i].getCoordinates()[0]},10 }); // adds to vector
			mHorde[mHorde.size() - 1].set_fill_color(MyColor::yellow);	// sets fill color to yellow
			attach(mHorde[mHorde.size() - 1]);							// adds circle to screen
			
		}
		addChromosomeCount();							// chromosome count++
		constexpr double delay = 1.0;                   // Delay before first timeout
		Fl::add_timeout(delay, cb_game_loop, this);		// starts timeout with callback
	}

	// == gets genetic algorithm from population == //
	void GA_window::getPopulation()
	{
		if (mGeneration == 100) throw "Run ended!";
		setChromosomeCount(0);
		//currPopulation.clear();			// emptys vector to be filled by new one otherwise they stack up
		Population::getGA(mGeneration, currPopulation, start);
	}

	// == fltk callback == //
	void GA_window::cb_game_loop(Address pw)
	{
		const double delay = 0.25;
		reference_to<GA_window>(pw).game_loop();		// creates child widget with reference to window used
		Fl::repeat_timeout(delay, cb_game_loop, pw);	// starts game loop via recursion
		
	}

	// == game loop that creates child widget on window == //
	void GA_window::game_loop()
	{
		ConVar::ConstVariables cv;
		for (int i = 0; i < mHorde.size(); i++)
		{
			int x = currPopulation[i].getCoordinates()[mChromosomeCount].x;
			int y = currPopulation[i].getCoordinates()[mChromosomeCount].y;
			mHorde[i].move(x, y);								// move circle in mHorde vector
		}
		
		addChromosomeCount();
		if (mChromosomeCount == 4)
		{

			getPopulation();								// gets genetic algorithm from population

			std::string stGen = std::to_string(mGeneration);	// turns int into string for output box
			gen_out.put(mGeneration);							// output box
		}

		redraw();
		
	}

}

