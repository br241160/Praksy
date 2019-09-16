#include "Path.h"


void Cell::fun_printing_map() {	

	std::cout << "----WORKSPACE----\n\n";
	for (int i = 0; i < scheme_size.second; i++) {
		for (int j = 0; j < scheme_size.first; j++) {
			std::cout << scheme[i][j];
			if (j == scheme_size.first - 1) {
				std::cout << std::endl;
			}
		}
	}
}

bool Cell::func_checking_destination(const int x, const int y, Pair& dest) {
	if (x == dest.first && y == dest.second) {
#ifdef _DEBUG
		std::cout << x << " " << y << std::endl;
		std::cout << "We have reached the destination" << std::endl;
#endif
		return true;
	}
	return false;
}

bool Cell::func_checking_cell(Pair& cell) {
	if (scheme[cell.second][cell.first] == WAY || scheme[cell.second][cell.first] == BLCKD) {
#ifdef _DEBUG
		std::cout << cell.first << " " << cell.second << std::endl;
		std::cout << "This cell is blocked" << std::endl;
#endif
		return true;
	}
	return false;
}

double Cell::func_checking_path(const int x, const int y, Pair& dest) {
	return sqrt((x - dest.first)*(x - dest.first) + (y - dest.second)*(y - dest.second));
}

void Cell:: func_drawing_path(Pair& dest, Pair& start) {
	int prevx, prevy, tempprevx;
	std::stack<Pair> grids_stack;

	prevx = elem_info[dest.second][dest.first].m_parent_x;
	tempprevx = prevx;
	prevy = elem_info[dest.second][dest.first].m_parent_y;
	scheme[dest.second][dest.first] = 8;

	while (prevx != -1 && prevy != -1) {
		
		if (scheme[prevy][prevx] != WAY) {
			scheme[prevy][prevx] = WAY;
		}
		grids_stack.push(std::make_pair(prevx, prevy));
		
		prevx = elem_info[prevy][prevx].m_parent_x;
		prevy = elem_info[prevy][tempprevx].m_parent_y;
		tempprevx = prevx;
	}

	scheme[start.second][start.first] = 8;

	func_grids_list(grids_stack, dest);	
}

void Cell::func_drawing_way(Pair& start, Pair& end) {

	if (start.first == end.first && start.second != end.second) {
		if ((start.second - end.second) < 0) {
			while (start.second != end.second) {
				start.second++;
				scheme[start.second][start.first] = PATH;
			}
		}
		else if ((start.second - end.second) > 0) {
			while (start.second != end.second) {
				start.second--;
				scheme[start.second][start.first] = PATH;
			}
		}
	}
	else if (start.first != end.first && start.second == end.second) {
		if ((start.first - end.first) < 0) {
			while (start.first != end.first) {
				start.first++;
				scheme[start.second][start.first] = PATH;
			}
		}
		else if ((start.first - end.first) > 0) {
			while (start.first != end.first) {
				start.first--;
				scheme[start.second][start.first] = PATH;
			}
		}
	}
}

