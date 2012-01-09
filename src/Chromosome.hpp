#ifndef _CHROMOSOME_HPP_
#define _CHROMOSOME_HPP_

#include "EvolException.hpp"
#include <memory>

namespace evol
{

class Chromosome;

typedef std::shared_ptr<Chromosome> ChromosomePtr;

/**
 * Abstract class (interface) for Chromosome (Subject's attribute) representation
 *
 *  @author Andrzej 'Yester' Fieudkowicz
 *  @author Maciej 'mac' Grzybek
 */
class Chromosome
{
    public:

    /**
     * Do the crossover with given chromosome
     * @param chromosome - smart pointer to Chromosome which dereferences to Chromosome to crossover with.
     * @return smart pointer to Chromosome which represents product of crossover current chromosome with chromosome from argument, which is new Chromosome.
     */
    virtual ChromosomePtr crossWith(ChromosomePtr toCross ) const = 0;

    /**
     * Do the mutation (self-modification) of current Chromosome
     */
    virtual void mutate() = 0;
};

} /* end of evol namespace */

#endif
