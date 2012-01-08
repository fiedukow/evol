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
//    this->subjectPrototype = prototype_->clone();
}

void Population::start() throw ( SubjectOutOfBoundException )
{
    pickStartGeneration();
    std::auto_ptr<FitnessFunction> currentBestFF = goal.clone();
    try
    {
        currentBestFF->calculate( *subjects[bestId] );
    }
    catch( const std::out_of_range &e )
    {
        throw SubjectOutOfBoundException(e);
    }
        
    while( goal > *currentBestFF )
    {
        T( "Obecna populacja", subjects );       
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
    for( int i = 0; i < populationSize; ++i )
    {
        std::shared_ptr< Subject > currentSubject = subjectPrototype->clone();        
        currentSubject->setInitialValue();
        subjects.push_back(currentSubject);        
    } 
}



}/*end of namespace*/
