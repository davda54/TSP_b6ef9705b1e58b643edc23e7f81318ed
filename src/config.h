#ifndef TSP_CHALLENGE_KIWI_CONFIG_H
#define TSP_CHALLENGE_KIWI_CONFIG_H

class config
{
public:


    /* resources\TSALESMAN2-1.in, INITIAL_TEMP = 10*10, COOLING_TEMP = 0.99999994
     *
     * score average: 1396
     *
     */

    /* resources\TSALESMAN2-3.in, INITIAL_TEMP = 1*150, COOLING_TEMP = 0.9999998
     *
     * score average: 39338.8
     * score std deviation: 776.974
     * score min: 38265
     * score max: 40851
     *
     */

    // ANNEALING PARAMS:
    static double INITIAL_TEMP; //best: 0.3
    static double COOLING_TEMP; // best: 0.9999995

    // 2.in .. 3, 1.2 ---> 1628   / 2137      // 1562,   1.5, 0.05
    // 3.in .. 3, 2.5 ---> 44219  / 42148	  // 41061,  3.8, 0.05
    // 4.in .. 3, 2.3 ---> 111212 / 109968	  // 110008,
    static float GREEDY_SEARCH_EXP;
    static int GREEDY_SEARCH_KNBRS;
    static float GREEDY_SEARCH_RATIO; // 1 -> average, 0 -> min

};

#endif //TSP_CHALLENGE_KIWI_CONFIG_H
