#ifndef TSP_CHALLENGE_KIWI_TEST_H
#define TSP_CHALLENGE_KIWI_TEST_H

#include <string>

class test
{
public:
	static void check_performance();

private:
	static void check_performance(const std::string& path);
};

#endif