#ifndef _EVOL_FUNCTIONS_H_
#define _EVOL_FUNCTIONS_H_

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
    /*     
     * @return random value between 0 and 1
     */
    static double random();

    /*
     * @param begin
     * @param end
     * @return random integral value between 'begin' and 'end'
     */
    static int random( int begin, int end );
};

}

#endif
