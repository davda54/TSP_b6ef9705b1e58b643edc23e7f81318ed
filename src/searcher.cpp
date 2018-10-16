#include "searcher.h"
#include <iostream>

using namespace std;


const solution_t& searcher::run()
{
	const auto start = chrono::steady_clock::now();

	size_t greatest_length = 0;
	//_generator.generate_solution();

	while (chrono::steady_clock::now() - start < _available_time)
	{
		const solution_t& solution = _generator.generate_neighbor();
		const size_t length = _validator.longest_partial_route(solution);

		if (length < greatest_length)
		{
			_generator.revert_one_step();
		}
		else if(length > greatest_length)
		{
			greatest_length = length;
			cout << greatest_length << endl;
		}
	}

	return _generator.current_solution();
}
