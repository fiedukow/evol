#include "debug.h"
#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <math.h>
#include <iostream>

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
    {
        this->setCm(cm); /* we call setter on already set value to guard range (border values) */
    }
    
    int getCm()
    {
        return cm;
    }

    ChromosomePtr crossWith( ChromosomePtr toCross ) const
    {
        double contributionFactor = EvolFunctions::random();
        double resultCm;
            resultCm += this->cm * contributionFactor;
            resultCm += ptrCast(Wzrost,toCross)->cm * (1 - contributionFactor);
        #ifdef DEBUG
        std::cout << "Rodzic 1: " <<  this->cm \
        << " Rodzic 2: "<< ptrCast(Wzrost,toCross)->cm \
        << " Dziecko: "<< resultCm << std::endl ;
        #endif

        ChromosomePtr result( (Chromosome*) ( new Wzrost( (int) resultCm ) ) );
        return result;
    }
    
    void mutate( )
    {
        /*@note: wylaczona mutacja*/
        //this->addCm( EvolFunctions::random( -10, 10 ) );
        return;
    }
 
    void setCm(int toSet)
    {
            if(toSet > 200)
                    this->cm = 200;
            else if(toSet < 100)
                    this->cm = 100;
            else
                    this->cm = toSet;

    }

    void addCm(int toAdd)
    {
        this->setCm(this->cm + toAdd);
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
        this->addKg(EvolFunctions::random( 30, 150 ));
        V("Waga",this->kg);
    }
    
    Waga( int kg ) : kg(kg)
    {
        this->setKg(kg); /* like in Wzrost */
    }

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

    /* @note: wylaczona mutacja */
    void mutate( )
    {
    //this->addKg( EvolFunctions::random( -4, 4 ) );
        return;
    }

    void setKg(int toSet)
    {
            if(toSet > 150)
                    this->kg = 150;
            else if(toSet < 30)
                    this->kg = 30;
            else
                    this->kg = toSet;
    }

    void addKg(int toAdd)
    {
        this->setKg(this->kg + toAdd);
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
        this->clearChromosomes();
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
    void drukuj() const 
    {
        std::cout << "" << this->getCm() << "cm. " << this->getKg() << "kg.\n";
                
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
        #ifdef DEBUG
        std::cout << "Wolam > " << std::endl;
        std::cout << "Wynik " << (EvolFunctions::abs( perfectBMI - this->bmiValue      ) < 
               EvolFunctions::abs( perfectBMI - ((BMI&) toCompare).bmiValue ));
        #endif
 
        return EvolFunctions::abs( perfectBMI - this->bmiValue      ) < 
               EvolFunctions::abs( perfectBMI - ((BMI&) toCompare).bmiValue );
    }
    
    bool operator == ( const FitnessFunction& toCompare ) const
    {
        return EvolFunctions::abs( perfectBMI - this->bmiValue      ) ==
               EvolFunctions::abs( perfectBMI - ((BMI&) toCompare).bmiValue );
    }

    void calculate( const Subject& toCalculate )
    {
        this->bmiValue =  (double) ((Czlowiek&) toCalculate).getKg() / pow( ((double) ((Czlowiek&) toCalculate).getCm() / 100.0 ), 2 );
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
