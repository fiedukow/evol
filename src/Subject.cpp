#include "Subject.hpp"
#include <stdexcept>

namespace evol
{

std::shared_ptr<Subject> Subject::crossWith(std::shared_ptr<Subject> &subject)
{
    /* not tested yet */
    if(this->chromosomes.size() != subject.chromosomes.size())
    {
        throw SubjectCrossException(this->chromosomes.size(),subject.chromosomes.size());
    }
    std::vector< std::shared_ptr<Chromosome> >::const_iterator endIterator = this->chromosomes.end();
    for( std::vector< std::shared_ptr<Chromosome> >::const_iterator iter = this->chromosomes.begin(), std::vector< std::shared_ptr<Chromosome> >::const_iterator iter2 = subject.begin(); iter != endIterator; ++iter,++iter2)
    {
        if(typeid(*iter) != typeid(*iter2))
        {
            throw ChromosomeCrossException(typeid(*iter).name(),typeid(*iter2).name());
        }
        /* @FIXME implement this */
    }
}

std::shared_ptr<Subject> Subject::mutate()
{
    /* @FIXME implement this */
}

void Subject::addChromosome(std::shared_ptr<Chromosome> &chromosome) throw(ChromosomeAllocationException)
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

std::shared_ptr<Chromosome> Subject::getChromosome(unsigned int id) throw(ChromosomeOutOfBoundException)
{
    try
    {
        return std::shared_ptr<Chromosome>(this->chromosomes.at(id));
    }
    catch(const std::out_of_range &e)
    {
        throw ChromosomeOutOfBoundException(e);
    }
}

void Subject::replaceChromosomes(std::vector< std::shared_ptr<Chromosome> > &chromosomes)
{
    /* @FIXME implement this */
}

std::shared_ptr<Subject> clone()
{
    /* @FIXME implement this */
    
}

} /* end of evol namespace */
