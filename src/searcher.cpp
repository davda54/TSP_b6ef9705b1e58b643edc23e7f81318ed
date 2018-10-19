#include "searcher.h"

#include "solution.h"
#include "generator.h"

#include <iostream>
#include <cmath>


using namespace std;


searcher::searcher(const task& data, std::chrono::duration<int> available_time, const std::string& stats_path, std::chrono::steady_clock::time_point start): _data(data), _available_time(available_time), _start(start)
{
	_stats = std::ofstream(stats_path);
}

Solution searcher::run()
{
	_t = INITIAL_TEMP;

	solution s(_data);

	energy_t current_energy = s.cost();
	energy_t best_energy = current_energy;
	size_t count = 0;

	while (chrono::steady_clock::now() - _start < _available_time)
	{
		s.permute();

		energy_t new_energy = s.cost();

		if (new_energy < best_energy)
		{
			best_energy = new_energy;
			cout << endl << best_energy << endl << "\t" << _t;
		}

		if(new_energy < current_energy)
		{
			current_energy = new_energy;
		}
		else
		{
			float p = acceptance_probability(current_energy, new_energy);

			if (p > generator::rnd_float()) 
			{
				current_energy = new_energy;
				s.submit_step();
			}
			else
			{
				s.revert_step();
			}
		}

        // PRINT DEBUG
        //if (count % 1000 == 0)_stats << count << ' ' << current << ' ' << best << ' ' << _t << '\n';
        // PRINT DEBUG

		if(new_energy == 0)
		{
			break;
		}

		count++;
		update_temperature();
	}

	cout << endl << endl << "time: " << (chrono::steady_clock::now() - _start).count() / 1000000.0 << " ms" << endl;
	cout << "permutations: " << count << endl << endl;

	return s.clusters();
}

float searcher::acceptance_probability(energy_t current, energy_t next) const 
{
	return (float) exp(-(float)(next - current) / _t);
}

void searcher::update_temperature() 
{
	_t *= COOLING_TEMP;

	if((chrono::steady_clock::now() - _start).count() % 100000 == 0)
	{
		cout << "\r\t" << _t;
	}
}