#include <iostream>
#include <stdio.h>
#include <cmath>

#include "test.h"
#include "task.h"
#include "annealing.h"

using namespace std;

void test::check_performance()
{
	check_performance("../resources/TSALESMAN2-1.in"); // best solutions: 2 114 526, cost: 1407
	check_performance("../resources/TSALESMAN2-2.in"); // best solutions: 2 688 053, cost: 2147483647
	check_performance("../resources/TSALESMAN2-3.in"); // best solutions: 4 409 707, cost: 2147483647
	check_performance("../resources/TSALESMAN2-4.in"); // best solutions: 1 711 945, cost: 2147483647
}

void test::check_performance(const char *path)
{
	cout << path << endl << endl;

    FILE *file;
    file = fopen(path, "r");
    if (file == nullptr) perror("Error opening file");

	task t;
	t.load(file);

	const auto max_duration = t.get_available_time();

	double avg_time = 0.0;
	double var_time = 0.0;
	double min_time = std::numeric_limits<double>::max();
	double max_time = 0;

	double avg_speed = 0;
	double var_speed = 0;
	double min_speed = std::numeric_limits<double>::max();
	double max_speed = 0;


	for (size_t i = 1; i <= 10; ++i)
	{
		cout << "\r" << i;

		auto start = chrono::steady_clock::now();

		//annealing s(t, max_duration, "stats.out");
		solution solution(t);
		//s.run(solution);

		auto time_diff = chrono::steady_clock::now() - start;

		auto time = time_diff.count() / 1000000000.0f;

		auto new_avg_time = avg_time + (time - avg_time) / (i);
		var_time += avg_time*avg_time - new_avg_time*new_avg_time + (time*time - var_time - avg_time*avg_time) / (i);
		avg_time = new_avg_time;

		if (time < min_time) min_time = time;
		if (time > max_time) max_time = time;


		/*auto speed = s.permutations / time;

		auto new_avg_speed = avg_speed + (speed - avg_speed) / (i + 1);
		var_speed += avg_speed * avg_speed - new_avg_speed * new_avg_speed + (speed*speed - var_speed - avg_speed * avg_speed) / (i + 1);
		avg_speed = new_avg_speed;

		if (speed < min_speed) min_speed = speed;
		if (speed > max_speed) max_speed = speed;*/
	}  

	cout << "\r";
	cout << "time average: " << avg_time << endl;
	cout << "time std deviation: " << sqrt(var_time) << endl;
	cout << "time min: " << min_time << endl;
	cout << "time max: " << max_time << endl;

	/*cout << "speed average: " << avg_speed << endl;
	cout << "speed std deviation: " << sqrt(var_speed) << endl;
	cout << "speed min: " << min_speed << endl;
	cout << "speed max: " << max_speed << endl;*/

	cout << endl << "===========================================" << endl << endl << endl;
}
