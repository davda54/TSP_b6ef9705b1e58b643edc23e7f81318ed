#include "generator.h"
#include <algorithm>

using namespace std;

generator::generator(const task& t): _data(t), _random_engine(42)
{
	_cluster_count = _data.cluster_count();

	const cluster_id_t start_cluster = _data.get_start_cluster();
	for (size_t i = 0; i < _cluster_count; ++i)
	{
		if (i == start_cluster) continue;
		_solution.push_back(i);
	}
	_solution.push_back(start_cluster);
}

const solution_t& generator::generate_solution()
{
	shuffle(_solution.begin(), _solution.end()-1, _random_engine);
	
	return _solution;
}

const solution_t& generator::generate_neighbor()
{
	_swapped_a = _random_engine() % (_cluster_count - 1);
	_swapped_b = (_swapped_a + 1) % (_cluster_count - 1);

	_solution[_swapped_a] ^= _solution[_swapped_b];
	_solution[_swapped_b] ^= _solution[_swapped_a];
	_solution[_swapped_a] ^= _solution[_swapped_b];

	return _solution;
}

const solution_t& generator::revert_one_step()
{
	_solution[_swapped_a] ^= _solution[_swapped_b];
	_solution[_swapped_b] ^= _solution[_swapped_a];
	_solution[_swapped_a] ^= _solution[_swapped_b];

	return _solution;
}