void Cell::func_grids_list(std::stack<Pair> grids_stack, Pair& dest) {
	Pair temp_grids;
	Pair path_nod;
	
	path_nod.first = grids_stack.top().first;
	path_nod.second = grids_stack.top().second;

	temp_grids.first = grids_stack.top().first;
	temp_grids.second = grids_stack.top().second;
	grids_stack.pop();

	if (temp_grids.first == grids_stack.top().first && temp_grids.second != grids_stack.top().second) {
		m_direction = VERTICAL;
	}
	else {
		m_direction = HORIZONTAL;
	}
	grids_stack.push(temp_grids);

	std::ofstream grids;
	grids.open("grids_list.txt");
	/*
	if (grids_stack.empty()) {
#ifdef _DEBUG
		std::cout << "Couldn't open the file" << std::endl;
#endif
	}
	*/
	//else {
#ifdef _DEBUG
		std::cout << std::endl << "-----PATH-----" << std::endl;
		std::cout << grids_stack.top().first << " " << grids_stack.top().second << std::endl;
#endif
		/*
		func_drawing_way(path_nod, grids_stack.top());
		path_nod.first = grids_stack.top().first;
		path_nod.second = grids_stack.top().second;
		*/
		grids << grids_stack.top().first << " " << grids_stack.top().second << std::endl;

		while (!grids_stack.empty()) {

			if (m_direction == HORIZONTAL && temp_grids.second == grids_stack.top().second) {
			}
			else if (m_direction == HORIZONTAL && temp_grids.second != grids_stack.top().second) {
				m_direction = VERTICAL;
#ifdef _DEBUG
				
				std::cout << temp_grids.first << " " << temp_grids.second << std::endl;
#endif
				/*
				func_drawing_way(path_nod, grids_stack.top());	//check
				path_nod.first = grids_stack.top().first;
				path_nod.second = grids_stack.top().second;
				*/
				grids << temp_grids.first << " " << temp_grids.second << std::endl;
			}
			else if (m_direction == VERTICAL && temp_grids.first == grids_stack.top().first) {
			}
			else if (m_direction == VERTICAL && temp_grids.first != grids_stack.top().first) {
				m_direction = HORIZONTAL;
#ifdef _DEBUG
				std::cout << temp_grids.first << " " << temp_grids.second << std::endl;
#endif	
				/*
				func_drawing_way(path_nod, grids_stack.top());
				path_nod.first = grids_stack.top().first;
				path_nod.second = grids_stack.top().second;
				*/
				grids << temp_grids.first << " " << temp_grids.second << std::endl;
			}
			func_drawing_way(path_nod, grids_stack.top());
			path_nod.first = grids_stack.top().first;
			path_nod.second = grids_stack.top().second;

			temp_grids.first = grids_stack.top().first;
			temp_grids.second = grids_stack.top().second;
			grids_stack.pop();
		}

		func_drawing_way(path_nod, dest);
		grids << temp_grids.first << " " << temp_grids.second << std::endl;
		grids << dest.first << " " << dest.second << std::endl;

#ifdef _DEBUG
		std::cout << temp_grids.first << " " << temp_grids.second << std::endl;
		std::cout << dest.first << " " << dest.second << std::endl;
#endif
	//}
	grids.close();
}

bool Cell::func_checking_neighbours(int pathx, int pathy) {

	if (m_direction == UP) {
		if (scheme[pathy -1][pathx] == EMPT || scheme[pathy -1][pathx] == WAY) {
			return true;
		}
	}

	else if (m_direction == RIGHT) {
		if (scheme[pathy][pathx +1] == EMPT || scheme[pathy][pathx +1] == WAY) {
			return true;
		}
	}

	else if (m_direction == DOWN) {
		if (scheme[pathy +1][pathx] == EMPT || scheme[pathy +1][pathx] == WAY) {
			return true;
		}
	}

	else if (m_direction == LEFT) {
		if (scheme[pathy][pathx -1] == EMPT || scheme[pathy][pathx -1] == WAY) {
			return true;
		}
	}
	return false;
}

void Cell::func_checking_for_obstacles(int pathx, int pathy) {

	if (pathy - 1 > 0 && scheme[pathy -1][pathx] == BLCKD ) {
		m_direction = UP;
	}
	else if (pathx + 1 < scheme_size.first && scheme[pathy][pathx +1] == BLCKD) {
		m_direction = RIGHT;
	}
	else if (pathy + 1 < scheme_size.second && scheme[pathy +1][pathx] == BLCKD) {
		m_direction = DOWN;
	}
	else if (pathx - 1 > 0 && scheme[pathy][pathx -1] == BLCKD) {
		m_direction = LEFT;
	}
	else {
		m_direction = 'o';
	}
}

