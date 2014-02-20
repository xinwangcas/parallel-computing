#include <sys/types.h>
#include <iostream>
#include <cstdlib>

using namespace std;
#include "bmconfig.hpp"
#include "HashTable.hpp"

/**
 * the data structure we will manipulate in the experiment
 */
HashTable* hash_table;

/**
 * Initialize the data structure and warm it up
 */
void bench_init()
{
    hash_table = new HashTable();

    // warm up the datastructure by filling it half full
    for (uint32_t w = 0; w < Config::CFG.elements; w+=2)
         hash_table->insert(w, w);
}

/**
 * Run a bunch of random operations
 */
void bench_test(uintptr_t, uint32_t* seed)
{

    // select a random key
    uint32_t key = rand_r(seed) % Config::CFG.elements;

    // select a random value
    uint32_t val = rand_r(seed) % Config::CFG.elements;

    // select a random number to guide what operation to perform
    uint32_t act = rand_r(seed) % 100;

    // do an operation using the values we just created
    if (act < Config::CFG.lookpct)
        hash_table->lookup(key);
    else if (act < Config::CFG.inspct){
//    	cout << "To insert element (" << key << ", " << val << ")" << endl;
        hash_table->insert(key, val);
//	hash_table->print();
    }
    else {
//    	cout << "To remove an element with key = " << key << endl;
        hash_table->remove(key);
//	hash_table->print();
    }
}

/**
 * Ensure the final state of the benchmark satisfies all invariants
 */
bool bench_verify()
{
    return hash_table->isSane();
}
