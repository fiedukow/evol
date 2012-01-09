#include "Population.hpp"
#include "debug.h"
#include "EvolFunctions.hpp"

namespace evol
{

Population::Population( const FitnessFunction &goal_, 
                        const SubjectPtr prototype_, 
                        unsigned int populationSize_ ) 
                        : goal(goal_), populationSize(populationSize_),
                          subjectPrototype( prototype_->clone() )
{
    M("Obiekt klasy Population jest tworzony");
}

void Population::start() throw ( SubjectOutOfBoundException )
{
    M("Population::start() called.");
    /*default values*/
    this->bestId = 0;
    this->crossFactor = 1.0; 

    pickStartGeneration();
    currentBestFF = this->goal.clone();
    try
    {
        currentBestFF->calculate( *subjects[this->bestId] );
    }
    catch( const std::out_of_range &e )
    {
        M("out_of_range exception occured. Throwing SubjectOutOfBoundException.");
        throw SubjectOutOfBoundException(e);
    }
        
    while( !isGoalAchieved() )
    {
        T( "Obecna populacja", this->subjects );       
        C( goal > *currentBestFF );
        C( subjects.size() == populationSize );
        crossoverSubjects();
        mutateSubjects();
        selectSubjects();        

        /*current best*/
        try
        {
            currentBestFF->calculate( *(this->subjects[this->bestId]) );
        }
        catch( const std::out_of_range &e )
        {
            M("out_of_range exception occured. Throwing SubjectOutOfBoundException.");
            throw SubjectOutOfBoundException(e);
        }   
    }
}

void Population::pickStartGeneration()
{
    M("Population::pickStartGeneration() called.");
    for( unsigned int i = 0; i < populationSize; ++i )
    {
        std::shared_ptr< Subject > currentSubject = subjectPrototype->clone();        
        currentSubject->setInitialValue();
        subjects.push_back(currentSubject);        
    }
    T( "Current population", this->subjects );
}

void Population::mutateSubjects()
{
    for( std::shared_ptr< Subject > currentSubject : this->subjects )
    {
        if( EvolFunctions::random() < 0.2 ) /*20% chance*/
            currentSubject->mutate();
    }
}

void Population::crossoverSubjects()
{
    M("Population::crossoverSubjects() called.");
    for( int i = 0; i < this->crossFactor*populationSize; ++i )
    {
        unsigned int first  = EvolFunctions::random( 0, subjects.size()-1 );
        unsigned int second = EvolFunctions::random( 0, subjects.size()-2 );
        if( second == first ) ++second;
        subjects[first]->crossWith( this->subjects[second] );
    }
    T( "Current population", this->subjects );
}

bool Population::isGoalAchieved()
{
    M("Population::isGoalAchieved() called.");
    V("currentBestFF",currentBestFF);
    return ( currentBestFF!=NULL && this->goal <= *currentBestFF );
}

/* observers part */

void Population::registerObserver( SObserverPtr toRegister )
{
    M("Population::registerObserver() called.");
    selectionObservers.push_back(toRegister);
}

void Population::registerObserver( MObserverPtr toRegister )
{
    M("Population::registerObserver() called.");
    mutateObservers.push_back(toRegister);
}

void Population::registerObserver( CObserverPtr toRegister )
{
    M("Population::registerObserver() called.");
    crossoverObservers.push_back(toRegister);
}

void Population::notifySelection()
{
    std::vector<SObserverPtr>::const_iterator iter = selectionObservers.begin();
    std::vector<SObserverPtr>::const_iterator endIterator = selectionObservers.end();

    for(;iter != endIterator;++iter)
    {
        (*iter)->update(*this);
    }
}

void Population::notifyMutate()
{
    std::vector<MObserverPtr>::const_iterator iter = mutateObservers.begin();
    std::vector<MObserverPtr>::const_iterator endIterator = mutateObservers.end();

    for(;iter != endIterator;++iter)
    {
        (*iter)->update(*this);
    }
}

void Population::notifyCrossover()
{
    std::vector<CObserverPtr>::const_iterator iter = crossoverObservers.begin();
    std::vector<CObserverPtr>::const_iterator endIterator = crossoverObservers.end();

    for(;iter != endIterator;++iter)
    {
        (*iter)->update(*this);
    }
}

/*
 * FitnessFunction implementation
 */

bool FitnessFunction::operator >= ( const FitnessFunction& toCompare ) const
{
    return ( *this > toCompare || *this == toCompare );
}

bool FitnessFunction::operator <  ( const FitnessFunction& toCompare ) const
{
    return ( *this < toCompare || *this == toCompare );
}

bool FitnessFunction::operator <= ( const FitnessFunction& toCompare ) const
{
    return !( *this > toCompare );
}

bool FitnessFunction::operator != ( const FitnessFunction& toCompare ) const
{
    return !( *this == toCompare );
}


}/*end of namespace*/
