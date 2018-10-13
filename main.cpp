#include <iostream>
#include <fstream>
#include <task.h>

int main(int argc, char *argv[]) {

    std::fstream f("../resources/TSALESMAN2-1.in");

    task t;
    t.load(f);

    std::cout << "BAF";

}