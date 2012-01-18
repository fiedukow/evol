#include <boost/test/minimal.hpp>
#include <boost/test/detail/enable_warnings.hpp>
#include <iostream>

#include "../src/Population.hpp"
#include "../src/Chromosome.hpp"
#include "../src/Subject.hpp"
#include "../src/EvolFunctions.hpp"
#include "../src/Observer.hpp"
#include "../src/debug.h"

using namespace evol;

/*
 * zmienne globalne przechowujace liczniki wywolan poszczegolnych fragmentow kodu
 * wylacznie na potrzeby testow
 */

unsigned int crossovers = 0;
unsigned int chromosomeCrossovers = 0;
unsigned int chromosomeMutations = 0;
unsigned int selections = 0;
unsigned int generations = 0;

unsigned int coInvok = 0;
unsigned int moInvok = 0;
unsigned int soInvok = 0;

/* rozmiar populacji do testow */
const unsigned int populationSize = 10;
/* arbitralnie wybrany wzorcowy wspolczynnik krzyzowania */
const double  patternCrossFactor = 1.0;
/* aribitralnie wybrany wzorcowy wspolczynnik mutacji */
const double mutationChance = 0.2;
/* wyznaczona reczna symulacja ilosc mutacji chromosomow */
const unsigned int patternChromosomeMutations = 10;
/* wyznaczona reczna symulacja ilosc krokow do osiagniecia celu */
const unsigned int correctStepCountToResult = 2;
/* tablica wartosci referencyjnych wynikow posrednich dzialania algorytmu, wyznaczona przez reczna symulacyje */
const unsigned int correctPartialResults[2] = { 53, 15 };
/* oczekiwana wynikowa wartosc dzialania algorytmu */
const unsigned int referenceValue = 0;

class FunctionX : public Chromosome
{
    int value;
    FunctionX() {}
    public:
    FunctionX(const int value) : value(value) {}
    ChromosomePtr crossWith(ChromosomePtr toCross) const
    {
        ++chromosomeCrossovers;
        std::shared_ptr<FunctionX> chromosomeToReturn( new FunctionX() );
        double randomFactor = EvolFunctions::random(); /* udzial chromosomu toCross w krosowaniu */

        chromosomeToReturn->value = (1-randomFactor) * this->value + randomFactor*(EvolFunctions::ptr_cast<ChromosomePtr,FunctionX>(toCross)->value)/2;

        return chromosomeToReturn;
    }
    void mutate()
    {
        ++chromosomeMutations;
        this->value += EvolFunctions::random(-1,1); // mutacja dodaje +- 1
    }
    int getValue()
    {
        return value;
    }
};

class FunctionSubject : public Subject
{
    public:
    void setInitialValue()
    {
        this->clearChromosomes();
        ChromosomePtr functionValue = ChromosomePtr( new FunctionX(EvolFunctions::random(-100,100)) );
        this->addChromosome(functionValue);
    }
    int getValue()
    {
        FunctionX *firstChromo;

        firstChromo = EvolFunctions::ptr_cast<ChromosomePtr,FunctionX>(this->getChromosome(0));
        return firstChromo->getValue();
    }

    SubjectPtr clone() const
    {
        SubjectPtr newTestSubject = SubjectPtr(new FunctionSubject());
        for(auto& entry : this->chromosomes)
        {
            newTestSubject->addChromosome(entry);
        }
        return newTestSubject;
    }

    SubjectPtr crossWith(SubjectPtr &subject) const throw(SubjectCrossException)
    {
        ++crossovers;
        return Subject::crossWith(subject);
    }

    void print() const
    {
        std::cout << EvolFunctions::ptr_cast<ChromosomePtr,FunctionX>(this->getChromosome(0))->getValue() << std::endl;
    }
};

