#include <iostream>
#include "Path.h"
#include <chrono>


int main()
{
	Pair start, destination;
	//start = std::make_pair(0, 0);
	//destination = std::make_pair(7, 5);

	start = std::make_pair(33, 3);
	destination = std::make_pair(100, 63);

	Cell c("OPOLE2WP_S06_maze.txt");
	//Cell c("TEST.txt");

	c.fun_printing_map();
	using milli = std::chrono::milliseconds;
	auto start_clock = std::chrono::steady_clock::now();
	c.func_finding_best_path(start, destination, 10, 32);
	auto end_clock = std::chrono::steady_clock::now();
	auto run_time = std::chrono::duration_cast<milli>(end_clock - start_clock).count();
	c.fun_printing_map();
	std::cout << run_time << " ms" << std::endl;
}
