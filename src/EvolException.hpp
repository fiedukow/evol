#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <stdexcept>

namespace evol
{

/*
 * Base exception class for evol exceptions
 * 
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class EvolException : std::exception
{
    public:
    virtual ~EvolException() throw();
    virtual const char* what() const throw();
};

/*
 * Base exception class for out of bound exceptions
 * 
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class OutOfBoundException : EvolException
{
    private:
    /*
     * received in constructor exception (possibly from container which has thrown it's own out_of_range exception
     */
    std::out_of_range &e;
    public:
    /*
     * Constructor which gets and stores exception thrown by container
     * which thrown it's own out_of_range exception
     * @param e reference to exception thrown by container
     */
    OutOfBoundException(const std::out_of_range &e);

    /**
     * Virtual destructor
     */
    virtual ~OutOfBoundException() throw();
    
    /*
     * what() method calls container's out_of_range (stored) exception's what() method.
     * @return const char* string returned by stored exception's what() method
     */
    virtual const char* what() const throw();
};

/*
 * Exception class for chromosomes out of bound exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class ChromosomeOutOfBoundException : OutOfBoundException
{
    public:
    ChromosomeOutOfBoundException(const std::out_of_range &e);
};

/*
 * Exception class for subject out of bound exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class SubjectOutOfBoundException : OutOfBoundException
{
    public:
    SubjectOutOfBoundException(const std::out_of_range &e);
};

/*
 * Base exception class for allocation exceptions
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class AllocationException : EvolException
{
    private:
    /*
     * received in constructor exception (possibly from container which has thrown it's own bad_alloc exception
     */
    std::bad_alloc &e;

    public:
    /*
     * Constructor which gets and stores exception thrown by container
     * which thrown it's own out_of_range exception
     * @param e reference to exception thrown by container
     */
    AllocationException(const std::bad_alloc &e);
    
    virtual ~AllocationException() throw();

    /*
     * what() method calls container's bad_alloc (stored) exception's what() method.
     * @return const char* string returned by stored exception's what() method
     */
    virtual const char* what() const throw();
};

/* 
 * Exception for chromosome bad allocation exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class ChromosomeAllocationException : AllocationException
{
    public:
    ChromosomeAllocationException(const std::bad_alloc &e);
};

/* 
 * Exception for Subject bad allocation exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class SubjectAllocationException : AllocationException
{
    public:
    SubjectAllocationException(const std::bad_alloc &e);
};

/**
 * Base class for cross exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */

class CrossException : EvolException
{
    public:
    virtual ~CrossException() throw();
};

/**
 * Exception for Subject crossWith()
 * throws when collections of chromosomes from two subjects are different size
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class SubjectCrossException : CrossException
{
    private:
    unsigned int firstSize;
    unsigned int secondSize;
    public:
    /**
     * Constructor stores sizes of first and second subject's chromosomes collections
     */
    SubjectCrossException(unsigned int first, unsigned int second);
};

/**
 * Exception for Chromosome crossWith()
 * throws when pair of corresponding chromosomes are different types
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class ChromosomeCrossException : CrossException
{
    private:
    const char *firstName;
    const char *secondName;
    public:
    /**
     * Constructor stores name of first and second subject
     */
    ChromosomeCrossException(const char *first, const char *second);
};




} /* end of evol namespace */

#endif
