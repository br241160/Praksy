#include <iostream>
#include "Path.h"
#include <chrono>


int main()
{
	Pair start, destination;
	int file_number = 0;
	//start = std::make_pair(0, 0);
	//destination = std::make_pair(7, 5);


	start = std::make_pair(39, 38);
	destination = std::make_pair(55, 97);

	//Cell c("OPOLE2WP_S06_maze.txt");
	//Cell c("TEST.txt");
	//Cell c("OPOLE2WP.S29.maze.txt");
	//Cell c("OPOLE2WP.S52.maze.txt");
	//Cell c("OPOLE2WP.S42.maze.txt");
	Cell c("OPOLE2WP_S06_maze_updated.txt");
	//Cell c("OPOLE2WP.S29.maze_updated.txt");

	srand(time(NULL));

	/*
	for (int i = 0; i < 10; i++) {
		file_number++;

		start.first = rand() % ((c.scheme_size.first - 32) + 1);
		start.second = rand() % ((c.scheme_size.second) + 1);
		while (c.func_checking_cell(start)) {
			start.first = rand() % ((c.scheme_size.first - 32) + 1);
			start.second = rand() % ((c.scheme_size.second) + 1);
		}
		destination.first = rand() % ((c.scheme_size.first - 32) + 1);
		destination.second = rand() % ((c.scheme_size.second) + 1);
		while (c.func_checking_cell(destination)) {
			destination.first = rand() % ((c.scheme_size.first - 32) + 1);
			destination.second = rand() % ((c.scheme_size.second) + 1);
		}
#ifdef _DEBUG
		std::cout << start.first << " " << start.second << std::endl;
		std::cout << destination.first << " " << destination.second << std::endl;
#endif

*/
		//c.fun_printing_map();
		//using milli = std::chrono::milliseconds;
		//auto start_clock = std::chrono::steady_clock::now();
		c.func_finding_best_path(start, destination, 10, 32);
		c.func_printing_map_and_path(file_number);
		c.func_cleaning();
		//c.func_grids_list(destination, tests);
		//auto end_clock = std::chrono::steady_clock::now();
		//auto run_time = std::chrono::duration_cast<milli>(end_clock - start_clock).count();
		//c.fun_printing_map();
		//std::cout << run_time << " ms" << std::endl;
	//}
}
