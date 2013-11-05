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
    /**
     * Reference value to compare with.
     */
    const FitnessFunction &goal; 
    /**
     * The best FitnessFunction value for now
     */
    FFPtr currentBestFF;
    /**
     * If you want you can modyfi this field to use other then first element
     * of population vector as the place for best element
     */
    unsigned int bestId;
    /**
     * How much pairs in any generation should be created (each pair give one child)
     * eg. The 1.0 value (means 100%) implies that there will be exacly as much children 
     *      in any population as they parrents number.
     */
    double crossFactor;
    /**
     * How much elements should be duplicated in duplication phase related to base size.
     * eg. The 1.0 value (means 100%) implies that there will be populationSize clones
     *     added to population.
     */
    double duplicationRate;
    /**
     * What is the chance for mutation of every single Subject in every single generation
     * (0 to 1 is proper value but everything more then 1
     * is 100% and below zero is 0% chance)    
     */
    double mutationChance;
    /**
     *  Size of population after selection. Between crossover and selection it can
     *  much more (1+crossFactor)*populationSize - to be correct.
     */
    unsigned int populationSize;
    /**
     *  Prototype of subject - used to create new "random" elements. 
     *  It provides possibilty of creation element of the same derieved 
     *      type it was at the beginning.  
     *  See informations about prototype design pattern
     */
    const SubjectPtr subjectPrototype;    
    /**
     * Containt all current subjects.
     */
    std::vector< SubjectPtr > subjects;
    /**
     * If this variable is true the main loop will break even if the 
     * goal wasnt achieved yet. Can be used in observers for example.
     */
    bool stop;


    /* observers piece of code */

    /**
     * container for new generation observers 
     */
    std::vector< NObserverPtr > newGenerationObservers;

    /**
     * container for selection observers 
     */
    std::vector< SObserverPtr > selectionObservers;

    /**
     * container for mutate observers 
     */
    std::vector< MObserverPtr > mutateObservers;

    /**
     *  container for crossover observers 
     */
    std::vector< CObserverPtr > crossoverObservers;

    /**
     *  container for duplicate observers
     */
    std::vector< DObserverPtr > duplicateObservers;

    public:
    
    /**
     * Create Population with goal given by argument.
     * @param goal - FitnessFunction object reference beeing reference value to compre with.
     * @param prototype - Prototype of function which is used to create all subjects.
     * @param populationSize - maximal populaion size after selection phase
     * @param mutationChance - chance for mutation of every single Subject in any genartion.
     */
   Population(const FitnessFunction &goal_, 
              const SubjectPtr prototype_, 
              unsigned int populationSize_, 
              double mutationChance_, 
              double crossFactor_,
              double duplicationRate_);


    /**
     * Do main algorithm loop
     */
    virtual SubjectPtr start() throw ( SubjectOutOfBoundException );

    /**
     * Register observer which will be notified at the beginning of new generation cycle
     *
     * @param toRegister - observer object pointer to be registered.
     */
    void registerObserver( NObserverPtr toRegister );

    /**
     * Register observer which will be notify at the begining of Selection phase
     *
     * @param toRegister - observer object pointer to be register.
     */
    void registerObserver( SObserverPtr toRegister );

    /**
     * Register observer which will be notify at the begining of Mutate phase
     *
     * @param toRegister - observer object pointer to be register.
     */
    void registerObserver( MObserverPtr toRegister );

    /**
     * Register observer which will be notify at the begining of Crossover phase
     *
     * @param toRegister - observer object pointer to be register.
     */
    void registerObserver( CObserverPtr toRegister );

    /**
     * Register observer which will be notify at the begining of Duplicate phase
     *
     * @param toRegister - observer object pointer to be register.
     */
    void registerObserver( DObserverPtr toRegister );

    /**
     * Method stops main loop of algorithm.
     * It set stop variable.
     */
    void stopLoop( );

    /**
     *  Simple mutationChance getter
     *  @return - mutation chance (value between 0 - 1 )
     */
    double getMutationChance();

    /**
     *  Simple CrossFactor getter
     *  @return - crossFactor
     */
    double getCrossFactor();
   
    /**
     *  Simple mutationChance setter
     *  @param double newMutationChance - new possibilty of mutation     
     */ 
    void setMutationChance( double newMutationChance );

    /**
     *  Simple crossFactor setter
     *  @param newCorssFactor - new crossFactor value
     */
    void setCrossFactor   ( double newCrossFactor    );
   
    /*
     * Getter for subjects vector.
     */
    std::vector< SubjectPtr >& getSubjects();

    /**
     * Getter for currentBestFF.
     */
    FFPtr getCurrentBestFF();

    /**
     * Getter for bestId.
     */
    unsigned int getBestId();

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
     * Duplicate phase - creating clones of some elements in current population
     */
    virtual void duplicateSubjects();
    
    /**
     * Check if the algoritm should end because of goal achived.
     *
     * @return true if FitnessFunction condition is achived
     */
    virtual bool isGoalAchieved();

    /**
     * Notify all New Generation observers that New Generation starts.
     * It SHOULD be called at the beginnig of new generation cycle
     * or observer system will not work as it was designed.
     */
    void notifyNewGeneration();

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
     * Notify all Duplication observers that Duplication Phase starts.
     * It SHOULD be called at the begining of Duplication Phase
     * or observer system will not work as it was designed.
     */
    void notifyDuplication();

    /**
     * Adds another subject to collection
     */
    void addSubject( SubjectPtr toAdd );
};


/*
 * This class allow to sort subjects using std::algorithm (sort)
 * This is functor witch can compare two subject ptr's using proper FF. 
 */
class SubjectComparator
{
friend class Population;
private:
    /**
     * Contains prototype of FF witch will be used to compare subjects
     */
    const FitnessFunction& prototype;

    /**
     * Create comparator with given FF prototype
     */
    SubjectComparator( const FitnessFunction& goal );

public:

    /**
     * Compare pair of SubjectsPtr (but it comapres VALUES not just pointers)
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
   
    /**
     * It prints the result - whatever that means
     */
    virtual void print() = 0;    

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
