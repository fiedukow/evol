#include "Population.hpp"
#include "debug.h"
#include "EvolFunctions.hpp"

namespace evol
{

Population::Population( const FitnessFunction &goal_, 
                        const std::shared_ptr< Subject > prototype_, 
                        unsigned int populationSize_ ) 
                        : goal(goal_), populationSize(populationSize_),
                          subjectPrototype( prototype_->clone() )
{
    M("Obiekt klasy Population jest tworzony");
}

void Population::start() throw ( SubjectOutOfBoundException )
{
    /*default values*/
    bestId = 0;
    crossFactor = 1.0; 

    pickStartGeneration();
    currentBestFF = this->goal.clone();
    try
    {
        currentBestFF->calculate( *subjects[bestId] );
    }
    catch( const std::out_of_range &e )
    {
        throw SubjectOutOfBoundException(e);
    }
        
    while( !isGoalAchieved() )
    {
        T( "Obecna populacja", subjects );       
        C( goal > *currentBestFF );
        C( subjects.size() == populationSize );
        crossoverSubjects();
        mutateSubjects();
        selectSubjects();        

        /*current best*/
        try
        {
            currentBestFF->calculate( *subjects[bestId] );
        }
        catch( const std::out_of_range &e )
        {
            throw SubjectOutOfBoundException(e);
        }   
    }
}

void Population::pickStartGeneration()
{
    M("Losuje poczatkowa populacje");
    for( int i = 0; i < populationSize; ++i )
    {
        std::shared_ptr< Subject > currentSubject = subjectPrototype->clone();        
        currentSubject->setInitialValue();
        subjects.push_back(currentSubject);        
    } 
}

void Population::mutateSubjects()
{
    for( std::shared_ptr< Subject > currentSubject : subjects )
    {
        if( EvolFunctions::random() < 0.2 ) /*20% chance*/
            currentSubject->mutate();
    }
}

void Population::crossoverSubjects()
{
    for( int i = 0; i < crossFactor*populationSize; ++i )
    {
        unsigned int first  = EvolFunctions::random( 0, subjects.size()-1 );
        unsigned int second = EvolFunctions::random( 0, subjects.size()-2 );
        if( second == first ) second++;
        subjects[first]->crossWith( subjects[second] );
    }
}

bool Population::isGoalAchieved()
{
    return ( currentBestFF!=NULL && this->goal <= *currentBestFF );
}


void registerObserver( std::shared_ptr<SelectionObserver> observer )
{
    /* @FIXME implement this */
}

void registerObserver( std::shared_ptr<MutateObserver> observer )
{
    /* @FIXME implement this */
}

void registerObserver( std::shared_ptr<MutateObserver> observer )
{
    /* @FIXME implement this */
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
