#include <boost/test/minimal.hpp>
#include <iostream>
 
int test_main( int argc, char* argv[] ) //uwaga - zmieniona nazwa funkcji main
{
 
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
