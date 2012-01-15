#include "EvolFunctions.hpp"
#include <time.h>
#include <cstdlib>

namespace evol
{

bool EvolFunctions::isInitialized = false;

double EvolFunctions::random()
{
    if(!EvolFunctions::isInitialized)
    {
        srand(time( NULL ));
        EvolFunctions::isInitialized = true;
    }
    return (double)rand()/RAND_MAX;
}

int EvolFunctions::random( int begin, int end )
{
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
