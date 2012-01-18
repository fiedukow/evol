#ifndef _EVOL_FUNCTIONS_H_
#define _EVOL_FUNCTIONS_H_
#include <memory>
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

    /** 
     * Initialize seed - if needed
     */
    static void initialize();

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
    static double abs( double valueToAbs );

    /**
     * Cast shared_ptr of base class to concret derieved class
     * Use only when you are sure you know class of the object
     */
    template< class fromClass, class targetClass >
    static targetClass* ptr_cast( fromClass& what ) 
    {
        return ((targetClass*) (&(*(what))));
    }
};

} /* end of evol namespace */

#endif