class testFF : public FitnessFunction
{
    double value;
    public:
    testFF( double value ) : value(value)
    {}
    void calculate( const Subject& toCalculate )
    {
        FunctionSubject& doOceny = (FunctionSubject&) toCalculate;
        this->value = doOceny.getValue()*doOceny.getValue(); // x^2
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
        return this->value < ((testFF&)toCompare).value;
    }
    bool operator == ( const FitnessFunction& toCompare ) const
    {
        return this->value == ((testFF&)toCompare).value;
    }
    

};

class ResultPrinter : public NewGenerationObserver
{
    public:
    void update(Population& population)
    {
        FunctionSubject *toCheck = EvolFunctions::ptr_cast<SubjectPtr,FunctionSubject>(population.getSubjects().at( population.getBestId() ));

        /*
         * sprawdzenie czy w danym kroku algorytmu (danej generacji) wynik posredni jest poprawny, tj. zgodny z reczna symulacja
         */
        M("Sprawdzanie wynikow czastkowych dzialania algorytmu.");
        BOOST_CHECK(toCheck->getValue() == correctPartialResults[generations]);
        C(toCheck->getValue() == correctPartialResults[generations]);
        population.getCurrentBestFF()->print();

        ++generations;

        std::vector< SubjectPtr >& populationSubjectsVector = population.getSubjects();

        /*
         * testowanie czy na poczatku (przed kazdym obiegiem petli glownej) istnieje poprawna ilosc osobnikow (obiektow)
         */
        M("Sprawdzanie ilosci osobnikow w populacji przed krokiem petli algorytmu.");
        BOOST_CHECK(populationSubjectsVector.size() == populationSize);
        C(populationSubjectsVector.size() == populationSize);
    }
};


class coObserver : public CrossoverObserver
{
    public:
    void update(Population& population)
    {
        ++coInvok;
    }
};
class moObserver : public MutateObserver
{
    public:
    void update(Population& population)
    {
        ++moInvok;
    }
};
class soObserver : public SelectionObserver
{
    public:
    void update(Population& population)
    {
        ++soInvok;
        std::vector< SubjectPtr >& populationSubjectsVector = population.getSubjects();
        M("Sprawdzanie wielkosci populacji przed selekcja.");
        BOOST_CHECK(populationSubjectsVector.size() == (1+patternCrossFactor)*populationSize);
        C(populationSubjectsVector.size() == (1+patternCrossFactor)*populationSize);
    }
};

class Observers
{
    CObserverPtr co;
    MObserverPtr mo;
    SObserverPtr so;
    Population &population;
    public:
    Observers(Population &population) : population(population)
    {
        this->co = CObserverPtr( new coObserver() );
        this->mo = MObserverPtr( new moObserver() );
        this->so = SObserverPtr( new soObserver() );
    }

    void registerObservers()
    {
        population.registerObserver(this->co);
        population.registerObserver(this->mo);
        population.registerObserver(this->so);
    }

    CObserverPtr getCrossoverObserver()
    {
        return this->co;
    }
    MObserverPtr getMutateObserver()
    {
        return this->mo;
    }
    SObserverPtr getSelectionObserver()
    {
        return this->so;
    }
};

class CycleCounter : public NewGenerationObserver
{
    unsigned int cycles;
    constexpr static int maxCycles = 10;
    public:
    CycleCounter() : cycles(0) {}
    void update(Population& population)
    {
        if(cycles == maxCycles)
        {
            population.stopLoop();
        }
        ++cycles;
    }
};

