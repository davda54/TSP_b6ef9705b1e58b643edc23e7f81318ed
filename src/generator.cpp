#include "generator.h"
#include <algorithm>

using namespace std;

generator::generator(const task& t): _data(t), _random_engine(42)
{
	_uniform_dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
	_cluster_count = _data.cluster_count();

	const cluster_id_t start_cluster = _data.get_start_cluster();
	for (size_t i = 0; i < _cluster_count; ++i)
	{
		if (i == start_cluster) continue;
		_solution.push_back(i);
	}
	_solution.push_back(start_cluster);
}

const Solution& generator::generate_solution()
{
	shuffle(_solution.begin(), _solution.end()-1, _random_engine);
	
	return _solution;
}

const Solution& generator::generate_neighbor()
{
	return *swap(_random_engine());
}

const Solution* generator::swap(size_t index){

	_swapped_a = index % (_cluster_count - 1);
	_swapped_b = (_swapped_a + 1) % (_cluster_count - 1);

	_solution[_swapped_a] ^= _solution[_swapped_b];
	_solution[_swapped_b] ^= _solution[_swapped_a];
	_solution[_swapped_a] ^= _solution[_swapped_b];

	return &_solution;
}

const Solution& generator::revert_one_step()
{
	_solution[_swapped_a] ^= _solution[_swapped_b];
	_solution[_swapped_b] ^= _solution[_swapped_a];
	_solution[_swapped_a] ^= _solution[_swapped_b];

	return _solution;
}

