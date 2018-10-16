#include <iostream>
#include <fstream>

#include "test.h"
#include "task.h"
#include "generator.h"
#include "validator.h"


using namespace std;

void test::check_performance()
{
	check_performance("TSALESMAN2-1.in"); // best solutions: 2 114 526, cost: 1407
	check_performance("TSALESMAN2-2.in"); // best solutions: 2 688 053, cost: 2147483647
	check_performance("TSALESMAN2-3.in"); // best solutions: 4 409 707, cost: 2147483647
	check_performance("TSALESMAN2-4.in"); // best solutions: 1 711 945, cost: 2147483647
}

void test::check_performance(const std::string& path)
{
	auto start = chrono::steady_clock::now();

	std::ifstream f(path);

	size_t solution_count = 0;

	task t;
	t.load(f);

	generator g(t);
	validator v(t);

	auto max_duration = t.get_available_time();
	total_cost_t best_price = INT32_MAX;

	while (chrono::steady_clock::now() - start < max_duration)
	{
		auto solution = g.generate_solution();

		solution_count++;

		if (!v.exist_route(solution)) continue;
		//else cout << "ha";
		auto price = v.route_cost(solution);
		if (price < best_price)
		{
			best_price = price;
		}
	}

	cout << path << ": clusters: " << t.cluster_count() << ",\tsolutions: " << solution_count << ",\tcost: " << best_price << endl;
}
