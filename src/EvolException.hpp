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
class OutOfBoundException : public EvolException
{
    protected:
    /*
     * received in constructor exception (possibly from container which has thrown it's own out_of_range exception
     */
    const std::out_of_range e;
    public:
    /*
     * Constructor which gets and stores exception thrown by container
     * which thrown it's own out_of_range exception
     * @param e reference to exception thrown by container
     */
    OutOfBoundException(const std::out_of_range e);

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
class ChromosomeOutOfBoundException : public OutOfBoundException
{
    public:
    ChromosomeOutOfBoundException(const std::out_of_range e);
    virtual ~ChromosomeOutOfBoundException() throw();
};

/*
 * Exception class for subject out of bound exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class SubjectOutOfBoundException : public OutOfBoundException
{
    public:
    SubjectOutOfBoundException(const std::out_of_range e);
    virtual ~SubjectOutOfBoundException() throw();
};

/*
 * Base exception class for allocation exceptions
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class AllocationException : public EvolException
{
    protected:
    /*
     * received in constructor exception (possibly from container which has thrown it's own bad_alloc exception
     */
    const std::bad_alloc e;

    public:
    /*
     * Constructor which gets and stores exception thrown by container
     * which thrown it's own out_of_range exception
     * @param e reference to exception thrown by container
     */
    AllocationException(const std::bad_alloc e);
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
class ChromosomeAllocationException : public AllocationException
{
    public:
    ChromosomeAllocationException(const std::bad_alloc e);
    virtual ~ChromosomeAllocationException() throw();

    /*
     * what() method calls container's bad_alloc (stored) exception's what() method.
     * @return const char* string returned by stored exception's what() method
     */
    virtual const char* what() const throw();
};

/* 
 * Exception for Subject bad allocation exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class SubjectAllocationException : public AllocationException
{
    public:
    SubjectAllocationException(const std::bad_alloc e);
    virtual ~SubjectAllocationException() throw();

    /*
     * what() method calls container's bad_alloc (stored) exception's what() method.
     * @return const char* string returned by stored exception's what() method
     */
    virtual const char* what() const throw();
};

/**
 * Base class for cross exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */

class CrossException : public EvolException
{
    public:
    virtual ~CrossException() throw();
    
    /*
     * what() method returns message about exception
     * @return const char* null terminated string with message
     */
    virtual const char* what() const throw();

};

/**
 * Exception for Subject crossWith()
 * throws when collections of chromosomes from two subjects are different size
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class SubjectCrossException : public CrossException
{
    private:
    unsigned int firstSize;
    unsigned int secondSize;
    public:
    /**
     * Constructor stores sizes of first and second subject's chromosomes collections
     * @param sizeOfFirst size of first chromosome container
     * @param sizeOfSecond size of second chromosome container
     */
    SubjectCrossException(unsigned int sizeOfFirst, unsigned int sizeOfSecond);
    virtual ~SubjectCrossException() throw();

    /*
     * what() method returns message with exception details
     * @return const char* null terminated string with exception details
     */
    virtual const char* what() const throw();

};

/**
 * Exception for Chromosome crossWith()
 * throws when pair of corresponding chromosomes are different types
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class ChromosomeCrossException : public CrossException
{
    private:
    const char *firstName;
    const char *secondName;
    public:
    /**
     * Constructor stores name of first and second subject
     * @param first name of first chromosome object (class)
     * @param second name of second chromosome object (class)
     */
    ChromosomeCrossException(const char *first, const char *second);
    virtual ~ChromosomeCrossException() throw();

    /*
     * what() method returns message with exception details
     * @return const char* null terminated string with exception details
     */
    virtual const char* what() const throw();
};

class FileException : public EvolException
{
    protected:
    const std::string filePath;
    public:
    FileException(const std::string filePath);
    virtual ~FileException() throw();

    /*
     * what() method returns message with exception details
     * @return const char* null terminated string with exception details
     */
    virtual const char* what() const throw();

};

class CannotOpenFileException : public FileException
{
    public:
    CannotOpenFileException(const std::string filePath);
    virtual ~CannotOpenFileException() throw();

    /*
     * what() method returns message with exception details
     * @return const char* null terminated string with exception details
     */
    virtual const char* what() const throw();
};


} /* end of evol namespace */

#endif
