#include "debug.h"
#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <math.h>
#include <iostream>

#define ptrCast(typ, nazwa) ((typ*)(&(*(nazwa))))

using namespace evol;

typedef std::shared_ptr< Przedmiot > PrzedmiotPtr;


/**
 *  Skarbiec przechowuje przedmioty do wyboru
 *  Skarbiec potrafi wylosować element do wyjęcia, który ma conajwyżej zadaną wagę.
 */
class Skarbiec
{    
    /*wektor powinien być zawsze posortowany wg. wagi przedmiotu */
    std::vector< PrzedmiotPtr > przedmioty;

    public:
    #define DP(waga,wartosc) this->przedmioty.push_back( new Przedmiot(waga,wartosc) );
    Skarbiec()
    {
        /*tworzenie domyslnego sejfu (w zasadzie zawartosc statyczna
          ale mogla by byc wczytana np. z pliku lub bazy danych) */
        DP(2.4, 300);
        DP(2.4, 300);
        DP(2.4, 300);
        DP(2.4, 300);
        DP(2.4, 300);
        DP(2.4, 300);
        DP(2.4, 300);
        DP(2.4, 300);
        DP(2.4, 300);
        this->sortuj();
    }

    /*tworzy skrarbiec na bazie wektora (np. konkretnego plecaka*/
    Skarbiec( std::vector <PrzedmiotPtr> przedmioty )
    {        
        this->przedmioty = przedmioty;        
        this->sortuj();
    }
        
    /*wybiera losowy przedmiot spośród takiego podzbioru przedmiotów 
      w skarbcu, że waga każdego z nich jest mniejsza równa maksWaga*/
    PrzedmiotPtr wybierzLosowy( int maksWaga )
    {
        /* ustal zakres losowania */
        int i = -1;
        for( PrzedmiotPtr przedmiot : przedmioty )
        {
           if( przedmiot.getWaga()>maksWaga )
                ++i;
           else 
                break;          
        }
        if( i < 0 ) return PrzedmiotPtr(NULL);
        int wybor = EvolFunctions::random( 0, i );
        PrzedmiotPtr rezultat = przedmioty[wybor];
        przedmioty.erase(wybor);
        return rezultat;
    }

    /*tworzy kopie skarbca*/
    std::unique_ptr<Skarbiec> clone()
    {
        vector <PrzedmiotPtr> kopia = this->przedmioty;
        return std::unique_ptr( new Skarbiec(kopia) );
    }

    private:
    sortuj()
    {
        sort( this->przedmioty.begin(), this->przedmioty.end(), new PrzedmiotComparator()); 
    }
};

class PrzedmiotComparator
{
    bool operator( const PrzedmiotPtr first, const PrzedmiotPtr second )
    {
        return first->getWaga() < second->getWaga();
    }
};

class Przedmiot 
{
    double waga;
    int wartosc;

    public: 
    /* prosty konsturktor */
    Przedmiot( double waga, int wartosc): waga(waga), wartosc(wartosc)
    {}

    /* gettery */
    double getWaga(){ return this->waga;    }
    int getWartosc(){ return this->wartosc; }
};


class ZawartoscPlecaka : public Chromosome
{
    std::vector< PrzedmiotPtr > przedmioty;
    static double udzwig;

    public: 
    /* tworzy losowy plecak
       z przedmiotow ze skarbca   
     */
    ZawartoscPlecaka( const Skarbiec& skad )
    {
        std::shared_ptr<Skarbiec> SkarbPtr = skad.clone();
        PrzedmiotPtr przedmiot;
        while(przedmiot = SkarbPtr->wybierzLosowy(udzwig-getWagaSumaryczna()))
        {
            przedmioty.push_back(przedmiot);
        }
    }

    /* ile przedmiotow jest aktualnie w plecaku*/
    int getIlePrzedmiotow( )
    {
        return this->przedmioty.size();
    }

    /* waga wszystkich przedmiotow w plecaku*/
    double getWagaSumaryczna( )
    {
        double waga = 0;
        for( auto przedmiot : przedmioty )
        {
            waga += przedmiot->getWaga();
        }
        return waga;
    }

