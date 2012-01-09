#include "debug.h"
#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <iostream>
#include <math.h>

#define ptrCast(typ, nazwa) ((typ*)(&(*(nazwa))))

using namespace evol;

class Wzrost : Chromosome
{
    int cm;

    public: 
    
    Wzrost( )
    {
        this->cm = EvolFunctions::random( 100, 200 );
    }

    Wzrost( int cm ) : cm(cm)
    { }
    
    int getCm()
    {
        return cm;
    }

    ChromosomePtr crossWith( ChromosomePtr toCross ) const
    {
        double contributionFactor = EvolFunctions::random();
        int resultCm;
            resultCm += this->cm * contributionFactor;
            resultCm += ptrCast(Wzrost,toCross)->cm * (1 - contributionFactor);

        ChromosomePtr result( (Chromosome*) ( new Wzrost( resultCm ) ) );
        return result;
    }
    
    void mutate( )
    {
        this->cm += EvolFunctions::random( -20, 20 );
        return;
    }
 
    ChromosomePtr clone( )
    {
        ChromosomePtr result( (Chromosome*) new Wzrost ( this->cm ) );
        return result;
    }
};

class Waga : Chromosome
{
    int kg;

    public: 
    
    Waga( )
    {
        this->kg = EvolFunctions::random( 30, 150 );
    }
    
    Waga( int kg ) : kg(kg)
    { }

    int getKg( )
    {
        return kg;
    }

    ChromosomePtr crossWith( ChromosomePtr toCross ) const
    {  
        double contributionFactor = EvolFunctions::random();
        int resultKg;
            resultKg += this->kg * contributionFactor;
            resultKg += ptrCast(Waga,toCross)->kg * (1 - contributionFactor);

        ChromosomePtr result( (Chromosome*) new Waga( resultKg ) );
        return result;
    }   

    void mutate( )
    {
        this->kg += EvolFunctions::random( -5, 5 );
        return;
    }

    ChromosomePtr clone( )
    {
        ChromosomePtr result( (Chromosome*) new Waga ( this->kg ) );
        return result;
    }
    
};




class Czlowiek : Subject
{
    public:

    int getCm() const 
    {
        this->getChromosome( 0 );
        return ptrCast( Wzrost, this->getChromosome( 0 ) )->getCm();
    }

    int getKg() const 
    {
        return ptrCast( Waga,   this->getChromosome( 1 ) )->getKg();
    }    
    
    void setInitialValue()
    {
        ChromosomePtr wzrost( (Chromosome*) new Wzrost() );
        ChromosomePtr waga( (Chromosome*) new Waga() );
        this->addChromosome( wzrost );
        this->addChromosome( waga   );       
    }

    SubjectPtr clone() const 
    {
        SubjectPtr result( (Subject*) new Czlowiek() );

        /*@TODO fix those ugly lines */
        try
        {
            result->addChromosome( ptrCast( Wzrost, this->getChromosome( 0 ) )->clone()  );
            result->addChromosome( ptrCast( Waga,   this->getChromosome( 1 ) )->clone()  );      
        }
        catch(ChromosomeOutOfBoundException &e)
        {
            std::cout << e.what() << std::endl;
        }
        return result;
    }

    #ifdef DEBUG
    void drukuj()
    {
        std::cout << "Czlowiek ideal ma " << this->getCm() << "cm. wzrostu \
                      oraz wazy " << this->getKg() << "kg.\n";
                
    }    
    #endif
};



class BMI : FitnessFunction
{
    double bmiValue;

    public:

    BMI()
    {
        this->bmiValue = 20.0;
    }
    
    /* const static double perfectBMI; jk */
    #define perfectBMI 21.0
    bool operator > ( const FitnessFunction& toCompare ) const
    {
        return abs( perfectBMI - this->bmiValue      ) < 
               abs( perfectBMI - ((BMI&) toCompare).bmiValue );
    }
    
    bool operator == ( const FitnessFunction& toCompare ) const
    {
        return abs( perfectBMI - this->bmiValue      ) ==
               abs( perfectBMI - ((BMI&) toCompare).bmiValue );
    }

    void calculate( const Subject& toCalculate )
    {
        this->bmiValue = pow( ((double) ((Czlowiek&) toCalculate).getCm() / 100.0 ), 2 )
                   /  (double) ((Czlowiek&) toCalculate).getKg();
    }
    
    std::unique_ptr < FitnessFunction > clone() const
    {
        std::unique_ptr<FitnessFunction> result = std::unique_ptr<FitnessFunction>(new BMI());
        ((BMI&)(*result)).bmiValue = this->bmiValue;
        return result;
    }
};

int main()
{
    M("POCZATEK PROGRAMU.");
    const BMI goal;
    SubjectPtr czlowiekSubject( (Subject*) new Czlowiek() );
    Population populacja( ( FitnessFunction& ) goal, czlowiekSubject, 200 );
    Czlowiek* wynik;
    try
    {
        wynik = ptrCast(Czlowiek, populacja.start( ));
    }
    catch ( OutOfBoundException &e )
    {
        std::cerr << e.what() << std::endl ;
    }
    #ifdef DEBUG
    wynik->drukuj();
    #endif
    return 0;
}
