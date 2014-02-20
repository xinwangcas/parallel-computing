#ifndef BST_HPP__
#define BST_HPP__

#include <stack>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;
using std::vector;
using std::pair;
using std::make_pair;
/**
 *  A simple Balanced Search Tree holding key/value pairs.  
 */

class BST
{
    /**
     *  Type for the nodes of the BST
     */
    struct Node
    {
    	/**
	 * The key stored at this node
	 */
	int   key;

        /**
         *  The value stored at this node
         */
        int   val;

        /**
         *  The left child
         */
        Node* left;

	/**
	 *  The right child
	 */
	Node* right;

	/*
	 * the Balance factor
	 */
	int balance_factor;

	/**
	 * The offset from the screen margin, used to print the bst
	 */
	int offset;

        /**
         *  Basic constructor
         */
        Node(int _key = -1, int _val = -1, Node* _left = NULL, Node * _right = NULL) 
		: key(_key), val(_val), left(_left), right(_right), balance_factor(0), offset(0) { }
	
	unsigned int height(void)
	{
		int h1 = left  ? left->height(): 0;
		int h2 = right ? right->height() : 0;
		return max(h1, h2) + 1;
	}
	int cal_balance_factor()
	{
		int lh = left  ? left->height() : 0;
		int rh = right ? right->height(): 0;
		return rh - lh;
	}
    };

    void rotate_left(Node ** r)
    {
	    Node * new_root = (*r)->right;
	    Node ** temp = &((*r)->right->left);
	    (*r)->right = *temp;
	    *temp = *r;
	    *r = new_root;
    }

    void rotate_right(Node ** r)
    {
	    Node * new_root = (*r)->left;
	    Node ** temp = &((*r)->left->right);
	    (*r)->left = *temp;
	    *temp = *r;
	    *r = new_root;
    }

  public:

    Node * root;
    /**
     * constructor just makes a sentinel for the data structure
     */
    BST(): root(NULL)  {}

    /**
     * simple sanity check: make sure all elements of the BST are in sorted
     * order
     */
    bool isSane(void) const
    {
        return true;
    }

