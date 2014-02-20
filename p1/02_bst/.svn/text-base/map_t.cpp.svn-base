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

#include "map_t.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;
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
	root = NULL;		
}

	template<class K, class V>
int map_t<K, V>::Hgt(Node<K, V>* t)
{
	if (t == NULL)
	{
		return -1; 
	}
	else
	{
		return t->height;
	}
}

	template<class K, class V>
int map_t<K, V>::max(int a, int b)
{
	if (a < b)
	{
		return b;
	}
	else
	{
		return a;
	}
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
bool map_t<K, V>::insrt(Node<K,V> *&p, K key, V val)
{
	if (p == NULL)
	{
		p = new Node<K,V>(key, val);
		return true;
	}
	else if (p->pr.first > key)
	{
		insrt(p->left, key, val);
		p->height = max(Hgt(p->left),Hgt(p->right))+1;
		return true;
	}
	else if (p->pr.first < key)
	{
		insrt(p->right, key, val);
		p->height = max(Hgt(p->left),Hgt(p->right))+1;
		return true;
	}
	else if (p->pr.first == key)
	{
		return false;
	}
}

	template <class K, class V>
bool map_t<K, V>::insert(K key, V val)
{
	return insrt(root, key, val);
}

template<class K, class V>
bool map_t<K, V>::update(K key, V val)
{
	Node<K, V> *r = root;
	while (r != NULL)
	{
		if(r->pr.first == key)
		{
			r->pr.second = val;
			return true;
		}
		else if (r->pr.first > key)
		{
			r = r->left;
			continue;
		}
		else if (r->pr.first < key)
		{
			r = r->right;
			continue;
		}
	}
	return false;
}
template <class K, class V>
pair<K, V> map_t<K,V>::Min(Node<K,V>* p)
{
	Node<K,V>* t;
	while(p != NULL)
	{
		t = p;
		p = p->left;
	}
	return t->pr;
}
/*
template <class K, class V>
bool map_t<K, V>::remove(K key)
{
	Node<K, V> *rt = root;
	Node<K, V> **r = &rt;
	while (*r != NULL)
	{
		if ((*r)->pr.first == key)
		{
			if ((*r)->left == NULL && (*r)->right == NULL)
			{
				delete *r;
				*r = NULL;
				return true;
			}
			else if ((*r)->right == NULL && (*r)->left != NULL)
			{
				Node<K, V>* m = (*r)->left;
				delete *r;
				(*r) = m;
				return true;
			}
			else if ((*r)->left == NULL && (*r)->right != NULL)
			{	
				Node<K, V>* m = (*r)->right;
				delete *r;
				(*r) = m;
				return true;
			}
			else if ((*r)->left != NULL && (*r)->right != NULL)
			{
				pair<K, V> tmp = Min((*r)->right);
				remove(tmp.first);
				(*r)->pr = tmp;
				return true;
			}
		}
		else if ((*r) -> pr.first > key)
		{
			r = &((*r)->left);
			continue;
		}
		else if ((*r) -> pr.first < key)
		{
			r = &((*r)->right);
			continue;
		}
	}
	return false;
}
*/



template<class K, class V>
bool map_t<K, V>::remove(K key)
{
	rmv(root, key);
}

	template <class K, class V>
bool map_t<K, V>::rmv(Node<K, V>* &r, K key)
{
	while (r != NULL)
	{
		if ((r)->pr.first == key)
		{
			if ((r)->left == NULL && (r)->right == NULL)
			{
				delete r;
				r = NULL;
				return true;
			}
			else if ((r)->right == NULL && (r)->left != NULL)
			{
				Node<K, V>* m = (r)->left;
				delete r;
				(r) = m;
				return true;
			}
			else if ((r)->left == NULL && (r)->right != NULL)
			{	
				Node<K, V>* m = (r)->right;
				delete r;
				(r) = m;
				return true;
			}
			else if ((r)->left != NULL && (r)->right != NULL)
			{
				pair<K, V> tmp = Min((r)->right);
				remove(tmp.first);
				(r)->pr = tmp;
				return true;
			}
		}
		else if ((r) -> pr.first > key)
		{
			rmv(r->left, key);
			r->height = max(Hgt(r->left),Hgt(r->right))+1;
			return true;
		}
		else if ((r) -> pr.first < key)
		{
			rmv(r->right, key);
			r->height = max(Hgt(r->left),Hgt(r->right))+1;
			return true;
		}
	}
	return false;
}
template <class K, class V>
pair<V, bool> map_t<K, V>::lookup(K key)
{
	Node<K, V>* r = root;
	while(r != NULL)
	{
		if (r->pr.first == key)
		{
			return pair<V,bool>(r->pr.second,true);
		}
		else if(r->pr.first > key)
		{
			r = r->left;
			continue;
		}
		else if(r->pr.first < key)
		{
			r = r->right;
			continue;
		}
	}
	return pair<V,bool>(root->pr.second,false);
}

template<class K, class V>
void map_t<K, V>::InOrder(std::function<void(pair<K,V>)> f, Node<K,V>* r)
{
	if(r != NULL)
	{
	InOrder(f,r->left);
	f(r->pr);
	InOrder(f,r->right);
	}
}

template<class K, class V>
bool map_t<K, V>::lookupval(std::function<bool(pair<K, V>)> f, Node<K, V>* r)
{
	
	if (r == NULL)
		return false;
	if (f(r->pr))
	{
		return true;
	}
	else 
	{
		if(lookupval(f, r->left) == true)
			return true;
		if(lookupval(f, r->right) == true)
			return true;
		return false;
	}
}

template<class K, class V>
bool map_t<K, V>::lookup_val(std::function<bool(pair<K, V>)> f)
{
	lookupval(f, root);
}
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
void map_t<K, V>::in_order(std::function<void(pair<K,V>)> f)
{
		InOrder(f,root);
}
template<class K, class V>
void map_t<K, V>::PreOrder(std::function<void(pair<K,V>)> f, Node<K,V>* r)
{
	if(r != NULL)
	{
	f(r->pr);
	PreOrder(f,r->left);
	PreOrder(f,r->right);
	}
}
template <class K, class V>
void map_t<K, V>::pre_order(std::function<void(pair<K,V>)> f)
{
		PreOrder(f,root);
}

template <class K, class V>
void map_t<K, V>::level_order()
{
	vector<Node<K, V>* > nodes;
	if (root == NULL)
		return;
	nodes.push_back(root);
	root->pos = 30;
	int current = 0;
	int last = 1;
	while(current < nodes.size())
	{
		last = nodes.size();
		int fac = 2;
		int start = current;
		int strl = 0;
		strstream ss;
		string s;
		while(current < last)
		{
			if(current == start)
			{
				for(int i = nodes[current]->pos - fac*nodes[current]->height; i > 0 ; i --)
					cout << " ";
				for (int i = fac*nodes[current]->height; i > 0 ; i --)
					cout << ((nodes[current]->left != NULL) ? "*" : " ");
			}
			else
			{
				for(int i = nodes[current]->pos - nodes[current-1]->pos-fac*nodes[current]->height-
				fac*nodes[current-1]->height-strl; i > 0 ; i --)
					cout << " ";
				for (int i = fac*nodes[current]->height; i > 0 ; i --)
					cout << ((nodes[current]->left != NULL) ? "*" : " ");
			}
			cout << nodes[current]->pr.first;
			ss << nodes[current]->pr.first;
			ss >> s;
			//cout << "string: " <<s;
			strl = s.length();
			for (int i = fac*nodes[current]->height; i > 0 ; i --)
				cout << ((nodes[current]->right != NULL) ? "*" : " ");
			if(nodes[current]->left != NULL)
			{
				nodes[current]->left->pos = nodes[current]->pos - fac*nodes[current]->height;
				nodes.push_back(nodes[current]->left);
			}
			if(nodes[current]->right != NULL)
			{
				nodes[current]->right->pos = nodes[current]->pos + fac*nodes[current]->height;
				nodes.push_back(nodes[current]->right);
			}
			current += 1;
		}
		cout << endl;
	}

}

/**
 *  TODO: explain why this line is needed
 *
 *  TODO: you will probably need more lines of this sort to complete all of
 *        your various tests.
 */
template class map_t<int, int>;
template class map_t<int, Nval>;
