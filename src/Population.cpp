#include "Population.hpp"
#include "debug.h"

namespace
{

Population::Population( const FitnessFunction &goal ) : goal(goal)
{ /*nothing to be done*/ }

virtual void Population::start() throw ( SubjectOutOfBoundException )
{
    pickStartGeneration();
    auto_ptr<FitnessFunction> currentBestFF = goal.clone();
    try
    {
        currentBestFF.calculate( subject.get(bestId) );
    }
    catch( const std::out_of_range &e )
    {
        throw SubjectOutOfBoundException(e);
    }
        
    while( *currentBestFF < *goal )
    {
        T( "Obecna populacja", subjects );       
        crossoverSubjects();
        mutateSubjects();
        selectSubjects();        

        /*current best*/
        try
        {
            currentBestFF.calculate( subject.get(bestId) );
        }
        catch( const std::out_of_range &e )
        {
            throw SubjectOutOfBoundException(e);
        }   
    }
}

virtual void pickStartGeneration()
{
   
}

}/*end of namespace*/
