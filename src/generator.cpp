#include "generator.h"

using namespace std;

uniform_real_distribution<float> generator::_uniform_dist = uniform_real_distribution<float>(0.0f, 1.0f);
mt19937 generator::_random_engine = mt19937(random_device()());