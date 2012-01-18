#include <boost/test/minimal.hpp>
#include <boost/test/detail/enable_warnings.hpp>
#include <iostream>

#include "../src/Population.hpp"
#include "../src/Chromosome.hpp"
#include "../src/Subject.hpp"
#include "../src/EvolFunctions.hpp"
 
using namespace evol;

class testChromosome : public Chromosome
{
    int value;
    public:
    testChromosome(const int value) : value(value) {}
    ChromosomePtr crossWith(ChromosomePtr toCross) const
    {
    }
    void mutate()
    {
    }
    int getValue()
    {
        return value;
    }
};

class testSubject : public Subject
{
    public:
    void setInitialValue()
    {
        this->clearChromosomes();
        ChromosomePtr firstChromo = ChromosomePtr( new testChromosome(0) );
        ChromosomePtr secondChromo = ChromosomePtr( new testChromosome(1) );
        this->addChromosome(firstChromo);
        this->addChromosome(secondChromo);
    }
    int getSummaryValue()
    {
        testChromosome *firstChromo;
        testChromosome *secondChromo;

        firstChromo = EvolFunctions::ptr_cast<ChromosomePtr,testChromosome>(this->getChromosome(0));
        secondChromo = EvolFunctions::ptr_cast<ChromosomePtr,testChromosome>(this->getChromosome(1));
        return firstChromo->getValue() + secondChromo->getValue();
    }

    SubjectPtr clone() const
    {
        SubjectPtr newTestSubject = SubjectPtr(new testSubject());
        for(auto& entry : this->chromosomes)
        {
            newTestSubject->addChromosome(entry);
        }
        return newTestSubject;
    }

    void drukuj() const
    {
    }
};

class testFF : public FitnessFunction
{
    int value;
    public:
    testFF( int value ) : value(value)
    {}
    void calculate( const Subject& toCalculate )
    {
        testSubject& doOceny = (testSubject&) toCalculate;
        this->value = doOceny.getSummaryValue();
    }

    std::unique_ptr< FitnessFunction > clone() const
    {
        return std::unique_ptr< FitnessFunction >( new testFF( this->value ) );
    }

    void print()
    {
    }
    bool operator >  ( const FitnessFunction& toCompare ) const
    {
        return (this->value>((testFF&)toCompare).value);
    }
    bool operator == ( const FitnessFunction& toCompare ) const
    {
        return (this->value == ((testFF&)toCompare).value);
    }
    

};

int test_main( int argc, char* argv[] ) //uwaga - zmieniona nazwa funkcji main
{
    EvolFunctions::initialize(1234);
    testFF ff(100);
    SubjectPtr subjectPrototype( (Subject*) new testSubject() );
    Population populacja( ( FitnessFunction &)ff, subjectPrototype, 100, 0.2, 1.0 );
    std::cout << EvolFunctions::random() << std::endl;
    std::cout << EvolFunctions::random() << std::endl;
    std::cout << EvolFunctions::random() << std::endl;

    BOOST_CHECK(populacja.getMutationChance() == 0.2);
    BOOST_CHECK(populacja.getCrossFactor() == 1.0);

    //w monitorowanym srodowisku uzyskujemy dostep do makr testujacych o wiele mowiacych nazwach
    //makro BOOST_REQUIRE przerywa testowanie w przypadku niespelnienia podanego mu warunku
    BOOST_REQUIRE( 3 == 3 );
    //za pomoca tego makra powinny byc wiec testowane warunki, ktorych spelnienie jest krytyczne dla
    //dalszego dzialania programu
 
 
    //BOOST_CHECK wypisuje informacje o bledzie na standardowe wyjscie po zakonczeniu testow
    BOOST_CHECK( 9 == 9 );
    BOOST_CHECK( 9 == 9 );
    return 0;
}
