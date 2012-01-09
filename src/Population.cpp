#include "Population.hpp"
#include "debug.h"

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
    pickStartGeneration();
    this.currentBestFF = goal.clone();
    try
    {
        currentBestFF->calculate( *subjects[bestId] );
    }
    catch( const std::out_of_range &e )
    {
        throw SubjectOutOfBoundException(e);
    }
        
    while( !isGoalAchived() )
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

void Population::reproductSubjects()
{
    for( std::shared_ptr< Subject > currentSubject : subjects )
    {
        currentSubject->mutate();
    }
}

void Population::reproductSubjects()
{
    for( int i = 0; i < crossFactor*populationSize; ++i )
    {
        first  = EvolFunctions::random( 0, subjects.size()-1 );
        second = EvolFunctions::random( 0, subjects.size()-2 );
        if( second == first ) second++;
        subjects[first].crossWith( subjects[second] );
    }
}

bool Population::isGoalAchived()
{
    return ( currentBestFF!=NULL && this.goal <= *currentBestFF );
}

}/*end of namespace*/
