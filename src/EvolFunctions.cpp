#include "EvolFunctions.hpp"
#include <time.h>
#include <cstdlib>

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

double EvolFunctions::random()
{
    EvolFunctions::initialize();
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