    /**
     * insert method; find the right place in the BST, add key/val node; 
     * if the node is already in the BST, exit without inserting
     */
    bool insert(int key, int val)
    {
	    __transaction_relaxed {
		    //generate a new node
		    Node * temp = new Node(key, val);

		    if(!root)
		    {
			    root = temp;
			    return true;
		    }

		    //create a stack to store the path of the address from the root to the inserted node.
		    stack<Node **> path;

		    Node ** cur = &root;
		    Node ** parent = NULL;

		    while(*cur)
		    {
			    if(key == (*cur)->key) //the key is in the map
				    return false;
			    else if (key < (*cur)->key)
			    {
				    parent = cur;
				    cur = &((*cur)->left);
			    }
			    else
			    {
				    parent = cur;
				    cur = &((*cur)->right);
			    }
			    path.push(parent);
		    }

		    if(key < (*parent)->key)
			    *cur = temp;
		    else
			    *cur = temp;

		    Node ** child = cur;
		    Node ** childchild = NULL;
		    bool higher = true;
		    //look back through the tree to the root to see if each subtree is still balanced.
		    while(!path.empty())
		    {
			    Node ** t = path.top();

			    if(!higher)
				    break;

			    if(&((*t)->left) == child)
			    {
				    switch((*t)->balance_factor)
				    {
					    case 0:
						    (*t)->balance_factor = -1;
						    higher = true;
						    break;
					    case 1:
						    (*t)->balance_factor = 0;
						    higher = false;
						    break;
					    case -1://we added the node to the left subtree of t, which was already higher.
						    //so we may need to balance.
						    switch((*child)->balance_factor)
						    {
							    case 0://since the avl tree root at t is already balanced, we do nothing
								    break;
							    case 1:
								    childchild = &((*child)->right);
								    if((*childchild)->balance_factor == -1) 
								    { 
									    (*t)->balance_factor = 1; 
									    (*child)->balance_factor = 0;
									    (*childchild)->balance_factor = 0;
								    }
								    else if((*childchild)->balance_factor == 0)
								    {
									    (*t)->balance_factor = 0;
									    (*child)->balance_factor = 0;
									    (*childchild)->balance_factor = 0;
								    }
								    else if((*childchild)->balance_factor == 1)
								    {
									    (*t)->balance_factor = 0;
									    (*child)->balance_factor = -1;
									    (*childchild)->balance_factor = 0;
								    }

								    rotate_left(child);
								    rotate_right(t);
								    break;
							    case -1:
								    (*child)->balance_factor = 0;
								    (*t)->balance_factor = 0;
								    rotate_right(t);
								    break;
							    default:
								    assert(0);
								    break;
						    }
						    higher = false;
						    break;
					    default:
						    assert(0);
						    break;
				    }
			    }
			    else if(&((*t)->right) == child)
			    {
				    switch((*t)->balance_factor)
				    {
					    case 0:
						    (*t)->balance_factor = 1;
						    higher = true;
						    break;
					    case -1:
						    (*t)->balance_factor = 0;
						    higher = false;
						    break;
					    case 1: //we inserted a node to the right subtree of t, which was already higher.
						    //so we may need to balance in this case.
						    switch((*child)->balance_factor)
						    {
							    case 0://since the avl tree root at t is already balanced, we do nothing
								    break;
							    case -1:
								    childchild = &((*child)->left);
								    if((*childchild)->balance_factor == -1) 
								    { 
									    (*t)->balance_factor = 0; 
									    (*child)->balance_factor = 1;
									    (*childchild)->balance_factor = 0;
								    }
								    else if((*childchild)->balance_factor == 0)
								    {
									    (*t)->balance_factor = 0;
									    (*child)->balance_factor = 0;
									    (*childchild)->balance_factor = 0;
								    }
								    else if((*childchild)->balance_factor == 1)
								    {
									    (*t)->balance_factor = -1;
									    (*child)->balance_factor = 0;
									    (*childchild)->balance_factor = 0;
								    }

								    rotate_right(child);
								    rotate_left(t);
								    break;
							    case 1:
								    (*child)->balance_factor = 0;
								    (*t)->balance_factor = 0;
								    rotate_left(t);
								    break;
							    default:
								    assert(0);
								    break;
						    }
						    higher = false;
						    break;
					    default:
						    assert(0);
						    break;
				    }
			    }
			    else
				    assert(0);

			    child = t;
			    path.pop();
		    }
		    return true;
	    }
    }

    /**
     * lookup method, return true if found, false otherwise.
     */
    bool lookup(int key)
    {
	    __transaction_atomic {
		    Node * r = root;

		    while(r)
		    {
			    if(key == r->key)
				    return true;
			    else if (key < r->key)
				    r = r->left;
			    else 
				    r = r->right;	
		    }
		    return false;
	    }
    }

