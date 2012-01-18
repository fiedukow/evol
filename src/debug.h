#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef DEBUG
/**
 * Simple debug library
 */
#ifndef DEBUG_ITERATOR
#define DEBUG_ITERATOR
#include <assert.h>
#include <iostream>
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
#define T(a,b) { int debug_iterator=0;                                          \
             std::cerr << (a) << std::endl;                                     \
             for( auto debug_tmp_value : (b) )                                  \
             {                                                                  \
                 std::cerr << debug_iterator << ".\t" << debug_tmp_value;       \
                 std::cerr << std::endl;                                        \
                 ++debug_iterator;                                              \
             }} 
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
 * Chceck condition but dont asssert :-)
 */
#ifndef C
#define C(a) std::cerr<< "(Check)  Testuje warunek\n " << #a;                     \
             if(!(a)) std::cerr << "\t\t[FAIL]\n";                              \
             else  std::cerr << "\t\t[OK]\n";                                
#endif
#else
#define V(a,b)
#define M(a)
#define T(a,b)
#define A(a)
#define C(a)

/*ifdef DEBUG*/
#endif

#endif
