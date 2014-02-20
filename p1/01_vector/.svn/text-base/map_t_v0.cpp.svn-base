/**
 *  Origin:  Lehigh CSE Department
 *  Course:  CSE 375/475
 *  Date:    2013-08-27
 *  Version: 1
 *
 *  Description: This file implements a few of the functions for a simple
 *  map, but does so poorly.  The student's job is to complete the
 *  implementation and do it well.
 */

#include "map_t_v0.hpp"

/**
 *  Construct two vectors for our map
 *
 *  TODO: change this according to the changes to map_t's fields
 */
template <class K, class V>
map_t<K, V>::map_t()
{
//    keys = new vector<K>();
//    values = new vector<K>();
	pairs= new vector<pair<K, V> >;
	K keys;
	V values;
}

/**
 *  Insert a (key, value) pair
 *
 *  TODO: this implementation is not sorted, and hence the in_order method is
 *        not correct.  Note that getting this correct will require
 *        significant re-thinking of the approach to iteration in this
 *        method.
 */
template <class K, class V>
bool map_t<K, V>::insert(K key, V val)
{
    // if the key is in the map, return false.  If the list was sorted, this
    // could be done in O(log(n)) time
    for (auto i = keys->begin(); i != keys->end(); ++i) {
        if (*i == key) {
            return false;
        }
    }

    // insert the key and value.  Note that indices should, by default, match
    // between these two vectors.
//    keys->push_back(key);
//    values->push_back(val);
    pair<K, V> pr;
    pr.first = keys;
    pr.second = values;
    pairs.push_back(pr);
    return true;
}

   template <class K, class V>
 bool update(K key, V val)
    {
    	for (int i = 0; i < pairs.size() ; i ++)
	{
		if (pairs[i].first == key){
			pairs[i].second = value;
			return true;
		}
	}
	return false;
    }

    /**
     *  Remove the (key, val) pair if it is present in the data structure.
     *  Returns true on success, false if the key was not already present.
     *
     *  TODO: implement this function
     */
  template <class K, class V>
  bool remove(K key){
    	for (int i = 0 ; i < pairs.size() ; i ++)
	{	
		if (pairs[i].first == key){
			pairs.erase(pairs[i]);
			return true;
		}
	}
	return false;
    }

    /**
     *  If key is present in the data structure, return a pair consisting of
     *  the corresponding val and true.  Otherwise, return a pair with the
     *  boolean set to false.
     *
     *  TODO: implement this function
     *
     *  TODO: What requirements does the use of std::pair place on
     *        constructors for the template parameter V?
     */
 template <class K, class V>
   pair<V, bool> lookup(K key){
    	for (int i = 0 ; i < pairs.size(); i ++){
		if (pairs[i].first == key){
			return pair<pairs[i].second, true>;
		}
	}
	return pair<pairs[i--].second, false>;
    }

    /**
     *  Apply a function to each key, in order
     *
     *  TODO: switch to std::function, instead of ugly C function pointer
     *        syntax
     */
//    void in_order(void (*f)(K, V));

    /**
     *  TODO: implement a function that can do a pre-order traversal.  As
     *        above, it should use std::function for its parameter
     */
//    void pre_order(void (*f)(K, V));
};
/**
 *  Perform a traversal of the map, and execute function 'f()' on each k/v
 *  pair
 *
 *  TODO: This code is obviously not correct, since it doesn't use the values
 *        vector at all.  It's probably the case that for an implementation
 *        that uses a pair of vectors, the aggressive use of auto and vector
 *        ranges is too optimistic.
 */
template <class K, class V>
void map_t<K, V>::in_order(void (*f)(K, V))
{
    for (auto i : *keys) {
        f(i, 0);
    }
}

/**
 *  TODO: explain why this line is needed
 *
 *  TODO: you will probably need more lines of this sort to complete all of
 *        your various tests.
 */
template class map_t<int, int>;
