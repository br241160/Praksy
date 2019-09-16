#pragma once
#include <iostream>
#include <cmath>
#include <queue>
#include <utility>
#include <stack>
#include <fstream>
#include <vector>

#define EMPT 0
#define BLCKD 2
#define WAY 1
#define HORWAY 4
#define VERTWAY 5
#define PATH 7
#define ASCII_0 48
#define ASCII_1 49
#define ASCII_2 50
#define ASCII_4 52
#define ASCII_5 53

#define UP 'u'
#define RIGHT 'r'
#define DOWN 'd'
#define LEFT 'l'
#define INF INT_MAX
#define VERTICAL 'y'
#define HORIZONTAL 'x'


typedef std::pair<int, int> Pair;
typedef std::pair<double, Pair> Pair_d_p;


struct element {
	double m_dist_start, m_dist_target, m_dist_whole;
	int m_parent_x, m_parent_y;
};

class Cell {
private:
	char m_direction;
	double m_counter = 0;
	Pair scheme_size;
	
	
	int x, y;
	bool test;
	int  step_size;
	std::priority_queue<Pair_d_p, std::vector<Pair_d_p>, std::greater<Pair_d_p>> short_dist;

	std::vector<std::vector<element>> elem_info;
	std::vector<std::vector<int>> scheme;
	std::vector<std::vector<bool>> visited;
	std::vector<std::vector<bool>> onstack;

	Pair func_straight_path(int, int, char, Pair dest);
	void func_drawing_way(Pair&, Pair&);
	void func_grids_list(std::stack<Pair>, Pair&);

	bool func_making_moves(int, int, double, Pair&, Pair&, Pair&, char);
	bool func_checking_neighbours(int, int);
	void func_checking_for_obstacles(int, int);
	bool func_checking_destination(const int, const int, Pair&);
	bool func_checking_cell(Pair&);
	double func_checking_path(const int, const int, Pair&);
	void func_drawing_path(Pair&, Pair&);
	bool func_checking_collision(const int, const int);

public:
	
	Cell(std::string filename) {

		std::ifstream sheet;
		sheet.open(filename);

		if (!sheet) {
#ifdef _DEBUG
			std::cout << "Couldn't open the file" << std::endl;
#endif
		}
		else {
			int i = 0;
			int j = 0;
			char a = ASCII_0;

			while (!sheet.eof()) {
				scheme.push_back(std::vector<int>());
				elem_info.push_back(std::vector<element>());
				visited.push_back(std::vector<bool>());
				onstack.push_back(std::vector<bool>());

				i = 0;
				while ((a = sheet.get()) != '\n' && !sheet.eof()) {	
					
					scheme[j].push_back(a);
					
					if (scheme[j][i] == ASCII_1) {
						scheme[j][i] = WAY;
					}
					else if (scheme[j][i] == ASCII_0) {
						scheme[j][i] = EMPT;
					}
					else if (scheme[j][i] == ASCII_2) {
						scheme[j][i] = BLCKD;
					}
					else if (scheme[j][i] == ASCII_4) {
						scheme[j][i] = HORWAY;
					}
					else if (scheme[j][i] == ASCII_5) {
						scheme[j][i] = VERTWAY;
					}
					
					elem_info[j].push_back(element());
					elem_info[j][i].m_dist_whole = INF;
					visited[j].push_back(false);
					onstack[j].push_back(false);

					i++;
				}
				a = ASCII_0;
				j++;
			}
			sheet.close();
			scheme_size.first = i;
			scheme_size.second = j;
		}
		
	}

	void fun_printing_map();
	void func_finding_best_path(Pair&, Pair&, int);
	
	//Pair func_checking_scheme_size(std::string file);
	//bool func_reading_map(std::string file);
};