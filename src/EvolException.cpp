#include "EvolException.hpp"

namespace evol
{

/* out of bound exception pack */
OutOfBoundException::OutOfBoundException(const std::out_of_range &e) : e(e) {}

const char* OutOfBoundException::what() const throw()
{
        return this->e.what();
}

ChromosomeOutOfBoundException::ChromosomeOutOfBoundException(const std::out_of_range &e) : OutOfBoundException(e) {}

SubjectOutOfBoundException::SubjectOutOfBoundException(const std::out_of_range &e) : OutOfBoundException(e) {}

/* allocation exception pack */
AllocationException::AllocationException(const std::bad_alloc &e) : e(e) {}

const char* AllocationException::what() const throw()
{
        return this->e.what();
}

ChromosomeAllocationException::ChromosomeAllocationException(const std::bad_alloc &e) : AllocationException(e) {}

SubjectAllocationException::SubjectAllocationException(const std::bad_alloc &e) : AllocationException(e) {}

} /* end of evol namespace */
