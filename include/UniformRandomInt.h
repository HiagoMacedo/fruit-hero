/*
 credits: 
 https://stackoverflow.com/a/69125048 @stackoverflowuser2010
*/

#pragma once
#include <random>

// Returns random integer in closed range [low, high].
class UniformRandomInt {
public:
    UniformRandomInt();
    UniformRandomInt(int low, int high);

    // Set the distribution parameters low and high.
    void set(int low, int high) ;

    // Get random integer.
    int get();

private:
    std::random_device _rd{};
    std::mt19937 _gen{_rd()};
    std::uniform_int_distribution<int> _dist;
};