#include "Population.hpp"
#include "debug.h"
#include "EvolFunctions.hpp"
#include <algorithm>

#include <iostream>

namespace evol
{

Population::Population( const FitnessFunction &goal_, 
                        const SubjectPtr prototype_, 
                        unsigned int populationSize_,
                        double mutationChance_ ) 
                        : goal(goal_), populationSize(populationSize_),
                          subjectPrototype( prototype_->clone() ), stop(false),
                          mutationChance(mutationChance_)
{
    /*nothign to be done*/
}

SubjectPtr Population::start() throw ( SubjectOutOfBoundException )
{
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
        throw SubjectOutOfBoundException(e);
    }
        
    while( !isGoalAchieved() && !stop )
    {  
        /*TODO: PRINT - observer?*/
        std::cout << "W tym pokoleniu najlepszy wynik to "<<std::endl;
        subjects[0]->drukuj();
        currentBestFF->print();
        std::cout << std::endl;

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
            throw SubjectOutOfBoundException(e);
        }   
    }
    return this->subjects[this->bestId];
}

double Population::getMutationChance()
{
    double result = this->mutationChance;
    if( result > 1 ) result = 1;
    if( result < 0 ) result = 0;
    return result;
}

double Population::getCrossFactor()
{
    return this->crossFactor;
}

void Population::setMutationChance( double newMutationChance )
{
    this->mutationChance = newMutationChance;
}

void Population::setCrossFactor( double newCrossFactor )
{
    this->crossFactor = newCrossFactor;
}

void Population::pickStartGeneration()
{
    for( unsigned int i = 0; i < populationSize; ++i )
    {
        SubjectPtr currentSubject = subjectPrototype->clone();        
        currentSubject->setInitialValue();
        subjects.push_back(currentSubject);        
    }
}

void Population::selectSubjects()
{
    notifySelection();

    for( SubjectPtr sub : subjects )
    {
        std::shared_ptr<FitnessFunction> wynik = goal.clone();
        wynik->calculate( *sub );
    }

    SubjectComparator comparator( goal );
    std::sort (this->subjects.begin(), this->subjects.end(), comparator );
    this->subjects.erase( this->subjects.begin() + this->populationSize,
                          this->subjects.end() );
}

void Population::mutateSubjects()
{
    notifyMutate();
    for( SubjectPtr currentSubject : this->subjects )
    {
        if( EvolFunctions::random() < this->mutationChance ) 
            currentSubject->mutate();
    }
}

void Population::crossoverSubjects()
{
    notifyCrossover();
    for( int i = 0; i < this->crossFactor*populationSize; ++i )
    {
        unsigned int first  = EvolFunctions::random( 0, subjects.size()-1 );
        unsigned int second = EvolFunctions::random( 0, subjects.size()-2 );
        if( second == first ) ++second;
        this->addSubject( subjects[first]->crossWith( this->subjects[second] ) );
    }
}

void Population::stopLoop()
{
    this->stop = true;
}

void Population::addSubject( SubjectPtr toAdd )
{
    this->subjects.push_back( toAdd );
}

bool Population::isGoalAchieved()
{
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
 * SubjectComparator implementation
 */
SubjectComparator::SubjectComparator( const FitnessFunction& goal ) : prototype( goal )
{ }

bool SubjectComparator::operator() ( const SubjectPtr first, const SubjectPtr second )
{
    std::unique_ptr< FitnessFunction > firstResult  = this->prototype.clone();
    firstResult->calculate( *first ); 
    std::unique_ptr< FitnessFunction > secondResult = this->prototype.clone();
    secondResult->calculate( *second );
    return (*firstResult) > (*secondResult);
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
