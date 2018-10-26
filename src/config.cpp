#include "config.h"

// 2.in .. 3, 1.2 ---> 1628   / 2137      // 1562,   1.5, 0.05
// 3.in .. 3, 2.5 ---> 44219  / 42148	  // 41061,  3.8, 0.05
// 4.in .. 3, 2.3 ---> 111212 / 109968	  // 110008,

float config::GREEDY_SEARCH_EXP = 1.2f;
int config::GREEDY_SEARCH_KNBRS = 3;
float config::GREEDY_SEARCH_RATIO = 0.05f;


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

double config::INITIAL_TEMP = 1;
double config::COOLING_TEMP = 0.9999998;
