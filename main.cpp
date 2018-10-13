#include <iostream>
#include <fstream>

#include "utilities.h"
#include "generator.h"
#include "task.h"

int main() {

    std::ifstream file("../resources/TSALESMAN2-4.in");

    task t;
    t.load(file);

    std::cout << "Hello, World!" << std::endl;

    return 0;
}