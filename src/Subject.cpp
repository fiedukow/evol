#include "Subject.hpp"
#include <stdexcept>

namespace evol
{

SubjectPtr Subject::crossWith(SubjectPtr &subject) const throw (SubjectCrossException)
{
    M("Subject::crossWith called.");
    SubjectPtr returnSubject;
    /* not tested yet */
    if(this->chromosomes.size() != subject->chromosomes.size())
    {
        M("Chromosomes containers size mismatch.");
        throw SubjectCrossException(this->chromosomes.size(),subject->chromosomes.size());
    }

    M("Clonning subject.");
    returnSubject = SubjectPtr(subject->clone());

    std::vector< ChromosomePtr >::const_iterator iter = this->chromosomes.begin();
    std::vector< ChromosomePtr >::const_iterator iter2 = subject->chromosomes.begin();

    std::vector< ChromosomePtr >::const_iterator endIterator = this->chromosomes.end();
    for(;iter != endIterator;++iter,++iter2)
    {
        if(typeid(*iter) != typeid(*iter2))
        {
            M("Chromosomes types mismatch.");
            throw ChromosomeCrossException(typeid(*iter).name(),typeid(*iter2).name());
        }
        M("Adding chromosome (product of crossover)");
        returnSubject->addChromosome(((*iter)->crossWith(*iter2))); /* test it */
    }
    return returnSubject;
}

void Subject::mutate()
{
    M("Subject::mutate called.");
    std::vector< ChromosomePtr >::const_iterator iter = this->chromosomes.begin();

    std::vector< ChromosomePtr >::const_iterator endIterator = this->chromosomes.end();
    for(;iter != endIterator;++iter)
    {
        (*iter)->mutate();
    }
}

void Subject::addChromosome(ChromosomePtr chromosome) throw(ChromosomeAllocationException)
{
    M("Subject::addChromosome() called.");
    try
    {
        this->chromosomes.push_back(chromosome);
    }
    catch(const std::bad_alloc &e)
    {
        M("std::bad_alloc occured. Throwing ChromosomeAllocationException.");
        throw ChromosomeAllocationException(e);
    }
}

ChromosomePtr Subject::getChromosome(unsigned int id) const throw(ChromosomeOutOfBoundException)
{
    M("Subject::getChromosome() called.");
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
    M("Subject::replaceChromosomes called.");
    /* swap content of current chromosomes vector with given one */
    this->chromosomes.swap(chromosomes);
}

} /* end of evol namespace */
