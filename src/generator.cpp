#include "generator.h"

using namespace std;

uniform_real_distribution<float> generator::_uniform_dist = uniform_real_distribution<float>(0.0f, 1.0f);
mt19937 generator::random_engine = mt19937(42/*random_device()()*/);