#include "generator.h"
#include <algorithm>

using namespace std;

generator::generator(const task& t): _data(t), _random_engine(42)
{
	const cluster_id_t start_cluster = _data.get_start_cluster();

	for (size_t i = 0; i < _data.cluster_count(); ++i)
	{
		if (i == start_cluster) continue;
		_solution.push_back(i);
	}
	_solution.push_back(start_cluster);
}

const vector<cluster_id_t>& generator::generate_solution()
{
	shuffle(_solution.begin(), _solution.end()-1, _random_engine);
	
	return _solution;
}
