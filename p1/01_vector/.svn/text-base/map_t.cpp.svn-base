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
#include <algorithm>
#include "map_t.hpp"
#include <iostream>
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
bool myfunc(pair<K, V> k1, pair<K, V> k2){return (k1.first<k2.first);}
template <class K, class V>
bool map_t<K, V>::insert(K key, V val)
{
    // if the key is in the map, return false.  If the list was sorted, this
    // could be done in O(log(n)) time
/*    for (auto i = keys->begin(); i != keys->end(); ++i) {
        if (*i == key) {
            return false;
        }
    }
*/
    // insert the key and value.  Note that indices should, by default, match
    // between these two vectors.
//    keys->push_back(key);
//    values->push_back(val);
    pair<K, V> pr;
    pr.first = key;
    pr.second = val;
    if(!std::binary_search(pairs->begin(),pairs->end(),pr,myfunc<K, V>))
    {
    pairs->push_back(pr);
    std::sort(pairs->begin(),pairs->end(),myfunc<K, V>);
    return true;
    }
    return false;
}

 template <class K, class V>
 bool map_t<K,V>::update(K key, V val)
    {
    	for (auto &i: *pairs)
	{
		if (i.first == key){
			i.second = val;
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
  bool map_t<K,V>::remove(K key){
    	for (auto i = pairs->begin(); i != pairs->end(); ++i)
	{	
		if (i->first == key){
			pairs->erase(i);
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
   pair<V, bool> map_t<K,V>::lookup(K key){

    	for (auto i = pairs->begin() ; i != pairs->end(); ++i){
		if (i->first == key){
			return pair<V, bool>(i->second, true);
		}
	}
	return pair<V, bool>(pairs->begin()->second, false);
    }

template<class K, class V>
bool map_t<K, V>::lookup_val(std::function<bool(pair<K, V>)> f)
{
	for (auto i:*pairs)
	{
		if(f(i))
			return true;
	}
	return false;
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

//};

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
void map_t<K, V>::in_order(std::function<void(pair<K, V>)> f)
{
    for (auto i : *pairs) {
        f(i);
    }
}

template <class K, class V>
void map_t<K, V>::pre_order(std::function<void(pair<K, V>)> f)
{
}

template <class K, class V>
void map_t<K, V>::level_order()
{
}


/**
 *  TODO: explain why this line is needed
 *
 *  TODO: you will probably need more lines of this sort to complete all of
 *        your various tests.
 */
template class map_t<int, int>;

template class map_t<int, Nval>;
