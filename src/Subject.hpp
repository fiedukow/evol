#ifndef _SUBJECTS_HPP_
#define _SUBJECTS_HPP_

#include <vector>
#include <memory>
#include "EvolException.hpp"

namespace evol
{


/**
 * Abstract class (interface) for Chromosome (Subject's attribute) representation
 *
 *  @author Andrzej 'Yester' Fieudkowicz
 *  @author Maciej 'mac' Grzybek
 */
class Chromosome
{
    public:

    /**
     * Do the crossover with given chromosome
     * @param chromosome - smart pointer to Chromosome which dereferences to Chromosome to crossover with.
     * @return smart pointer to Chromosome which represents product of crossover current chromosome with chromosome from argument, which is new Chromosome.
     */
    virtual std::shared_ptr<Chromosome> crossWith(std::shared_ptr<Chromosome> chromsome); 

    /**
     * Do the mutation (self-modification) of current Chromosome
     * @return smart pointer to Chromosome which represents product of mutation, which is new Chromosome.
     */
    virtual std::shared_ptr<Chromosome> mutate();
};

/**
 * Class represents Subject (person, individual etc.)
 * Subject can:
 * - crossover with other Subject
 * - mutate (self-modification)
 *
 *  @author Andrzej 'Yester' Fieudkowicz
 *  @author Maciej 'mac' Grzybek
 */
class Subject
{
    private:
    /**
     * vector of Chromosomes as subject attributes.
     */
    std::vector< std::shared_ptr<Chromosome> > chromosomes;

    public:

    /**
     * Do the crossover of current subject with given one.
     * @param  smart pointer to Subject which dereferences to Subject to crossover with.
     * @return smart pointer to Subject which represents product of crossover with Subject from argument, which is new Subject.
     */
    virtual std::shared_ptr<Subject> crossWith(std::shared_ptr<Subject> &subject);

    /**
     * Do the mutation (self-modification) of subject.
     * @return smart pointer reference as a product of mutation, which is new Subject.
     */
    virtual std::shared_ptr<Subject> mutate();

    /**
     * Add single chromosome to vector of subject's chromosomes.
     * @param chromosome smart pointer to chromosome to be added
     * @throw ChromosomeAllocationException throws when allocation in chromosomes container failed
     */
    virtual void addChromosome(std::shared_ptr<Chromosome> chromosome) throw(ChromosomeAllocationException);

    /**
     * Get single chromosome by given id
     * @param id position of chromosome in Subject's chromosome vector
     * @return smart pointer to got chromosome
     * @throw ChromosomeOutOfBoundException throws when asked for chromosome out of bound in chromosomes container
     */
    virtual std::shared_ptr<Chromosome> getChromosome(unsigned int id) throw(ChromosomeOutOfBoundException);

    /**
     * Replace whole vector of subject's chromosomes.
     * @param chromosomes reference to vector of chromosomes that will replace current
     */
    virtual void replaceChromosomes(std::vector< std::shared_ptr<Chromosome> > &chromosomes);


    /**
     * Set initial value of current Subject (collection of Chromosomes)
     * It produces new instance of collection and swaps it with current.
     */
    virtual void setInitialValue();

    /**
     * Clones current Subject (with it's all chromosomes)
     * It produces deep copy of Subject
     */
    virtual std::shared_ptr<Subject> clone();

};

} /* end of namespace evol */

#endif
