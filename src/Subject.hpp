#ifndef _SUBJECT_HPP_
#define _SUBJECT_HPP_

#include <vector>
#include <memory>
#include "EvolException.hpp"
#include "Chromosome.hpp"
#include "debug.h"

namespace evol
{

class Subject;

/** 
 * declaration of smart pointer type Subject
 */
typedef std::shared_ptr<Subject> SubjectPtr;

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
    protected:
    /**
     * vector of Chromosomes as subject attributes.
     */
    std::vector< ChromosomePtr > chromosomes;

    public:

    /**
     * Do the crossover of current subject with given one.
     * @param  smart pointer to Subject which dereferences to Subject to crossover with.
     * @return smart pointer to Subject which represents product of crossover with Subject from argument, which is new Subject.
     */
    virtual SubjectPtr crossWith(SubjectPtr &subject) const throw (SubjectCrossException);

    /**
     * Do the mutation (self-modification) of subject.
     */
    virtual void mutate();

    /**
     * Add single chromosome to vector of subject's chromosomes.
     * @param chromosome smart pointer to chromosome to be added
     * @throw ChromosomeAllocationException throws when allocation in chromosomes container failed
     */
    virtual void addChromosome(ChromosomePtr chromosome) throw(ChromosomeAllocationException);

    /**
     * Get single chromosome by given id
     * @param id position of chromosome in Subject's chromosome vector
     * @return smart pointer to got chromosome
     * @throw ChromosomeOutOfBoundException throws when asked for chromosome out of bound in chromosomes container
     */
    virtual ChromosomePtr getChromosome(unsigned int id) const throw(ChromosomeOutOfBoundException);

    /**
     * Replace whole vector of subject's chromosomes.
     * @param chromosomes reference to vector of chromosomes that will replace current
     */
    virtual void replaceChromosomes(std::vector< ChromosomePtr > &chromosomes);


    /**
     * Set initial value of current Subject (collection of Chromosomes)
     * It produces new instance of collection and swaps it with current.
     */
    virtual void setInitialValue() = 0;

    /**
     * Clones current Subject (with it's all chromosomes)
     * It produces deep copy of Subject
     */
    virtual SubjectPtr clone() const = 0;

    virtual void print() const = 0;

    protected: 
    /**
     * Clears chromosomes list.
     * It can be used to overwrite all chromosomes using
     * 'list' of chromosomes to add and addChromosome method.
     */
    virtual void clearChromosomes();

};

} /* end of namespace evol */

#endif
