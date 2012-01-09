#include "EvolException.hpp"

namespace evol
{

EvolException::~EvolException() throw() {}
const char* EvolException::what() const throw()
{
    return "Evol library exception has occured.";
}

/* out of bound exception pack */

OutOfBoundException::OutOfBoundException(const std::out_of_range e) : e(e) {}
OutOfBoundException::~OutOfBoundException() throw() {}

const char* OutOfBoundException::what() const throw()
{
        return this->e.what();
}

ChromosomeOutOfBoundException::ChromosomeOutOfBoundException(const std::out_of_range e) : OutOfBoundException(e) {}
ChromosomeOutOfBoundException::~ChromosomeOutOfBoundException() throw() {}

SubjectOutOfBoundException::SubjectOutOfBoundException(const std::out_of_range e) : OutOfBoundException(e) {}
SubjectOutOfBoundException::~SubjectOutOfBoundException() throw() {}

/* allocation exception pack */
AllocationException::AllocationException(const std::bad_alloc e) : e(e) {}
AllocationException::~AllocationException() throw() {}

const char* AllocationException::what() const throw()
{
        return this->e.what();
}

ChromosomeAllocationException::ChromosomeAllocationException(const std::bad_alloc e) : AllocationException(e) {}
ChromosomeAllocationException::~ChromosomeAllocationException() throw() {}

const char* ChromosomeAllocationException::what() const throw()
{
        return this->e.what();
}

SubjectAllocationException::SubjectAllocationException(const std::bad_alloc e) : AllocationException(e) {}
SubjectAllocationException::~SubjectAllocationException() throw() {}

const char* SubjectAllocationException::what() const throw()
{
        return this->e.what();
}

} /* end of evol namespace */
