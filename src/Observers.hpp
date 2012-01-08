#ifndef _OBSERVERS_HPP_
#define _OBSERVERS_HPP_

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
