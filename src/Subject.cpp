#include "Subject.hpp"
#include <stdexcept>

namespace evol
{

SubjectPtr Subject::crossWith(SubjectPtr &subject) const throw (SubjectCrossException)
{
    /* not tested yet */
    Subject *returnSubject;
    if(this->chromosomes.size() != subject->chromosomes.size())
    {
        throw SubjectCrossException(this->chromosomes.size(),subject->chromosomes.size());
    }

    std::vector< ChromosomePtr >::const_iterator iter = this->chromosomes.begin();
    std::vector< ChromosomePtr >::const_iterator iter2 = subject->chromosomes.begin();

    std::vector< ChromosomePtr >::const_iterator endIterator = this->chromosomes.end();
    if(this->chromosomes.size() > 0) /* if there is any chromosome in current subject */
    {
        returnSubject = new Subject(); /* create result subject, to return */
    }
    for(;iter != endIterator;++iter,++iter2)
    {
        if(typeid(*iter) != typeid(*iter2))
        {
            delete returnSubject; /* if exception occured, delete subject to be returned */
            throw ChromosomeCrossException(typeid(*iter).name(),typeid(*iter2).name());
        }
        returnSubject->addChromosome(((*iter)->crossWith(*iter2))); /* test it */
    }
    return SubjectPtr(subject);
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

ChromosomePtr Subject::getChromosome(unsigned int id) throw(ChromosomeOutOfBoundException)
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

SubjectPtr Subject::clone()
{
    /* @FIXME implement this */
    
    std::vector< ChromosomePtr > newChromosomes;

    std::vector< ChromosomePtr >::const_iterator iter = this->chromosomes.begin();
    std::vector< ChromosomePtr >::const_iterator endIterator = this->chromosomes.end();

    for(;iter != endIterator; ++iter)
    {
        newChromosomes.push_back(*iter);
    }

    Subject *newSubject = new Subject();
    newSubject->replaceChromosomes(newChromosomes);
    return SubjectPtr(newSubject);
}

} /* end of evol namespace */
