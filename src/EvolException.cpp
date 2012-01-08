#include "EvolException.hpp"

namespace evol
{

/* out of bound exception pack */
class OutOfBoundException : EvolException
{
    private:
    std::out_of_range &e;
    public:
    OutOfBoundException(const std::out_of_range &e)
    {
        this.e = e;
    }
    
    const char* what() const throw()
    {
        return e.what();
    }
};

class ChromosomeOutOfBoundException : OutOfBoundException
{
    public:
    ChromosomeOutOfBoundException(const std::out_of_range &e) : OutOfBoundException(e);
};

class SubjectOutOfBoundException : OutOfBoundException
{
    public:
    SubjectOutOfBoundException(const std::out_of_range &e) : OutOfBoundException(e);
};

/* allocation exception pack */
class AllocationException : EvolException
{
    private:
    std::bad_alloc &e;

    public:
    AllocationException(const std::bad_alloc &e)
    {
        this.e = e;
    }

    const char* what() const throw()
    {
        return e.what();
    }
};

class ChromosomeAllocationException : AllocationException
{
    public:
    ChromosomeAllocationException(const std::bad_alloc &e) : AllocationException(e);
};


class SubjectAllocationException : AllocationException
{
    public:
    SubjectAllocationException(const std::bad_alloc &e) : AllocationException(e);
};

} /* end of evol namespace */
