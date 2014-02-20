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
#include <queue>
#include <vector>
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

	template<class K, class V>
Node<K, V>* map_t<K, V>::L_Rotate(Node<K, V>* &t)
{
	Node<K, V>* temp = t->left;
	Node<K, V>* &tp = t->left->right;
	t->left = tp;
	tp = t;
	t->height = max(Hgt(t->left),Hgt(t->right))+1;
	temp->height = max(Hgt(temp->left),Hgt(temp->right))+1;
	return temp;
}

	template<class K, class V>
Node<K, V>* map_t<K, V>::R_Rotate(Node<K, V>* &t)
{
	Node<K, V> * temp = t->right;
	Node<K, V>* &tp = t->right->left;
	t->right = tp;
	tp = t;
	t->height = max(Hgt(t->left),Hgt(t->right))+1;
	temp->height = max(Hgt(temp->right),Hgt(temp->left))+1;
	return temp;
}

	template<class K, class V>
Node<K, V>* map_t<K, V>::LR_Rotate(Node<K, V>* &t)
{
	t->left = R_Rotate(t->left);
	return L_Rotate(t);
}

	template<class K, class V>
Node<K, V>* map_t<K, V>::RL_Rotate(Node<K, V>* &t)
{
	t->right = L_Rotate(t->right);
	return R_Rotate(t);
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
		p->height = 0;
		return true;
	}
	else if (p->pr.first > key)
	{
		insrt(p->left, key, val);
		if(Hgt(p->left)-Hgt(p->right) == 2)
		{
			if(p->left->pr.first > key)
			{
				p = L_Rotate(p);
			}
			else
			{
				p = LR_Rotate(p);
			}
		}
		p->height = max(Hgt(p->left),Hgt(p->right))+1;
		return true;
	}
	else if (p->pr.first < key)
	{
		insrt(p->right, key, val);
		if(Hgt(p->right)-Hgt(p->left) == 2)
		{
			if(p->right->pr.first < key)
			{
				p = R_Rotate(p);
			}
			else
			{
				p = RL_Rotate(p);
			}
		}
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
			if (Hgt((r)->right)-Hgt((r)->left) == 2)
			{
				if((r)->right->left != NULL && (Hgt((r)->right->left)>Hgt((r)->right->right)))
				{
					(r) = RL_Rotate((r));
				}
				else
				{
					(r) = R_Rotate((r));
				}
			}
			return true;
		}
		else if ((r) -> pr.first < key)
		{
			rmv(r->right, key);
			if(Hgt((r)->left)-Hgt((r)->right) == 2)
			{
				if((r)->left->right != NULL &&(Hgt((r)->left->right)>Hgt((r)->left->left)))
				{
					r = LR_Rotate(r);
				}
				else
				{
					r = L_Rotate(r);
				}
			}
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
		int fac = 4;
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

/*void map_t<K, V>::level_order(Node<K, V>* r)
  {
  if(r != NULL)
  {
  queue<Node<K, V>* > Q;
  Node<K, V> *t= r;
  Q.push(t);
  int layer = t->height;
  int n = layer;
  while(!Q.empty())
  {
  Node<K, V>* fr = Q.front();
  if ((layer - fr->height) >= 1)
  {
  layer -- ;
  cout << endl;
  cout << "+";
  cout << endl;
  }
  Q.pop();
  cout << " " << fr->pr.first << " ";
  if(fr->left != NULL)
  {
  Q.push(fr->left);
  for(int i = 0 ; i <= n-layer ; i ++)
  cout  << " ";
  }
  if(fr->right != NULL)
  {
  Q.push(fr->right);
  for(int i = 0 ; i <= n-layer ; i ++)
  cout  << " ";
  }
  }
  }
  cout << endl;
  }
  */
/**
 *  TODO: explain why this line is needed
 *
 *  TODO: you will probably need more lines of this sort to complete all of
 *        your various tests.
 */
template class map_t<int, int>;
