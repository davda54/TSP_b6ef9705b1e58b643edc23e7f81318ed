/*

#ifndef TSP_CHALLENGE_KIWI_POPULATION_H
#define TSP_CHALLENGE_KIWI_POPULATION_H

#include "solution.h"
#include "generator.h"
#include "annealing.h"
#include <chrono>
#include <algorithm>

#include <iostream>
using namespace std;

class evolution
{
public:
    evolution(task& data, generator& g, validator &v, std::chrono::duration<int> available_time, std::chrono::duration<int> start) :
        _data(data), _generator(g), _validator(v), _available_time(available_time), _start(start) {

        for (int i = 0; i < POPULATION_SIZE; ++i) {
            _population.emplace_back(_data, _generator, _validator);
        }
    }

    const Solution& run(){

        Solution* best_solution;
        auto best_cost = 0;
        int generation = 0;

        while (std::chrono::steady_clock::now() - _start < _available_time)
        {
            std::cout << "Generation: " << ++generation << std::endl;

            for (int i = 0; i < POPULATION_SIZE; ++i) {
                _population[i].run(std::chrono::duration<int>(MAX_ANNEALING_TIME));
            }
            crossing();

            best_solution = &_population[0].get_solution();
            best_cost = _population[0].get_solution().get_cost();
            for (int i = 1; i < POPULATION_SIZE; ++i) {
                auto cost = _population[i].get_solution().get_cost();
                if (cost < best_cost){
                    best_cost = cost;
                    best_solution = &_population[i].get_solution();
                }
            }

            cout << endl << endl << "time: " << (chrono::steady_clock::now() - _start).count() / 1000000.0 << " ms" << endl;
            cout << "best cost: " << best_cost << endl << endl;
        }

        return *best_solution;
    }

private:

    void crossing() {

        // not sure about whether we really want to sort entire vector instead of some sampling
        sort(_population.begin(), _population.end(), [ ]( const annealing& l, const annealing& r ){
            return l.get_solution().get_cost() < r.get_solution().get_cost();;
        });

        vector<size_t> to_cross;

        auto best = _population[0].get_solution().get_cost();
        auto worst = _population[0].get_solution().get_cost();

        for (size_t i = ELITISM_SIZE; i < ; ++i) {

            auto cost = _population[i].get_solution().get_cost();

            // TODO: avoid float -- division and so on
            if ((float)(cost - worst) / (float)(best - worst) > _generator.rnd_number()) {
                to_cross.push_back(i);
            }

            to_cross.push_back(i);
        }

        for (int j = 0; j + 1 < _population.size() - 1; j += 2) {
            cross(to_cross[j], to_cross[j + 1]);
        }
    }

    void cross(size_t ind_a, size_t ind_b){

        // najit pozici na ktery se obe veci shoduji a pak je nejak spojit
        // tu pozici bud nejbliz nejakymu random indexu nebo proste od stredu?
        // pak bych ale nemusel krizit nic jinyho nez jen pulky



        // TODO: napsat spojeni dvou Solution veci do jediny ale to nevim jak uplne
        // udelat kvuli tem chache :/

        _population[ind_b] = annealing(_data, _generator, _validator);
    }

    // PARAMETERS:
    const size_t POPULATION_SIZE = 50;
    const size_t ELITISM_SIZE = 10;
    const size_t MAX_ANNEALING_TIME = 1;

    std::vector<annealing> _population;
    std::chrono::duration<int> _available_time;
    std::chrono::duration<int> _start;

    task& _data;
    generator& _generator;
    validator& _validator;

};


#endif //TSP_CHALLENGE_KIWI_POPULATION_H

 */