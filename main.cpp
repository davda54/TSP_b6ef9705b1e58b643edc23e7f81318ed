#include <stdio.h>

#include "task.h"
#include "test.h"

using namespace std;


int main(int argc, char *argv[]) 
{
	//test::check_performance();
	
	task t;
    FILE *file;
    file = fopen(argv[1], "r");
    if (file == nullptr) perror("Error opening file");
    else t.run(file);
    fclose(file);
}