Pair Cell::func_straight_path(int pathx, int pathy, char direction, Pair dest) {
	bool test1 = false;
	bool test2 = false;
	Pair grids_straight = std::make_pair(pathx, pathy);
	int count = 0;
	m_counter = 0;

	if (direction == UP) {
		while ((pathy - 1) >= 0 && (scheme[pathy -1][pathx] == EMPT || scheme[pathy -1][pathx] == HORWAY) && count < step_size) {
			if (m_direction == LEFT || m_direction == RIGHT) {
				if (func_checking_neighbours(pathx, pathy) == true) {
					break;
				}
			}
			if (pathy == dest.second) {
				grids_straight = std::make_pair(pathx, pathy);
				break;
			}
			/*
			if (scheme[pathx][pathy -1] == WAY && test1) {
				grids_straight = std::make_pair(pathx, pathy);
				break;
			}
			test1 = false;
			if (scheme[pathx][pathy -1] == WAY) {
				test1 = true;
			}
			*/
			pathy--;
			count++;
			m_counter++;

		}
	}

	else if (direction == RIGHT) {
		while ((pathx + 1) < scheme_size.first && (scheme[pathy][pathx +1] == EMPT || scheme[pathy][pathx +1] == VERTWAY) && count < step_size ) {
			if (m_direction == DOWN || m_direction == UP) {
				if (func_checking_neighbours(pathx, pathy) == true) {
					break;
				}
			}	
			if (pathx == dest.first) {
				grids_straight = std::make_pair(pathx, pathy);
				break;
			}
			/*
			if (scheme[pathx +1][pathy] == WAY && test1) {
				grids_straight = std::make_pair(pathx, pathy);
				break;
			}
			test1 = false;
			if (scheme[pathx +1][pathy] == WAY) {
				test1 = true;
			}
			*/
			pathx++;
			count++;
			m_counter++;

		}
	}

	else if (direction == DOWN) {
		while ((pathy + 1) < scheme_size.second && (scheme[pathy +1][pathx] == EMPT ||scheme[pathy +1][pathx] == HORWAY) && count < step_size) {
			if (m_direction == LEFT || m_direction == RIGHT) {
				if (func_checking_neighbours(pathx, pathy) == true) {
					break;
				}
			}
			if (pathy == dest.second) {
				grids_straight = std::make_pair(pathx, pathy);
				break;
			}
			/*
			if (scheme[pathx][pathy +1] == WAY && test1) {
				grids_straight = std::make_pair(pathx, pathy);
				break;
			}
			test1 = false;
			if (scheme[pathx][pathy +1] == WAY) {
				test1 = true;
			}
			*/
			pathy++;
			count++;
			m_counter++;

		}
	}

	else if (direction == LEFT) {
		while ((pathx - 1) >= 0 && (scheme[pathy][pathx -1] == EMPT || scheme[pathy][pathx -1] == VERTWAY) && count < step_size) {
			if ( m_direction == DOWN || m_direction == UP) {
				if (func_checking_neighbours(pathx, pathy) == true) {
					break;
				}
			}
			if (pathx == dest.first) {
				grids_straight = std::make_pair(pathx, pathy);
				break;
			}
			/*
			if (scheme[pathx -1][pathy] == WAY && test1) {
				grids_straight = std::make_pair(pathx, pathy);
				break;
			}
			
			test1 = false;
			if (scheme[pathx -1][pathy] == WAY) {
				test1 = true;
			}
			*/
			pathx--;
			count++;
			m_counter++;

		}
	}

	return grids_straight = std::make_pair(pathx, pathy);
}

bool Cell::func_checking_collision(const int x, const int y) {
	if (scheme[y][x] == BLCKD) {
		return true;
	}
	return false;
}

bool Cell::func_making_moves(int temp_x, int temp_y, double temp_dist_start, Pair& start, Pair& dest, Pair& parent, char direction) {
	
	Pair cell_grids;
	x = temp_x;
	y = temp_y;

	if (y >= 0 && y < scheme_size.first &&  x >= 0 && x < scheme_size.first && Cell::func_checking_collision(x, y) == false) {

		if (y >= 0 && y < scheme_size.first &&  x >= 0 && x < scheme_size.first && func_checking_destination(x, y, dest) == true) {
			elem_info[y][x].m_parent_x = parent.first;
			elem_info[y][x].m_parent_y = parent.second;
			return true;
		}
		
		else if (y >= 0 && y < scheme_size.first &&  x >= 0 && x < scheme_size.first && visited[y][x] == false && onstack[y][x] == false ) {
			/*
			if (test == true && scheme[x][y] == WAY) {
			}
			*/
			// if (y >= 0 && y < scheme_size.first &&  x >= 0 && x < scheme_size.first) {
				if (direction == UP || direction == DOWN) {
					if (sqrt((dest.second - y)*(dest.second - y)) < (dest.second - parent.second)*(dest.second - parent.second)) {
						cell_grids = func_straight_path(x, y, direction, dest);
						x = cell_grids.first;
						y = cell_grids.second;
					}
				}
				else if (direction == RIGHT || direction == LEFT) {
					if (((dest.first - x)*(dest.first - x)) < (dest.first - parent.first)*(dest.first - parent.first)) {
						cell_grids = func_straight_path(x, y, direction, dest);
						x = cell_grids.first;
						y = cell_grids.second;
					}
				}
				if ((direction == RIGHT || direction == LEFT) && scheme[y][x] != HORWAY) {
					if (visited[y][x] == false) {
						elem_info[y][x].m_parent_x = parent.first;
						elem_info[y][x].m_parent_y = parent.second;
					}
					elem_info[y][x].m_dist_start = temp_dist_start + (m_counter / 2);
					elem_info[y][x].m_dist_target = func_checking_path(x, y, dest);
					elem_info[y][x].m_dist_whole = elem_info[y][x].m_dist_start + elem_info[y][x].m_dist_target;

					short_dist.push(std::make_pair(elem_info[y][x].m_dist_whole, std::make_pair(x, y)));
					onstack[y][x] = true;
				}
				else if ((direction == UP|| direction == DOWN) && scheme[y][x] != VERTWAY) {
					if (visited[y][x] == false) {
						elem_info[y][x].m_parent_x = parent.first;
						elem_info[y][x].m_parent_y = parent.second;
					}
					elem_info[y][x].m_dist_start = temp_dist_start + (m_counter / 2);
					elem_info[y][x].m_dist_target = func_checking_path(x, y, dest);
					elem_info[y][x].m_dist_whole = elem_info[y][x].m_dist_start + elem_info[y][x].m_dist_target;

					short_dist.push(std::make_pair(elem_info[y][x].m_dist_whole, std::make_pair(x, y)));
					onstack[y][x] = true;
				}
			//}
		}
	}
	return false;
}

