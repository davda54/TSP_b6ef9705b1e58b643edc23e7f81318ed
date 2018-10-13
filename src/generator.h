#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include "task.h"

class generator {

public:

    generator(const task& t) : _data(t){}

    std::vector<cluster_id_t> generate_solution() const {

        int n = _data.cluster_count();
        std::vector<cluster_id_t> solution;

        for (int i=1; i < n; ++i) solution.push_back(i);
        std::random_shuffle(solution.begin(), solution.end());

        return solution;
    }

private:

    const task& _data;

};

#endif