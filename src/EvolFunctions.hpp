#ifndef _EVOL_FUNCTIONS_H_
#define _EVOL_FUNCTIONS_H_
#include <memory>
#ifdef GSL_AVAILABLE
#include <gsl/gsl_rng.h>
#endif
#include "Chromosome.hpp" 

namespace evol
{
/*
 * Class with static methods for evol library.
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
struct EvolFunctions
{
    /**
     * True if seed is initialized
     */
    static bool isInitialized;

#ifdef GSL_AVAILABLE
    /**
     * True if GSL random generator is created
     */
    static bool isGSLInitialized;

    /**
     * Random number generator for GSL
     */
    static gsl_rng* gslRandomNumberGenerator;
#endif

    /** 
     * Initialize seed - if needed
     */
    static void initialize();

    /**
     * Initialize seed by given number
     */
    static void initialize(int);

#ifdef GSL_AVAILABLE
    /**
     * Creates GSL random number generator 
     * using time(NULL) as seed
     */
    static void initializeGSL();

    /**
     * Creates GSL random number generator
     * using argument as seed
     */
    static void initializeGSL(int);
#endif

    /**
     * @return random value between 0 and 1
     */
    static double random();

    /**
     * @param begin
     * @param end
     * @return random integral value between 'begin' and 'end'
     */
    static int random( int begin, int end );

    /**
     * @param valueToAbs
     * @return ABS of given double value
     */
    template<class numericType>
    numericType abs(numericType valueToAbs)
    {
      return valueToAbs > 0 ? valueToAbs : -valueToAbs;
    }

#ifdef GSL_AVAILABLE
    /**
     * @param EX - expected value
     * @param sigma - standard deviation
     */
    static double gaussRandom(double EX, double sigma);
#endif //GSL_AVAILABLE

    /**
     * Cast shared_ptr of base class to concret derieved class
     * Use only when you are sure you know class of the object
     */
    template< class fromClass, class targetClass >
    static targetClass* ptr_cast( fromClass what ) 
    {
        return ((targetClass*) (&(*(what))));
    }
};

} /* end of evol namespace */

#endif
