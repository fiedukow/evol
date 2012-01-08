/**
 * Simple debug library
 */
#ifndef DEBUG_ITERATOR
#define DEBUG_ITERATOR
#include <assert.h>
int debug_iterator;
#endif

/*
 * Print message (first argument) and variable (second argument) value
 * @example V("Iterator ",i);
 */
#ifndef V
#define V(a,b) std::cerr << (a) << "\t" << #b << " = " << (b) << std::endl ; 
#endif


/*
 * Print debug message (first argument) 
 */
#ifndef M
#define M(a) std::cerr << (a) << std::endl;
#endif

/*
 * Print message (first argument) and container (second argument) content with numeration.
 */
#ifndef T 
#define T(a,b) debug_iterator=0;                                                \
             std::cerr << (a) << std::endl;                                     \
             for( auto debug_tmp_value : (b) )                                  \
             {                                                                  \
                 std::cerr << debug_iterator << ".\t" << debug_tmp_value;       \
                 std::cerr << std::endl;                                        \
                 ++debug_iterator;                                              \
             }                                                                  
#endif

/*
 * Assert test with message :-)
 */
#ifndef A
#define A(a) std::cerr<< "(Assert) Testuje warunek " << #a;                     \
             if(!(a)) std::cerr << "\t\t[FAIL]\n";                              \
             assert(a); std::cerr << "\t\t[OK]\n";                                
#endif

/*
 * Chceck condition but dont do asssert :-)
 */
#ifndef C
#define C(a) std::cerr<< "(Check)  Testuje warunek " << #a;                     \
             if(!(a)) std::cerr << "\t\t[FAIL]\n";                              \
             else  std::cerr << "\t\t[OK]\n";                                
#endif