    /**
     *  To remove from the BST
     */
    bool remove(int key)
    {
	    __transaction_relaxed {
		    //create a stack to store the path of the address from the root to the inserted node.
		    stack<Node **> path;

		    Node ** cur = &root;
		    Node ** parent = NULL;


		    while(*cur)
		    {
			    if(key == (*cur)->key)
				    break;
			    else if (key < (*cur)->key)
			    {
				    parent = cur;
				    cur = &((*cur)->left);
			    }
			    else
			    {
				    parent = cur;
				    cur = &((*cur)->right);
			    }
			    path.push(parent);
		    }

		    if(!(*cur))//the key was not found
			    return false;
		    else//the key was present, so I can remove
		    {
			    Node ** child = cur;
			    Node * to_be_deleted = *child;
			    //the node we are trying to delete has no or one child
			    if((*child)->left != NULL && (*child)->right != NULL){
				    Node ** post = &((*child)->right);
				    parent = child;
				    path.push(parent);
				    while((*post)->left)
				    {
					    parent = post;
					    post = &((*post)->left);
					    path.push(parent);
				    }

				    pair<int, int> p((*post)->key, (*post)->val);
				    (*post)->key = (*child)->key;
				    (*post)->val = (*child)->val;
				    (*child)->key = p.first;
				    (*child)->val = p.second;
				    child = post;
				    to_be_deleted = *child;
			    }

			    //now it seems proper to delete child
			    if(parent == NULL)
			    {
				    if((*child)->left == NULL)
					    root = (*child)->right;
				    else if((*child)->right == NULL)
					    root = (*child)->left;
				    else
					    assert(0);
			    }
			    else if (&((*parent)->left) == child)
			    {
				    if((*child)->left == NULL)
					    (*parent)->left = (*child)->right;
				    else if ((*child)->right == NULL)
					    (*parent)->left = (*child)->left;
				    else
					    assert(0);
			    }
			    else if (&((*parent)->right) == child)
			    {
				    if((*child)->left == NULL)
					    (*parent)->right = (*child)->right;
				    else if ((*child)->right == NULL)
					    (*parent)->right = (*child)->left;
				    else
					    assert(0);
			    }
			    else
				    assert(0);
			    delete to_be_deleted;
			    to_be_deleted = NULL;

			    bool shorter = true;
			    while(!path.empty())
			    {
				    if(!shorter)
					    break;

				    Node ** t = path.top();
				    Node ** child2 = NULL, ** child3 = NULL;

				    if(&((*t)->left) == child)
				    {
					    switch((*t)->balance_factor)
					    {
						    case 0://orig balanced tree, left subtree gets shorter
							    (*t)->balance_factor = 1;
							    shorter = false;
							    break;
						    case -1://orig left subtree is higher,now equally high
							    (*t)->balance_factor = 0;
							    shorter = true;
							    break;
						    case 1://orig left subtree is lower, now gets even low, 
							    //may need to do balance
							    child2 = &((*t)->right);
							    switch((*child2)->balance_factor)
							    {
								    case 0:
									    (*child2)->balance_factor = -1;
									    rotate_left(t);
									    shorter = false;
									    break;
								    case 1:
									    (*t)->balance_factor = 0;
									    (*child2)->balance_factor = 0;
									    rotate_left(t);
									    shorter = true;
									    break;
								    case -1:
									    child3 = &((*child2)->left);
									    if(*child3 == NULL)
									    {
										    (*t)->balance_factor = 0;
										    (*child2)->balance_factor = 0;
									    }
									    else
									    {
										    switch((*child3)->balance_factor)
										    {
											    case 0:
												    (*t)->balance_factor = 0;
												    (*child2)->balance_factor = 0;
												    (*child3)->balance_factor = 0;
												    break;
											    case 1:
												    (*t)->balance_factor = -1;
												    (*child2)->balance_factor = 0;
												    (*child3)->balance_factor = 0;
												    break;
											    case -1:
												    (*t)->balance_factor = 0;
												    (*child2)->balance_factor = 1;
												    (*child3)->balance_factor = 0;
												    break;
											    default:
												    assert(0);
												    break;
										    }
									    }
									    rotate_right(child2);
									    rotate_left(t);
									    shorter = true;
									    break;
								    default:
									    assert(0);
									    break;

							    }
							    break;
						    default:
							    assert(0);
							    break;
					    }
				    }
				    else if (&((*t)->right) == child)
				    {
					    switch((*t)->balance_factor)
					    {
						    case 0://orig balanced tree, right subtree gets shorter
							    (*t)->balance_factor = -1;
							    shorter = false;
							    break;
						    case 1://orig right subtree is higher,now equally high
							    (*t)->balance_factor = 0;
							    shorter = true;
							    break;
						    case -1://orig right subtree is lower, now gets even low, 
							    //may need to do balance
							    child2 = &((*t)->left);
							    switch((*child2)->balance_factor)
							    {
								    case 0:
									    (*child2)->balance_factor = 1;
									    rotate_right(t);
									    shorter = false;
									    break;
								    case -1:
									    (*child2)->balance_factor = 0;
									    (*t)->balance_factor = 0;
									    rotate_right(t);
									    shorter = true;
									    break;
								    case 1:
									    child3 = &((*child2)->right);
									    if(*child3 == NULL)
									    {
										    (*t)->balance_factor = 0;
										    (*child2)->balance_factor = 0;
									    }
									    else
									    {
										    switch((*child3)->balance_factor)
										    {
											    case 0:
												    (*t)->balance_factor = 0;
												    (*child2)->balance_factor = 0;
												    (*child3)->balance_factor = 0;
												    break;
											    case -1:
												    (*t)->balance_factor = 1;
												    (*child2)->balance_factor = 0;
												    (*child3)->balance_factor = 0;
												    break;
											    case 1:
												    (*t)->balance_factor = 0;
												    (*child2)->balance_factor = -1;
												    (*child3)->balance_factor = 0;
												    break;
											    default:
												    assert(0);
												    break;
										    }
									    }
									    rotate_left(child2);
									    rotate_right(t);
									    shorter = true;
									    break;
								    default:
									    assert(0);
									    break;

							    }
							    break;
						    default:
							    assert(0);
							    break;
					    }
				    }
				    else
					    assert(0);

				    child = t;	
				    path.pop();
			    }
			    return true;
		    }
	    }
    }

