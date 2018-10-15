#include "generator.h"
#include <algorithm>

using namespace std;

vector<cluster_id_t> generator::generate_solution()
{
	int n = _data.cluster_count();
	cluster_id_t start_cluster = _data.get_start_cluster();
	vector<cluster_id_t> solution;

	for (int i = 0; i < n; ++i) 
	{
		if (i == start_cluster) continue;
		solution.push_back(i);
	}
	solution.push_back(start_cluster);

	shuffle(solution.begin(), solution.end()-1, _random_engine);
	
	return solution;
}
