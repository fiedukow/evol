#include "EvolFunctions.hpp"
#include <time.h>
#include <cstdlib>
#include <iostream>

#ifdef GSL_AVAILABLE
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#endif //GSL_AVAILABLE

namespace evol
{

bool EvolFunctions::isInitialized = false;

#ifdef GSL_AVAILABLE
bool EvolFunctions::isGSLInitialized = false;
gsl_rng* EvolFunctions::gslRandomNumberGenerator = NULL;
#endif

void EvolFunctions::initialize()
{
    initialize(time(NULL));
}

#ifdef GSL_AVAILABLE
void EvolFunctions::initializeGSL()
{
    initializeGSL(time(NULL));  
}

void EvolFunctions::initializeGSL(int seed)
{
    if(!isGSLInitialized)
    {
      const gsl_rng_type* generatorType;
      gsl_rng_env_setup();
      generatorType = gsl_rng_default;
      gslRandomNumberGenerator = gsl_rng_alloc(generatorType);
      //TODO - const memory leak here gsl_rng_free should be called somwhere
      gsl_rng_set(gslRandomNumberGenerator, seed);
      isGSLInitialized = true;
    }
}
#endif //GSL_AVAILABLE

void EvolFunctions::initialize(int seed)
{
    if(!isInitialized)
    {
        srand(seed);
        isInitialized = true;
    }
}

double EvolFunctions::random()
{
    initialize();
    return (double)rand()/RAND_MAX;
}

int EvolFunctions::random(int begin, int end)
{
    initialize();
    return rand()%(end-begin+1)+begin;
}

#ifdef GSL_AVAILABLE
double EvolFunctions::gaussRandom(double EX, double sigma)
{
  initializeGSL();
  return gsl_ran_gaussian(gslRandomNumberGenerator, sigma) + EX;
}
#endif //GSL_AVAILABLE

} /* end of evol namespace */