    void print(){
//    	bool inconsistant = false;

	__transaction_relaxed {
	if(root == NULL)
	{
		printf("\n-------------------------\n");
		return;
	}

	queue<Node *> q1;
	queue<Node *> q2;
	q1.push(root);
	
	int mid = 55; //the offset of the middle of the console, default 60
	
	int x = root->left? 1<<root->left->height():0;
	int y = root->right? 1<<root->right->height():0;
	double ratio = ((x != 0) || (y != 0))?((double)x)/(x + y):0.5f;
	printf("ratio = %f\n", ratio);
	root->offset = (int)(10 + (mid<<1)*ratio);
	printf("root offset = %d\n", root->offset);
	while(1)
	{
		while(!q1.empty())
		{
			q2.push(q1.front());
			q1.pop();
		}

		if(q2.empty())
			break;

		while(!q2.empty())
		{
			int off = 1<<q2.front()->height();
			if(q2.front()->left)
			{	
				q2.front()->left->offset = q2.front()->offset - off;
				q1.push(q2.front()->left);
			}	
			if(q2.front()->right)
			{
				q2.front()->right->offset = q2.front()->offset + off;
				q1.push(q2.front()->right);
			}
			q2.pop();
		}
	}

	q1.push(root);
	while(1)
	{
		while(!q1.empty())
		{
			q2.push(q1.front());
			q1.pop();
		}

		if(q2.empty())
			break;

		Node * pre_node = NULL;
		string str = "";

		while(!q2.empty())
		{
			int off = 1<<q2.front()->height();

			if(pre_node == NULL)
			{
				for(int i = 0; i < q2.front()->offset; ++i)
					cout << " ";
				
				for(int i = 0; i < q2.front()->offset - off - 2; ++i)
					str += " ";
			}
			else
			{
				int pre_off = 1<<pre_node->height();
				for(int i = 0; i < q2.front()->offset - pre_node->offset; ++i)
					cout << " ";
				
				for(int i = 0; i < q2.front()->offset - pre_node->offset - off - pre_off - 4; ++i)
					str += " ";
			}

			string temp1 = "", temp2 = "";
			for(auto i = 0; i < off; ++i)
			{
				temp1 += "_";
				temp2 += " ";
			}

			if(q2.front()->left)
			{
				str += temp1;
				str += "| ";
				q1.push(q2.front()->left);
			}
			else
			{
				str += temp2;
				str += "  ";
			}

			cout << q2.front()->key << "," << q2.front()->balance_factor;
//			if(q2.front()->cal_balance_factor() != q2.front()->balance_factor)
//				inconsistant = true;
			str += " ";
			
			if(q2.front()->right)
			{
				str += " |";
				str += temp1;
				q1.push(q2.front()->right);
			}
			else
			{
				str += "  ";
				str += temp2;
			}

			pre_node = q2.front();
			q2.pop();
		}
		cout << endl << str << endl << endl;
	}
	
	printf("\n-------------------------\n");
//   	if(inconsistant)
//		pthread_exit((void*)1);
	}
    }
};

#endif // BST_HPP__
