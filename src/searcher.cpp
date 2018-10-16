#include "searcher.h"

const solution_t& search::run()
{
	return _generator.generate_solution();
}
