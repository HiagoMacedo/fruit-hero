/*
 credits: 
 https://stackoverflow.com/a/69125048 @stackoverflowuser2010
*/

#include "UniformRandomInt.h"

UniformRandomInt::UniformRandomInt() {
    set(1, 10);
}

UniformRandomInt::UniformRandomInt(int low, int high) {
    set(low, high);
}

// Set the distribution parameters low and high.
void UniformRandomInt::set(int low, int high) {
    std::uniform_int_distribution<int>::param_type param(low, high);
    _dist.param(param);
}

// Get random integer.
int UniformRandomInt::get() {
    return _dist(_gen);
}