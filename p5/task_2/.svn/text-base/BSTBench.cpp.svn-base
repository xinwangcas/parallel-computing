#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include "bmconfig.hpp"
#include "BST.hpp"

/**
 * the data structure we will manipulate in the experiment
 */
BST* bst;

/**
 * Initialize the data structure and warm it up
 */
void bench_init()
{
    bst = new BST();
/*
    bst->insert(5, 5);
    bst->print();
    bst->insert(1, 1);
    bst->print();
    bst->insert(8, 8);
    bst->print();
    bst->insert(0, 0);
    bst->print();
    bst->insert(6, 6);
    bst->print();
    bst->insert(11, 11);
    bst->print();
    bst->insert(7, 7);
    bst->print();
    */

    // warm up the datastructure by filling it half full
    for (uint32_t w = 0; w < Config::CFG.elements; w+=2)
         bst->insert(w, w);
}

/**
 * Run a bunch of random operations
 */
void bench_test(uintptr_t, uint32_t* seed)
{
/*
	bst->remove(0);
	bst->print();
	*/

    // select a random key
    uint32_t key = rand_r(seed) % Config::CFG.elements;

    // select a random value
    uint32_t val = rand_r(seed) % Config::CFG.elements;

    // select a random number to guide what operation to perform
    uint32_t act = rand_r(seed) % 100;

    // do an operation using the values we just created
    if (act < Config::CFG.lookpct)
        bst->lookup(key);
    else if (act < Config::CFG.inspct){
//    	cout << "To insert element (" << key << ", " << val << ")" << endl;
        bst->insert(key, val);
//	bst->print();
    }
    else {
//    	cout << "To remove an element with key = " << key << endl;
        bst->remove(key);
//	bst->print();
    }
}

/**
 * Ensure the final state of the benchmark satisfies all invariants
 */
bool bench_verify()
{
    return bst->isSane();
}
