#include <iostream>
#include "Path.h"



int main()
{
	Pair start, destination;
	start = std::make_pair(0, 0);
	destination = std::make_pair(0, 6);

	//start = std::make_pair(15, 3);
	//destination = std::make_pair(130, 23);

	//Cell c("OPOLE2WP_S06_maze.txt");
	Cell c("TEST.txt");

	c.fun_printing_map();
	c.func_finding_best_path(start, destination, 5);
	c.fun_printing_map();
}
