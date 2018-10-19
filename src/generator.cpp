#include "generator.h"
#include <algorithm>

using namespace std;

generator::generator(const task& t): _data(t), _random_engine(random_device()())
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
	_swapped_a = _random_engine() % (_cluster_count - 1);
	_swapped_b = (_swapped_a + 1) % (_cluster_count - 1);

	_solution[_swapped_a] ^= _solution[_swapped_b];
	_solution[_swapped_b] ^= _solution[_swapped_a];
	_solution[_swapped_a] ^= _solution[_swapped_b];

	return _solution;
}

const Solution& generator::generate_clever_neighbor()
{
	for (size_t i = 0; i < 30; ++i)
	{
		_swapped_a = _random_engine() % (_cluster_count - 2);
		_swapped_b = _swapped_a + 1;

		const auto a = _solution[((int)_swapped_a - 1) % (_cluster_count - 1)];
		const auto b = _solution[_swapped_a];
		const auto c = _solution[_swapped_b];
		const auto d = _solution[_swapped_b + 1];

		// a -- b -- c -- d
		auto conflicts_before = _data.get_conflict(a, b, _swapped_a)
			+ _data.get_conflict(b, c, _swapped_b)
			+ _data.get_conflict(c, d, _swapped_b + 1);

		// a -- c -- b -- d
		auto conflict_after = _data.get_conflict(a, c, _swapped_a)
			+ _data.get_conflict(c, b, _swapped_b)
			+ _data.get_conflict(b, d, _swapped_b + 1);

		if (conflict_after <= conflicts_before) break;
	}

	_solution[_swapped_a] ^= _solution[_swapped_b];
	_solution[_swapped_b] ^= _solution[_swapped_a];
	_solution[_swapped_a] ^= _solution[_swapped_b];

	return _solution;
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

