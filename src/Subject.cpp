#include "Subject.hpp"
#include <stdexcept>

namespace evol
{

std::shared_ptr<Subject> Subject::crossWith(std::shared_ptr<Subject> &subject)
{
    /* not tested yet */
    for( std::shared_ptr<Chromosome> chromosome : this->chromosomes)
    {
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
