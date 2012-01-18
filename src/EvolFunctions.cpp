#include "EvolFunctions.hpp"
#include <time.h>
#include <cstdlib>
#include <iostream>

namespace evol
{

bool EvolFunctions::isInitialized = false;

void EvolFunctions::initialize()
{
    if(!EvolFunctions::isInitialized)
    {
        srand(time( NULL ));
        EvolFunctions::isInitialized = true;
    }
}

void EvolFunctions::initialize(int seed)
{
    if(!EvolFunctions::isInitialized)
    {
        srand(seed);
        EvolFunctions::isInitialized = true;
    }
}

double EvolFunctions::random()
{
    EvolFunctions::initialize();
    //double dupa = (double)rand()/RAND_MAX;
    //std::cout << "dupa = " << dupa << std::endl;
    //return dupa;
    return (double)rand()/RAND_MAX;
}

int EvolFunctions::random( int begin, int end )
{
    EvolFunctions::initialize();
    return rand()%(end-begin+1)+begin;
}

double EvolFunctions::abs( double valueToAbs )
    {
        if(valueToAbs < 0)
            return -valueToAbs;
        else
            return valueToAbs;
    }


} /* end of evol namespace */
