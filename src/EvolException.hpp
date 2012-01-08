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
    
    /*
     * what() method calls container's out_of_range (stored) exception's what() method.
     * @return const char* string returned by stored exception's what() method
     */
    const char* what() const throw();
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

    /*
     * what() method calls container's bad_alloc (stored) exception's what() method.
     * @return const char* string returned by stored exception's what() method
     */
    const char* what() const throw();
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

} /* end of evol namespace */

#endif
