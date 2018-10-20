#include "searcher.h"
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;


Solution searcher::run()
{
	_t = INITIAL_TEMP;

	_generator.generate_solution();

	energy_t current_energy = get_energy(_generator.current_solution());
	energy_t best_energy = current_energy;
	Solution best_solution = _generator.copy_current_solution();
	size_t count = 0;

	while (chrono::steady_clock::now() - _start < _available_time)
	{
		/*if (_generator.rnd_float() < 0.5f) _generator.generate_clever_neighbor();
		else */_generator.generate_neighbor();

		const Solution& solution = _generator.current_solution();
		auto new_energy = get_energy(solution);

		if (new_energy < best_energy)
		{
			best_energy = new_energy;
			best_solution = _generator.copy_current_solution();
			cout << endl << best_energy << endl << "\t" << _t;
		}

		if(new_energy < current_energy)
		{
			current_energy = new_energy;
		}
		else
		{
			float p = acceptance_probability(current_energy, new_energy);

			if (p > _generator.rnd_float()) current_energy = new_energy;
			else
			{
				_generator.revert_one_step();
				_validator.route_cost_approx(solution, _generator.swapped_index());
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
	cout << "permutations: " << count << endl;
	cout << "best energy: " << best_energy << endl << endl;

	return best_solution;
}

float searcher::acceptance_probability(energy_t current, energy_t next) const {

	return (float) exp(-(float)(next - current) / _t);

}

energy_t searcher::get_energy(const Solution& s, size_t swapped_index) const {

	// TODO: better cost function
	return _validator.route_cost_approx(s, swapped_index);
}

energy_t searcher::get_energy(const Solution& s) const {

	// TODO: better cost function
	return _validator.route_cost_approx(s);
}

void searcher::update_temperature() {

	_t *= COOLING_TEMP;

	if((chrono::steady_clock::now() - _start).count() % 100000 == 0)
	{
		cout << "\r\t" << _t;
	}
}

energy_t searcher::get_order_energy(const Solution *s, size_t start, size_t first, size_t second, size_t end) const {

	/*size_t clusters = (_data.cluster_count() - 1);

	size_t a = start;
	size_t b = first % clusters;
	size_t c = second % clusters;
	size_t d = end % clusters;

	return _data.get_cost()*/
	return 0;
}


