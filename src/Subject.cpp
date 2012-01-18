#include "Subject.hpp"
#include <stdexcept>
#include <iostream>

namespace evol
{

SubjectPtr Subject::crossWith(SubjectPtr &subject) const throw (SubjectCrossException)
{
    SubjectPtr returnSubject;
    if(this->chromosomes.size() != subject->chromosomes.size())
    {
        throw SubjectCrossException(this->chromosomes.size(),subject->chromosomes.size());
    }

    returnSubject = SubjectPtr(subject->clone());
    returnSubject->clearChromosomes();

    std::vector< ChromosomePtr >::const_iterator iter = this->chromosomes.begin();
    std::vector< ChromosomePtr >::const_iterator iter2 = subject->chromosomes.begin();

    std::vector< ChromosomePtr >::const_iterator endIterator = this->chromosomes.end();
    for(;iter != endIterator;++iter,++iter2)
    {
        if(typeid(*iter) != typeid(*iter2))
        {
            throw ChromosomeCrossException(typeid(*iter).name(),typeid(*iter2).name());
        }
        returnSubject->addChromosome(((*iter)->crossWith(*iter2))); 
    }
    return returnSubject;
}

void Subject::mutate()
{
    std::vector< ChromosomePtr >::const_iterator iter = this->chromosomes.begin();

    std::vector< ChromosomePtr >::const_iterator endIterator = this->chromosomes.end();
    for(;iter != endIterator;++iter)
    {
        (*iter)->mutate();
    }
}

void Subject::addChromosome(ChromosomePtr chromosome) throw(ChromosomeAllocationException)
{
    try
    {
        this->chromosomes.push_back(chromosome);
    }
    catch(const std::bad_alloc &e)
    {
        throw ChromosomeAllocationException(e);
    }
}

ChromosomePtr Subject::getChromosome(unsigned int id) const throw(ChromosomeOutOfBoundException)
{
    try
    {
        return ChromosomePtr(this->chromosomes.at(id));
    }
    catch(const std::out_of_range &e)
    {
        throw ChromosomeOutOfBoundException(e);
    }
}

void Subject::replaceChromosomes(std::vector< ChromosomePtr > &chromosomes)
{
    /* swap content of current chromosomes vector with given one */
    this->chromosomes.swap(chromosomes);

}

void Subject::clearChromosomes()
{
    this->chromosomes.clear();
    return;
}

} /* end of evol namespace */
