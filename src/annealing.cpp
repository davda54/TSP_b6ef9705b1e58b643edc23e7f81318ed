#include "annealing.h"

#include "solution.h"
#include "generator.h"

#include <iostream>
#include <cmath>


using namespace std;


annealing::annealing(const task& data, std::chrono::duration<int> available_time, const std::string& stats_path): _data(data), _available_time(available_time)
{
	//_stats = std::ofstream(stats_path);
}

void annealing::run(solution& s)
{
	_start = chrono::steady_clock::now();
	_t = INITIAL_TEMP*_data.cluster_count();

	energy_t current_energy = s.cost();
	energy_t best_energy = current_energy;
	vector<cluster_id_t> best_solution = s.copy_clusters();

	permutations = 0;

	while (chrono::steady_clock::now() - _start < _available_time)
	{
		s.permute();

		energy_t new_energy = s.cost();

		if (new_energy < best_energy)
		{
			best_energy = new_energy;
			best_solution = s.copy_clusters();
#ifdef _PRINT
			cout << endl << best_energy << endl << "\t" << _t;
#endif
		}

		if (new_energy < current_energy || acceptance_probability(current_energy, new_energy) > generator::rnd_float())
		{
			current_energy = new_energy;
			s.submit_step();
		}
		else
		{
			s.revert_step();
		}

		// PRINT DEBUG
		//if (count % 1000 == 0)_stats << count << ' ' << current << ' ' << best << ' ' << _t << '\n';
		// PRINT DEBUG

		++permutations;
		update_temperature();
	}

	time = chrono::steady_clock::now() - _start;

	s.set_clusters(move(best_solution));
}

float annealing::acceptance_probability(energy_t current, energy_t next) const
{
	return (float) exp(-(float)(next - current) / _t);
}

void annealing::update_temperature()
{
	_t *= COOLING_TEMP;

#ifdef _PRINT
	if((chrono::steady_clock::now() - _start).count() % 100000 == 0)
	{
		cout << "\r\t" << _t;
	}
#endif
}