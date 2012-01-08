#ifndef _POPULATION_HPP_
#define _POPULATION_HPP_

/**
 * Population class.
 * It's main class of evol library. It provides main loop of genetic algorithms and 
 * some standard implementation of it. It can be derived or extended using
 * observers sytstem which allows to take some additional action without changing
 * any part of standard code.
 * Feel free to override virtual functions of this class, but do it at your own risk.
 * Overriding registerObserver and notify* method is NOT recommended.
 * 
 * @author Andrzej 'Yester' Fiedukow
 * @author Maciej 'mac' Grzybek
 */
class Population
{
    public:

    /**
     * Do main algorithm loop
     */
    virtual void start();

    /*
     * Register observer which will be notified at the beginning of Selection phase
     *
     * @param observer - observer object smart pointer to be registered.
     */
    void registerObserver( std::shared_ptr<SelectionObserver> observer );

    /*
     * Register observer which will be notified at the beginning of Mutate phase
     *
     * @param observer - observer object smart pointer to be registered.
     */
    void registerObserver( std::shared_ptr<MutateObserver> observer );

    /*
     * Register observer which will be notified at the beginning of Crossover phase
     * 
     * @param observer - observer object smart pointer to be registered.
     */
    void registerObserver( std::shared_ptr<CrossoverObserver> observer);
   
    protected:
    
    /** 
     * Pick first generation (in most cases random) 
     */
    virtual void pickStartGeneration();

    /**
     * Selection phase - choose only the best subjects
     */
    virtual void selectSubjects();
    
    /** 
     * Reproduction phase - generate some new Subjects
     */
    virtual void reproductSubjects();

    /**
     * Mutation phase - mutate Subjects
     */
    virtual void mutateSubjects();

    /**
     * Crossover phase - crossover Subjects with each other
     */
    virtual void crossoverSubjects();
    
    /**
     * Check algorithm stop condition.
     *
     * @return true if FitnessFunction condition is achived
     */
    virtual bool isGoalAchieved();

    /**
     * Notify all Selection observers that Selection Phase starts.
     * It SHOULD be called at the beginnig of Selection Phase 
     * or observer system will not work as it was designed.
     */
    void notifySelection();

    /**
     * Notify all Mutate observers that Mutate Phase starts.
     * It SHOULD be called at the beginnig of Mutate Phase 
     * or observer system will not work as it was desinged.
     */
    void notifyMutate();

    /**
     * Notify all Crossover observers that Crossover Phase starts.
     * It SHOULD be called at the beginnig of Crossover Phase 
     * or observer system will not work as it was designed.
     */
    void notifyCrossover(); 
}

/**
 * @interface FitnessFunction
 * 
 * FitnessFunction class should allow to compare value of FF for 2 Subjects.
 * This class SHOULD be able to calculate and keep FF value to compare with.
 * The most important part of this class is operator> method which compares
 * two FF values.
 *
 * @note This class is not only functor but also kind a container for FF value.
 * 
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek 
 */
class FitnessFunction
{
    public:

    /**
     * Compere current object with other FF object.
     *
     * @param toCompare - const reference to other FF value.
     * @return true if current FF is BETTER (whatever that means) than toCompare.
     */
    virtual bool operator>( const FitnessFunction& toCompare );    

    /**
     * Prepare FF object to compare using Subject object which provides necessary informations. 
     * Typical implementation will calculate & save some function value.
     * 
     * @param toCalculate - Subject we want to "calculate" FF value of.
     */
    virtual void calculate( const Subject& toCalculate );
}

#endif