void Cell::func_finding_best_path(Pair& start, Pair& dest, int steps) {	//pomyslec co moge zwracac a co lepiej wrzucic do paramaetrow klasy, zrobic przekazywanie ilosci krokow

	if (func_checking_cell(start) == true || func_checking_cell(dest) == true) {
		return;
	}

	//std::priority_queue<Pair_d_p, std::vector<Pair_d_p>, std::greater<Pair_d_p>> short_dist;

	//int x, y;	
	x = start.first;
	y = start.second;

	step_size = steps;

	//Pair cell_grids;	

	Pair parent;
	int temp_x, temp_y;	
	//temp_x = -1;
	//temp_y = -1;
	parent.first = -1;
	parent.second = -1;

	int count = 0;
	//bool test = false;	
	test = false;

	elem_info[start.second][start.first].m_dist_start = 0.0;
	elem_info[start.second][start.first].m_dist_target = func_checking_path(x, y, dest);
	elem_info[start.second][start.first].m_dist_whole = func_checking_path(x, y, dest);
	elem_info[start.second][start.first].m_parent_x = parent.first;	
	elem_info[start.second][start.first].m_parent_y = parent.second;

	visited[start.second][start.first] = true;

	double temp_dist_start;
	temp_dist_start = 0.0;	

	short_dist.push(std::make_pair(elem_info[start.second][start.first].m_dist_whole, std::make_pair(x, y)));

	while (!short_dist.empty()) {

		test = false;

		if (func_checking_destination(short_dist.top().second.first, short_dist.top().second.second, dest) == true) {
			elem_info[short_dist.top().second.second][short_dist.top().second.first].m_parent_x = parent.first;
			elem_info[short_dist.top().second.second][short_dist.top().second.first].m_parent_y = parent.second;
			break;
		}
		
		temp_x = short_dist.top().second.first;
		temp_y = short_dist.top().second.second;
		parent.first = temp_x;
		parent.second = temp_y;
		short_dist.pop();

		temp_dist_start = elem_info[temp_y][temp_x].m_dist_start;
		
		elem_info[temp_y][temp_x].m_dist_target = func_checking_path(temp_x, temp_y, dest);
		elem_info[temp_y][temp_x].m_dist_whole = temp_dist_start + func_checking_path(temp_x, temp_y, dest);

		visited[temp_y][temp_x] = true;

		func_checking_for_obstacles(temp_x, temp_y);

		if (scheme[temp_y][temp_x] == WAY) {
			test = true;
		}

#ifdef _DEBUG
		std::cout << /*elem_info[temp_x][temp_y].m_dist_start << " " << elem_info[temp_x][temp_y].m_dist_whole << " " << */temp_x << " " << temp_y << std::endl;
#endif	
		//UP//

		if (func_making_moves(temp_x, (temp_y - 1), temp_dist_start, start, dest, parent, UP) == true) {
			break;
		}
		//RIGHT//
		if (func_making_moves(temp_x + 1, (temp_y), temp_dist_start, start, dest, parent, RIGHT) == true) {
			break;
		}
		//DOWN//
		if (func_making_moves(temp_x, (temp_y + 1), temp_dist_start, start, dest, parent, DOWN) == true) {
			break;
		}
		//LEFT//
		if (func_making_moves(temp_x - 1, (temp_y), temp_dist_start, start, dest, parent, LEFT) == true) {
			break;
		}
	
	}
	
	func_drawing_path(dest, start);

}
