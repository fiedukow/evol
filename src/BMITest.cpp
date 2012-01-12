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
        this->setCm(EvolFunctions::random( 100, 200 ));
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
        setCm( this->cm += EvolFunctions::random( -10, 10 ) );
        return;
    }
 
    void setCm(int toSet)
    {
        if(toSet > 200)
            toSet = 200;
        if(toSet < 100)
            toSet = 100;
        this->cm = toSet;
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
        this->setKg(EvolFunctions::random( 30, 150 ));
        V("Waga",this->kg);
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
        this->setKg( this->getKg() + EvolFunctions::random( -4, 4 ) );
        return;
    }

    void setKg(int toSet)
    {
        if(toSet>150)
            toSet = 150;
        if(toSet<30)
            toSet = 30;
        this->kg = toSet;
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
        M("Czlowiek::getCm() called.");
        return ptrCast( Wzrost, this->getChromosome( 0 ) )->getCm();
    }

    int getKg() const 
    {
        M("Czlowiek::getKg() called.");
        return ptrCast( Waga,   this->getChromosome( 1 ) )->getKg();
    }    
    
    void setInitialValue()
    {
        M("Czlowiek::setInitialValue() called.");
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
            M("addChromosome(getChromosome(0)) called.");
            result->addChromosome( ptrCast( Wzrost, this->getChromosome( 0 ) )->clone()  );
            result->addChromosome( ptrCast( Waga,   this->getChromosome( 1 ) )->clone()  );      
        }
        catch(ChromosomeOutOfBoundException &e)
        {
            std::cout << e.what() << std::endl;
            exit(0);
        }
        return result;
    }

    #ifdef DEBUG2
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
        std::cout << ">";        
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
        this->bmiValue =  (double) ((Czlowiek&) toCalculate).getKg() / pow( ((double) ((Czlowiek&) toCalculate).getCm() / 100.0 ), 2 );
                   
        //std::cout << (double) ((Czlowiek&) toCalculate).getCm() << " " << (double) ((Czlowiek&) toCalculate).getKg() << " " << bmiValue << std::endl;
    }
    
    std::unique_ptr < FitnessFunction > clone() const
    {
        std::unique_ptr<FitnessFunction> result = std::unique_ptr<FitnessFunction>(new BMI());
        ((BMI&)(*result)).bmiValue = this->bmiValue;
        return result;
    }

    #ifdef DEBUG2
    void drukuj()
    {
        std::cout << "BMI: " << bmiValue << std::endl ;
    }
    #endif
};

int main()
{
    M("POCZATEK PROGRAMU.");
    const BMI goal;
    SubjectPtr czlowiekSubject( (Subject*) new Czlowiek() );
    czlowiekSubject->setInitialValue();
    Population populacja( ( FitnessFunction& ) goal, czlowiekSubject, 10 );
    Czlowiek* wynik;
    try
    {
        wynik = ptrCast(Czlowiek, populacja.start( ));
    }
    catch ( OutOfBoundException &e )
    {
        std::cerr << e.what() << std::endl ;
    }
    #ifdef DEBUG2
    wynik->drukuj();
    #endif
    return 0;
}
