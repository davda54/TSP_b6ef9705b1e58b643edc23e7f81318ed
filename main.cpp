#include <fstream>

#include "task.h"
#include "test.h"

using namespace std;


int main(int argc, char *argv[]) 
{
	//test::check_performance();
	
	task t;
	std::ifstream input(argv[1]);
	t.run(input);	
}