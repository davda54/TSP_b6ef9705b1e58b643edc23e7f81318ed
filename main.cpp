#include <stdio.h>

#include "task.h"
#include "test.h"

using namespace std;

int main(int argc, char *argv[]) 
{
#ifdef _PROFILE
	test::check_performance();
#else
	task t;
    FILE *file = stdin;
    //file = fopen(argv[1], "r");
    //if (file == nullptr) perror("Error opening file");
    //else 
	t.run(file);
    //fclose(file);
#endif
}