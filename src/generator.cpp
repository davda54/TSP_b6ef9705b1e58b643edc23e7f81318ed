#include "generator.h"
#include <random>

using namespace std;

vector<cluster_id_t> generator::generate_solution() const
{
	int n = _data.cluster_count();
	vector<cluster_id_t> solution;

	for (int i = 1; i < n; ++i) solution.push_back(i);
	shuffle(solution.begin(), solution.end(), mt19937(random_device()()));

	return solution;
}
