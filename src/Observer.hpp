#ifndef _OBSERVERS_HPP_
#define _OBSERVERS_HPP_

#include <memory>

namespace evol
{

class Population;

class NewGenerationObserver;
class SelectionObserver;
class MutateObserver;
class CrossoverObserver;
class DuplicateObserver;

typedef std::shared_ptr<NewGenerationObserver> NObserverPtr;
typedef std::shared_ptr<SelectionObserver> SObserverPtr;
typedef std::shared_ptr<MutateObserver> MObserverPtr;
typedef std::shared_ptr<CrossoverObserver> CObserverPtr;
typedef std::shared_ptr<DuplicateObserver> DObserverPtr;

/**
 * Abstract class (interface) for Selection observer,
 * which is fired (notified) at the beginning of selection process in Population.
 *
 *  @author Andrzej 'Yester' Fieudkowicz
 *  @author Maciej 'mac' Grzybek
 */
class NewGenerationObserver
{
    public:
    /**
     * Method called by population, which notifies observer of action.
     * @param population Population reference, which notifies observer.
     * @return void Nothing is returned.
     */
    virtual void update(Population& population) = 0;
};

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
    virtual void update(Population& population) = 0;
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
    virtual void update(Population& population) = 0;
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
    virtual void update(Population& population) = 0;
};

/**
 * Abstract class (interface) for Duplicate observer,
 * which is fired (notified) at the beginning of duplicate process in Population.
 *
 *  @author Andrzej 'Yester' Fieudkowicz
 *  @author Maciej 'mac' Grzybek
 */
class DuplicateObserver
{
    public:
    /**
     * Method called by population, which notifies observer of action.
     * @param population Population reference, which notifies observer.
     * @return void Nothing is returned
     */
    virtual void update(Population& population) = 0;
};

} /* end of evol namespace */

#endif
