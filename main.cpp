#include <iostream>
#include <fstream>
#include <chrono>

#include "task.h"
#include "generator.h"
#include "validator.h"

using namespace std;


int main(int argc, char *argv[]) 
{
	auto start = chrono::steady_clock::now();

    std::fstream f("../resources/TSALESMAN2-1.in");

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

		auto price = v.find_best_route(solution);
		if(price < best_price)
		{
			best_solution = solution;
			best_price = price;
		}
	}

    std::cout << best_price;
}