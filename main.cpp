#include <string>
#include <fstream>
#include <iostream>

#include "task.h"
#include "generator.h"
#include "validator.h"

using namespace std;


int main(int argc, char *argv[]) 
{
	auto start = chrono::steady_clock::now();

    std::ifstream f(argv[1]);
		
    task t;
    t.load(f);

	generator g(t);
	validator v(t);

	auto max_duration = t.get_available_time();
	auto best_price = INVALID_ROUTE;
	vector<int> best_solution;

	while(chrono::steady_clock::now() - start < max_duration)
	{
		auto solution = g.generate_solution();

		if(!v.exist_route(solution)) continue;

		auto price = v.route_cost(solution);
		if(price < best_price)
		{
			best_solution = solution;
			best_price = price;
		}
	}

	auto route = v.find_route(best_solution);

    std::cout << best_price << endl;
	t.print_path(route, cout);
}