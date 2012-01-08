#ifndef _SUBJECTS_HPP_
#define _SUBJECTS_HPP_

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
    public:

    /**
     * Do the crossover of current subject with given one.
     * @param  smart pointer to Subject which dereferences to Subject to crossover with.
     * @return smart pointer to Subject which represents product of crossover with Subject from argument, which is new Subject.
     */
    shared_ptr<Subject> crossWith(shared_ptr<Subject> subject);

    /**
     * Do the mutation (self-modification) of subject.
     * @return smart pointer reference as a product of mutation, which is new Subject.
     */
    shared_ptr<Subject> mutate();

    private:

    /**
     * Vector of Chromosomes as subject attributes.
     */
    Vector<shared_ptr<Chromosome> > chromosomes;
};

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
    virtual shared_ptr<Chromosome> crossWith(shared_ptr<Chromosome> chromsome); 

    /**
     * Do the mutation (self-modification) of current Chromosome
     * @return smart pointer to Chromosome which represents product of mutation, which is new Chromosome.
     */
    virtual shared_ptr<Chromosome> mutate();
};

#endif