int test_main( int argc, char* argv[] ) //uwaga - zmieniona nazwa funkcji main
{
    EvolFunctions::initialize(1234);
    /*
     * sprawdzenie czy dla podanego ziarna,
     * na testujacej architekturze, wartosci funkcji random() sa takie same jak referencyjne,
     * dla ktorych przeprowadzane byly symulacje dzialania algorytmu
     * W przypadku niepomyslnego przejscia tego testu, nie nalezy wierzyc testom zwiazanym z symulacja dzialania algorytmu (sprawdzanie ilosci wolanych funkcji/obserwatorow, iteracji do znalezienia wyniku etc.).
     * Nie sa to terminalne testy, poniewaz niektore z pozostalych testow nie zaleza od losowosci i przez to mozna je wykonac.
     * Ponadto inny losowy ciag nie oznacza blednego dzialania algorytmu, a jedynie niepewnosc co do wynikow jego testow.
     * Uzyto wartosci calkowitoliczbowych, mimo mniejszej precyzji (w tym przypadku), poniewaz dla liczb zmiennopozycyjnych moga wystepowac uchyby zwiazane z zaokragleniami, nawet dla "takich samych" wartosci z generatora liczb pseudolosowych.
     * Sprawdzeniu podlegaja trzy pierwsze wartosci, w celu zmniejszenia prawdopodobienstwa otrzymania takich samych wartosci dla roznych ciagow liczb losowych.
     */
    int pierwsza = EvolFunctions::random(0,100000);
    int druga = EvolFunctions::random(0,100000);
    int trzecia = EvolFunctions::random(0,100000);
    M("Sprawdzenie generatora liczb pseudolosowych.");
    BOOST_CHECK(pierwsza == 37623);
    BOOST_CHECK(druga == 61684);
    BOOST_CHECK(trzecia == 16544);
    C(pierwsza == 37623 && druga == 61684 && trzecia == 16544);
    testFF ff(0);
    SubjectPtr subjectPrototype( (Subject*) new FunctionSubject() );
    Population populacja( ( FitnessFunction &)ff, subjectPrototype, populationSize, mutationChance, patternCrossFactor );
    Observers testObservers(populacja);
    NObserverPtr cCounter( new CycleCounter() );
    NObserverPtr rpPtr( new ResultPrinter() );
    SubjectPtr wynik;

    /* sprawdzenie poprawnego ustawienia zadanych parametrow w konstruktorze i test dzialania getterow */
    BOOST_CHECK(populacja.getMutationChance() == mutationChance);
    C(populacja.getMutationChance() == mutationChance);
    BOOST_CHECK(populacja.getCrossFactor() == patternCrossFactor);
    C(populacja.getCrossFactor() == patternCrossFactor);

    testObservers.registerObservers(); // rejestrujemy obserwatorow w populacji
    populacja.registerObserver(cCounter);
    populacja.registerObserver(rpPtr);

    wynik = populacja.start();

    std::cout << std::endl;

    /*
     * test fitness function
     * Sprawdzamy czy porownanie dwoch fitnessFunction dziala prawidlowo (czy f(7) < f(10), gdzie f(x) = x^2 [dla zadanego ff]
     */
    testFF firstFitnessFunction(10);
    testFF secondFitnessFunction(7);
    M("Sprawdzanie fitness functions (first = 10, second = 7).");
    BOOST_CHECK(firstFitnessFunction<secondFitnessFunction);
    C(firstFitnessFunction<secondFitnessFunction);
    BOOST_CHECK(firstFitnessFunction<=secondFitnessFunction);
    C(firstFitnessFunction<=secondFitnessFunction);
    BOOST_CHECK(secondFitnessFunction>=firstFitnessFunction);
    C(secondFitnessFunction>=firstFitnessFunction);
    BOOST_CHECK(secondFitnessFunction>firstFitnessFunction);
    C(secondFitnessFunction>firstFitnessFunction);
    BOOST_CHECK(secondFitnessFunction!=firstFitnessFunction);
    C(secondFitnessFunction!=firstFitnessFunction);
    M("Porownywanie dwoch fitnessfunction o takich samych wartosciach.");
    testFF thirdFitnessFunction(8);
    testFF fourthFitnessFunction(8);
    BOOST_CHECK(thirdFitnessFunction==fourthFitnessFunction);
    C(thirdFitnessFunction==fourthFitnessFunction);
    BOOST_CHECK(thirdFitnessFunction>=fourthFitnessFunction);
    C(thirdFitnessFunction>=fourthFitnessFunction);
    BOOST_CHECK(thirdFitnessFunction<=fourthFitnessFunction);
    C(thirdFitnessFunction<=fourthFitnessFunction);
    BOOST_CHECK(!(thirdFitnessFunction>fourthFitnessFunction));
    C(!(thirdFitnessFunction>fourthFitnessFunction));
    BOOST_CHECK(!(thirdFitnessFunction<fourthFitnessFunction));
    C(!(thirdFitnessFunction<fourthFitnessFunction));

    /*
     * test obserwatorow i poprawnosci wykonania algorytmu
     * sprawdzamy ilosc wolan odpowiednich obserwatorow w klasie pochodnej:
     * dla referencyjnych danych, przy zadanym ziarnie (1234), wynik powinien zostac odnaleziony po correctStepCountToResult (3) iteracjach 
     */
    M("Test obserwatorow i poprawnosci wykonania algorytmu.");
    M("Testowanie ilosci wywolan obserwatora krzyzowania (crossoverObserver).");
    BOOST_CHECK( coInvok == correctStepCountToResult );
    C( coInvok == correctStepCountToResult );
    M("Testowanie ilosci wywolan obserwatora mutacji (mutateObserver).");
    BOOST_CHECK( moInvok == correctStepCountToResult );
    C( moInvok == correctStepCountToResult );
    M("Testowanie ilosci wywolan obserwatora selekcji (selectionObserver).");
    BOOST_CHECK( soInvok == correctStepCountToResult );
    C( soInvok == correctStepCountToResult );
    M("Testowanie ilosci wywolan obserwatora nowej generacji (ilosc przebiegow petli glownej).");
    BOOST_CHECK( generations == correctStepCountToResult );
    C( generations == correctStepCountToResult );

    M("Sprawdzanie ilosci krzyzowan chromosomow.");
    BOOST_CHECK( chromosomeCrossovers == 1*populationSize*correctStepCountToResult ); // ilosc krzyzowan chromosomow. 1 - ilosc chromosomow w obiekcie (argument funkcji - X)
    C( chromosomeCrossovers == 1*populationSize*correctStepCountToResult ); // ilosc krzyzowan chromosomow. 1 - ilosc chromosomow w obiekcie (argument funkcji - X)
    M("Sprawdzanie ilosci wykonanych krzyzowan.");
    BOOST_CHECK( crossovers == populationSize*correctStepCountToResult ); // ilosc krzyzowan obiektow
    C( crossovers == populationSize*correctStepCountToResult );

    M("Sprawdzanie ilosci mutacji chromosomow.");
    BOOST_CHECK( chromosomeMutations == patternChromosomeMutations ); // wyznaczona symulacyjnie wartosc mutacji chromosomow, dla zadanego mutationChance = 0.2
    C( chromosomeMutations == patternChromosomeMutations ); // wyznaczona symulacyjnie wartosc mutacji chromosomow, dla zadanego mutationChance = 0.2
    
    /*
     * czy po zakonczeniu dzialania algorytmu ustawione poczatkowo wspolczynniki sa nadal niezmienione i ustawione na zadane wartosci (niezmiennosc wybranych parametrow)
     */
    M("Sprawdzanie niezmiennosci parametrow poczatkowych.");
    BOOST_CHECK(populacja.getMutationChance() == mutationChance);
    C(populacja.getMutationChance() == mutationChance);
    BOOST_CHECK(populacja.getCrossFactor() == patternCrossFactor);
    C(populacja.getCrossFactor() == patternCrossFactor);

    FunctionSubject *resultSubject = EvolFunctions::ptr_cast<SubjectPtr,FunctionSubject>(wynik);
    
    M("Sprawdzanie osiagniecia przez algorytm oczekiwanej wartosci referencyjnej jako wyniku.");
    BOOST_CHECK(resultSubject->getValue() == referenceValue);
    C(resultSubject->getValue() == referenceValue);

    return 0;
}
