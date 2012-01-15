#ifndef _POPULATION_HPP_
#define _POPULATION_HPP_
#include <vector>
#include <memory>
#include "Subject.hpp"
#include "Observer.hpp"

namespace evol
{

class FitnessFunction;

typedef std::shared_ptr<FitnessFunction> FFPtr;

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
    private:
    /*
     * Reference value to compare with.
     */
    const FitnessFunction &goal; 
    FFPtr currentBestFF;
    bool stop;
    unsigned int bestId;
    double crossFactor;
    unsigned int populationSize;
    const SubjectPtr subjectPrototype;    
    std::vector< SubjectPtr > subjects;

    /* observers piece of code */

    /* container for selection observers */
    std::vector< SObserverPtr > selectionObservers;
    /* container for mutate observers */
    std::vector< MObserverPtr > mutateObservers;
    /* container for crossover observers */
    std::vector< CObserverPtr > crossoverObservers;

    public:
    
    /**
     * Create Population with goal given by argument.
     * @param goal - FitnessFunction object reference beeing reference value to compre with.
     * @param prototype - Prototype of function which is used to create all subjects.
     * @param populationSize - maximal populaion size after selection phase
     */
   Population(const FitnessFunction &goal_, 
              const SubjectPtr prototype_, 
              unsigned int populationSize_ );


    /**
     * Do main algorithm loop
     */
    virtual SubjectPtr start() throw ( SubjectOutOfBoundException );


    /*
     * Register observer which will be notify at the begining of Selection phase
     *
     * @param toRegister - observer object pointer to be register.
     */
    void registerObserver( SObserverPtr toRegister );

    /*
     * Register observer which will be notify at the begining of Mutate phase
     *
     * @param toRegister - observer object pointer to be register.
     */
    void registerObserver( MObserverPtr toRegister );

    /*
     * Register observer which will be notify at the begining of Crossover phase
     * 
     * @param toRegister - observer object pointer to be register.
     */
    void registerObserver( CObserverPtr toRegister );

    /*
     * Method stops main loop of algorithm.
     */
    void stopLoop( );
   
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

    /**
     * Adds another subject to collection
     */
    void addSubject( SubjectPtr toAdd );
};


/*
 * @FIXME - isnt any better place for that?
 */
class SubjectComparator
{
friend class Population;
private:
    const FitnessFunction& prototype;

    /*
     * Create comparator with given FF prototype
     */
    SubjectComparator( const FitnessFunction& goal );

public:

    /*
     * Compare pair of Subjects
     *
     * @param SubjectPtr first
     * @param SubjectPtr second
     * @return true if first Subject should be before second in collection
     */
    bool operator() ( const SubjectPtr first, const SubjectPtr second );
};



/**
 * @interface FitnessFunction
 * 
 * FitnessFunction class should allow to compare value of FF for 2 Subjects.
 * This class SHOULD be able to calculate and keep FF value to compare with.
 * The most important part of this class is operator> method with compare
 * two FF values.
 *
 * @note This class is not only functor but also kinda container for FF value.
 * 
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek 
 */
class FitnessFunction
{
    public:

    /**
     * Compare current object with other FF object. You HAVE TO overwrite > and == operator
     * to use basic class functionality. All other comparation operators are "implicit" :-)
     *
     * @param toCompare - const reference to other FF value.
     * @return true if current FF is BETTER (whatever that means) then toCompare.
     */
    virtual bool operator >  ( const FitnessFunction& toCompare ) const = 0;    
    virtual bool operator == ( const FitnessFunction& toCompare ) const = 0;    
    
    /*
     * Guess what?
     */
    virtual bool operator >= ( const FitnessFunction& toCompare ) const;    
    virtual bool operator <  ( const FitnessFunction& toCompare ) const;    
    virtual bool operator <= ( const FitnessFunction& toCompare ) const;    
    virtual bool operator != ( const FitnessFunction& toCompare ) const;    
    
    virtual void drukuj() = 0;

    /**
     * Prepare FF object to compare using Subject object which provides necessary informations. 
     * Typical implementation will calculate & save some function value.
     * 
     * @param toCalculate - Subject for which we want to "calculate" FF value.
     */
    virtual void calculate( const Subject& toCalculate ) = 0;

    /**
     * Clone this object - create it deep copy. Used to "type recognize" in Population.
     * 
     * @return smart pointer to deep copy of object
     */
    virtual std::unique_ptr< FitnessFunction > clone() const = 0; 
};

}/*end of namespace*/

#endif