    /* pobiera udzwig*/
    double getUdzwig()
    {
        return ZawartoscPlecaka::udzwig;
    }
    
    /*ustawia udzwig*/
    void setUdzwig( double doUstawienia )
    {
        ZawartoscPlecaka::udzwig = doUstawienia;
    }

    /*dodaje okreslony przedmiot do plecaka*/
    void dodajDoPlecaka( PrzedmiotPtr doDodania )
    {
        this->przedmioty.push_back( doDodania );
    }

    /*krzuje dwa plecaki ze soba w taki sposob ze
      1. Wez losowy procent przedmiotow ze starego plecaka
      2. Dopoki to mozliwe losuj ze skarbca drugiego plecaka przedmiotu
      3. Dopoki to mozliwe losuj ze skarbca ogolnego przedmioty
    */
    ChromosomePtr crossWith( ChromosomePtr toCross ) const
    {
        /*@FIXME*/
    }
    
    /* mutuje plecak w taki sposob ze
       1. Zabierz z plecaka jeden losowy przedmiot
       2. Dopoki to mozliwie losuj ze skarbca ogolnego nowe przedmioty   
     */
    void mutate( )
    {
        /*@FIXME*/
    }

    /*wykonuje kopie chromosomu*/ 
    ChromosomePtr clone( )
    {
        /*@FIXME*/
    }
};




class Plecak : public Subject
{
    public:
    
    /*tworzy plecak wypelniony losowa choc dopuszczalna zawartoscia*/
    void setInitialValue()
    {
        this->clearChromosomes();
        ChromosomePtr zawartosc = new ZawartoscPlecaka( SKARBIEC_OGOLNY );
        this->addChromosome( zawartosc );       
    }

    /*wykonuje kopie plecaka*/
    SubjectPtr clone() const 
    {
        SubjectPtr nowyPlecak = new Plecak(); 
        nowyPlecak.addChromosome( this->chromosomes[0] );
    }

    #ifdef DEBUG2
    void drukuj() const 
    {
        /*@FIXME if u need me :-) */        
    }    
    #endif
};



class WartoscPlecaka : FitnessFunction
{
    int wartosc;

    public:

    /* tworzy prototypowa wartosc do ktorej bedziemy dazyc*/
    WartoscPlecaka()
    {
        this->wartosc = 2000 ;
    }

    WartoscPlecaka( int wartosc ) : wartosc(wartosc)
    {}
    
    bool operator > ( const FitnessFunction& toCompare ) const
    {
        return this->wartosc > ((WartoscPlecaka&)toCompare).wartosc;
    }
    
    bool operator == ( const FitnessFunction& toCompare ) const
    {
        return this->wartosc == ((WartoscPlecaka&)toCompare).wartosc;
    }

    /*policz wartosc funkcji celu:
      1. Wez kolejne przedmiotu z plecaka i dodaj ich wartosci
      2. Zapisz uzyskana liczbe jako wartosc
    */
    void calculate( const Subject& toCalculate )
    {
        Plecak& doOceny = (Plecak&) toCalculate;
        this->wartoc = doOceny.getWartosc();
    }
    
    /*tworzy kopie funckji celu*/
    std::unique_ptr < FitnessFunction > clone() const
    {
        return std::unique_ptr< FitnessFunction >( new WartoscPlecaka( this->wartosc ) );  
    }

    #ifdef DEBUG2
    void drukuj()
    {
        /*@FIXME if u need me :-) */
    }
    #endif
};

int main()
{
    WartoscPlecaka goal;
    SubjectPtr plecak( (Subject*) new Plecak() );
    plecak->setInitialValue();

    /*@FIXME naruszenia ochrony pamieci dla populacji wielkosci 1 */
    Population populacja( ( FitnessFunction& ) goal, plecak, 100 );
    Plecak* wynik;
    try
    {
        wynik = ptrCast(Plecak, populacja.start( ));
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
