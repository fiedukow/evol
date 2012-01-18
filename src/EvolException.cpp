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

CrossException::~CrossException() throw() {}
const char* CrossException::what() const throw()
{
    return "Outsized crossover exception";
}

SubjectCrossException::SubjectCrossException(unsigned int sizeOfFirst, unsigned int sizeOfSecond) : firstSize(sizeOfFirst), secondSize(sizeOfSecond) {}
SubjectCrossException::~SubjectCrossException() throw() {}

const char* SubjectCrossException::what() const throw()
{
    return "Subject's crossover exception: chromosomes count mismatch.";
}

ChromosomeCrossException::ChromosomeCrossException(const char *first, const char *second) : firstName(first), secondName(second) {}
ChromosomeCrossException::~ChromosomeCrossException() throw() {}

const char* ChromosomeCrossException::what() const throw()
{
    return "Chromosome crossover exception: chromosomes' types mismatch.";
}

FileException::FileException(const std::string filePath) : filePath(filePath) {}
FileException::~FileException() throw() {}
const char* FileException::what() const throw()
{
    std::string temporaryString = "File exception occured on file ";
    temporaryString += filePath;
    return temporaryString.c_str();
}

CannotOpenFileException::CannotOpenFileException(const std::string filePath) : FileException(filePath) {}
CannotOpenFileException::~CannotOpenFileException() throw() {}

const char* CannotOpenFileException::what() const throw()
{
    std::string temporaryString = "File exception: cannot open file ";
    temporaryString += FileException::filePath;
    return temporaryString.c_str();
}

} /* end of evol namespace */
