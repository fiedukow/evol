#ifndef _OBSERVERS_HPP_
#define _OBSERVERS_HPP_

class Population;


/**
*/

/**
 * Abstract class (interface) for Selection observer,
 * which is fired (notified) at the beginning of selection process in Population.
 *
 *  @author Andrzej 'Yester' Fieudkowicz
 *  @author Maciej 'mac' Grzybek
 */
class SelectionObserver
{
    public:
    /**
     * Method called by population, which notifies observer of action.
     * @param population Population reference, which notifies observer.
     * @return void Nothing is returned.
     */
    virtual void update(Population& population);
};

/**
 * Abstract class (interface) for Mutate observer,
 * which is fired (notified) at the beginning of mutation process in Population.
 * 
 *  @author Andrzej 'Yester' Fieudkowicz
 *  @author Maciej 'mac' Grzybek
 */
class MutateObserver
{
    public:
    /**
     * Method called by population, which notifies observer of action.
     * @param population Population reference, which notifies observer.
     * @return void Nothing is returned.
     */
    virtual void update(Population& population);
};

/**
 * Abstract class (interface) for Crossover observer,
 * which is fired (notified) at the beginning of crossover process in Population.
 *
 *  @author Andrzej 'Yester' Fieudkowicz
 *  @author Maciej 'mac' Grzybek
 */
class CrossoverObserver
{
    public:
    /**
     * Method called by population, which notifies observer of action.
     * @param population Population reference, which notifies observer.
     * @return void Nothing is returned.
     */
    virtual void update(Population& population);
};

#endif
