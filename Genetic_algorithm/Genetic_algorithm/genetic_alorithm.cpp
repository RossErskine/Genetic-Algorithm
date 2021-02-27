#include "Horde.h"

//#include "Population.h"

int main()
{
	try
	{
		MyLib::GA_window win{ 400,400,"Genetic algorithm " };{}
		MyLib::MyRectangle goal(MyLib::Point{ 380,380 }, 20, 20);
		goal.set_fill_color(MyLib::MyColor::red);
		win.attach(goal);
		return MyLib::gui_main();
		
	}
	catch (const char* msg)
	{
		std::cerr << msg << std::endl;
	}
	catch (...)
	{
		std::cerr << "exception\n";
	}
}
