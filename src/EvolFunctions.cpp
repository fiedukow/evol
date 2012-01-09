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
    return EvolFunctions::random()*(end-begin+1)+begin;
}

} /* end of evol namespace */
