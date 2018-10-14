#include "generator.h"
#include <random>

using namespace std;

vector<cluster_id_t> generator::generate_solution() const
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

	shuffle(solution.begin(), solution.end()-1, mt19937(random_device()()));

	return solution;
}
