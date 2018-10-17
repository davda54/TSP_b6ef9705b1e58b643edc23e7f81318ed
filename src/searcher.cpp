#include "searcher.h"
#include <iostream>
#include <cmath>

using namespace std;


const Solution& searcher::run()
{
	const auto start = chrono::steady_clock::now();
	auto best = 0;

	_t = INITIAL_TEMP;
	energy_t current = get_energy(_generator.generate_solution());
	//const Solution* solution = &_generator.generate_solution();

	_generator.generate_solution();

	while (chrono::steady_clock::now() - start < _available_time)
	{
		//auto rnd = _generator.rnd_number();
		const Solution& solution = _generator.generate_neighbor();
		auto new_energy = get_energy(solution);

//		auto current = get_order_energy(solution, rnd - 1, rnd, rnd + 1, rnd + 2);
//		auto new_energy = get_order_energy(solution, rnd - 1, rnd + 1, rnd, rnd + 2);

		float p = acceptance_probability(current, new_energy);

		if (p > _generator.rnd_float()) {
			//solution = _generator.swap(rnd);
			current = new_energy;
		}
		else _generator.revert_one_step();

		if(new_energy > best)
		{
			best = new_energy;
			cout << best << endl;
		}

		if(new_energy == _data.cluster_count())
		{
			return _generator.current_solution();
		}

		update_temperature();
	}



	return _generator.current_solution();
}

float searcher::acceptance_probability(energy_t current, energy_t next) const {

	if (next >= current) return 1.0;
	return (float) exp((float)(next - current) / _t);

}

energy_t searcher::get_energy(const Solution& s) const {

	// TODO: better cost function
	return _validator.longest_partial_route(s);
}

void searcher::update_temperature() {

	_t *= COOLING_TEMP;
}

energy_t searcher::get_order_energy(const Solution *s, size_t start, size_t first, size_t second, size_t end) const {

	/*size_t clusters = (_data.cluster_count() - 1);

	size_t a = start;
	size_t b = first % clusters;
	size_t c = second % clusters;
	size_t d = end % clusters;

	return _data.get_cost()*/
}


