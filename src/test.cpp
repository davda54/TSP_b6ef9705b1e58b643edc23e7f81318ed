#include <iostream>
#include <stdio.h>
#include <cmath>
#include <tuple>

#include "test.h"
#include "annealing.h"
#include "config.h"


using namespace std;

void test::check_performance()
{
	//check_performance("../resources/TSALESMAN2-1.in");
	//check_performance("../resources/TSALESMAN2-2.in");
	/*check_performance("../resources/TSALESMAN2-3.in");
	check_performance("../resources/TSALESMAN2-4.in");*/
	check_performance(150, 250, 20, 1);

}

void test::check_performance(size_t cluster_count, size_t city_count, float average_branching, size_t seed) {

    task t;
    t.generate_input(cluster_count, city_count, average_branching, seed);

	cout << "Artificial input, cluster_c: " << cluster_count << ", city_c: " << city_count << ", branching: " << average_branching << endl << endl;

	run(t);
}

void test::check_performance(const char *path)
{
	cout << path << endl << endl;

    FILE *file;
    file = fopen(path, "r");
    if (file == nullptr) perror("Error opening file");

    task t;
    t.load(file);

	run(t);
}

void test::run(task &t) {

	auto available_time = t.get_available_time();

	double avg_score = 0.0;
	double var_score = 0.0;
	double min_score = std::numeric_limits<double>::max();
	double max_score = 0.0;

	double avg_speed = 0.0;
	double var_speed = 0.0;
	double min_speed = std::numeric_limits<double>::max();
	double max_speed = 0.0;

	const size_t N = 5;

	for (size_t i = 1; i <= N; ++i)
	{
		cout << endl << i;

		total_cost_t score = MAX_TOTAL_COST;
		size_t tried_count = 0;

		auto start = chrono::steady_clock::now();


		//
		// WORKFLOW DEFINITION:

		if (t.cluster_count() < 12 && t.get_number_of_cities() <= 300)
		{
			solution s(t, available_time, solution::init_type::COMPLETE_DFS);
			//s.print(cout);

			score = s.cost();
			tried_count = s.solutions_tried;
		}
		else
		{
			annealing search(t, available_time, "stats.out", start);
			solution s(t, chrono::duration<int>(config::GREEDY_SEARCH_TIME), solution::init_type::GREEDY_DFS);

			cout << " " << s.cost();

			search.run(s);
			//s.print(cout);

			cout << " " << s.cost();

			score = s.cost();
			tried_count = s.solutions_tried;
		}

		// END OF WORKFLOW DEFINITION
		//


		auto time = (chrono::steady_clock::now() - start).count() / 1000000000.0f;

		auto new_avg_score = avg_score + (score - avg_score) / i;
		var_score += (score - avg_score)*(score - new_avg_score);
		avg_score = new_avg_score;

		if (score < min_score) min_score = score;
		if (score > max_score) max_score = score;

		auto speed = tried_count / time;

		auto new_avg_speed = avg_speed + (speed - avg_speed) / i;
		var_speed += (speed - avg_speed)*(speed - new_avg_speed);
		avg_speed = new_avg_speed;

		if (speed < min_speed) min_speed = speed;
		if (speed > max_speed) max_speed = speed;

		cout << "\t" << avg_score;
	}

	cout << "\r";
	cout << "score average: " << avg_score << endl;
	cout << "score std deviation: " << sqrt(var_score / double(N)) << endl;
	cout << "score min: " << min_score << endl;
	cout << "score max: " << max_score << endl;

	cout << "speed average: " << avg_speed << endl;
	cout << "speed std deviation: " << sqrt(var_speed / double(N)) << endl;
	cout << "speed min: " << min_speed << endl;
	cout << "speed max: " << max_speed << endl;

	cout << endl << "===========================================" << endl << endl << endl;
}

