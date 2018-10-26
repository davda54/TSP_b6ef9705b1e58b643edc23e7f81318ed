#ifndef TSP_CHALLENGE_KIWI_TEST_H
#define TSP_CHALLENGE_KIWI_TEST_H

#include <string>
#include "task.h"

class test
{
public:
	static void check_performance();

private:
    static void check_performance(const char *path);
	static void check_performance(size_t cluster_count, size_t city_count, float average_branching, size_t seed);
	static void run(task& t);
};

#endif