#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
#include "bmconfig.hpp"
#include "ResizableHashTable.hpp"

struct int_t{
	int a;
	int_t(int _a) : a(_a) {}
	int_t(const int_t &i) {a = i.a;}
	bool operator== (struct int_t& i) {return this->a == i.a;}
	bool operator>= (struct int_t& i) {return this->a >= i.a;}
	friend std::ostream&  operator<<(std::ostream& os, const int_t& k) { os << "{" << k.a << "}"; return os;}
};

namespace std {
 template <> struct hash<int_t> 
 {
 	size_t operator() (const int_t & x) const
	{
		return hash<int>()(x.a);
	}
 };
}
/**
 * the data structure we will manipulate in the experiment
 */
HashTable<string, string>* hash_table;

/**
 * Initialize the data structure and warm it up
 */
void bench_init()
{
    hash_table = new HashTable<string, string>();

    // warm up the datastructure by filling it half full
    for (uint32_t w = 0; w < Config::CFG.elements; w+=2) {
	 string skey; skey += (char)(32 + w%95);
	 string sval; sval += (char)(32 + w%95);
         hash_table->insert(skey, sval);
    }
}

/**
 * Run a bunch of random operations
 */
void bench_test(uintptr_t, uint32_t* seed)
{
    uint32_t key, val;
    string skey, sval;
    // select a random key
    for(int i = 0; i < 5; ++i) {
	    key = rand_r(seed) % Config::CFG.elements;
	    skey += (char)(32 + key%95);
    }

    // select a random value
    for(int i = 0; i < 5; ++i) {
	    val = rand_r(seed) % Config::CFG.elements;
	    sval += (char)(32 + val%95);
    }
    // select a random number to guide what operation to perform
    uint32_t act = rand_r(seed) % 100;

    // do an operation using the values we just created
    if (act < Config::CFG.lookpct)
        hash_table->lookup(skey);
    else if (act < Config::CFG.inspct){
//    	cout << "To insert element (" << key << ", " << val << ")" << endl;
        hash_table->insert(skey, sval);
//	hash_table->print();
    }
    else {
//    	cout << "To remove an element with key = " << key << endl;
        hash_table->remove(skey);
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
