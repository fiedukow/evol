#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

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
    std::exception &e;
    public:
    /*
     * Constructor which gets and stores exception thrown by container
     * which thrown it's own out_of_range exception
     * @param e reference to exception thrown by container
     */
    OutOfBoundException(std::exception &e);
    
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
};

/*
 * Exception class for subject out of bound exception
 *
 * @author Andrzej 'Yester' Fiedukowicz
 * @author Maciej 'mac' Grzybek
 */
class SubjectOutOfBoundException : OutOfBoundException
{
};

} /* end of evol namespace */

#endif
