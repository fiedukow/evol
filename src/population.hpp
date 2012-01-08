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
     * Register observer which will be notify at the begining of Selection phase
     *
     * @param observer - observer object pointer to be register.
     */
    void registerObserver( std::shared_ptr<SelectionObserver> observer );

    /*
     * Register observer which will be notify at the begining of Mutate phase
     *
     * @param observer - observer object pointer to be register.
     */
    void registerObserver( std::shared_ptr<MutateObserver> observer );

    /*
     * Register observer which will be notify at the begining of Crossover phase
     * 
     * @param observer - observer object pointer to be register.
     */
    void registerObserver( std::shared_ptr<CrossoverObserver> observer);
   
    protected:
    
    /** 
     * Pick first generation (generaly random) 
     */
    virtual void pickStartGeneration();

    /**
     * Selection phase - leave only best
     */
    virtual void selectSubjects();
    
    /** 
     * Reproduction phase - generate some new Subjects
     */
    virtual void reproductSubjects();

    /**
     * Mutation phase - mutate some element which eachother 
     */
    virtual void mutateSubjects();

    /**
     * Crossover phase - each chromosome can be crossover 
     */
    virtual void crossoverSubjects();
    
    /**
     * Check if the algoritm should end because of goal achived.
     *
     * @return true if FitnessFunction condition is achived
     */
    virtual bool isGoalAchieved();

    /**
     * Notify all Selection observers that Selection Phase starts.
     * It SHOULD be called at the beginig of Selection Phase 
     * or observer system will not work as it was designed.
     */
    void notifySelection();

    /**
     * Notify all Mutate observers that Mutate Phase starts.
     * It SHOULD be called at the beginig of Mutate Phase 
     * or observer system will not work as it was desinged.
     */
    void notifyMutate();

    /**
     * Notify all Crossover observers that Crossover Phase starts.
     * It SHOULD be called at the beginig of Crossover Phase 
     * or observer system will not work as it was designed.
     */
    void notifyCrossover(); 
}
#endif
