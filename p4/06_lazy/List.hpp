#ifndef LIST_HPP__
#define LIST_HPP__
#include <chrono>
#include <unistd.h>
#include <memory>
#include "tbb/concurrent_queue.h"

using namespace std;
/**
 *  A simple sorted linked list holding integers.  Note that we insert a
 *  "dummy" node at the head of each list, which makes the rest of the code
 *  much simpler.
 */

template<typename T>
class object_pool{
	std::shared_ptr<tbb::concurrent_bounded_queue<std::shared_ptr<T>>> pool;
	public:
	object_pool()
		:pool(new tbb::concurrent_bounded_queue<std::shared_ptr<T>>()){}
	std::shared_ptr<T> create()
	{
		std::shared_ptr<T> obj;
		if(!pool->try_pop(obj))
			obj = std::make_shared<T>();
		return std::shared_ptr<T>(obj.get(),[=](T*){pool->push(obj);});
	}

};

class List
{
	/**
	 *  Type for the nodes of the list
	 */
	struct Node
	{
		/**
		 *  The value stored at this node
		 */
		int   val;

		/**
		 *  The next entry
		 */
		Node* next;
		volatile int exclusion = 0;

		void lock(){
			int delay = 2;
			while(true){
				while(exclusion);
				if(!__sync_lock_test_and_set(&exclusion,1))
					break;
				sleep(rand()%delay);
				if(delay < 1024)
					delay = 2*delay;
			}
		}

		void unlock(){
			exclusion = 0;
		}
		bool marked = false;
		/**
		 *  Basic constructor
		 */
		Node(int _val = -1, Node* _next = NULL) : val(_val), next(_next) { }
	};

	/**
	 *  The head of the list
	 */



	Node* sentinel;

	bool validate(Node* prev, Node* curr){
		return !prev->marked && !curr->marked && prev->next == curr;
	}

	bool validate2(Node* prev, Node* curr) {
		return !prev->marked&&curr==NULL;
	}

	public:

	/**
	 * constructor just makes a sentinel for the data structure
	 */
	List() : sentinel(new Node()) { }

	/**
	 * simple sanity check: make sure all elements of the list are in sorted
	 * order
	 */
	bool isSane(void) const
	{
		Node* prev = sentinel;
		Node* curr = prev->next;

		while (curr != NULL) {
			if (prev->val >= curr->val)
				return false;
			prev = curr;
			curr = curr->next;
		}
		return true;
	}

	/**
	 * insert method; find the right place in the list, add val so that it is
	 * in sorted order; if val is already in the list, exit without inserting
	 */
	void insert(int val)
	{
		while(true) {
			// traverse the list to find the insertion point
			Node* prev = sentinel;
			Node* curr = prev->next;
			while (curr != NULL) {
				if (curr->val >= val)
					break;
				prev = curr;
				curr = prev->next;
			}

			if(prev!=NULL)
				prev->lock();
			if(curr != NULL){
				curr->lock();
				if(validate(prev, curr)){
					// now insert new_node between prev and curr
					if (((curr->val) > val)) {
						// create the new node
						Node* i = (Node*)malloc(sizeof(Node));
						i->val = val;
						i->next = curr;
						// insert it
						prev->next = i;
					}
					curr->unlock();
					prev->unlock();
					return;
				}
				curr->unlock();
			}
			if(curr == NULL){
				if(validate2(prev, curr)){
					// create the new node
					Node* i = (Node*)malloc(sizeof(Node));
					i->val = val;
					i->next = NULL;
					// insert it
					prev->next = i;
					prev->unlock();
					return;
				}
			}
			prev->unlock();
		}
	}

	/**
	 * lookup method: just traverse the list in order, and see if we find the
	 * val
	 */
	bool lookup(int val)
	{
		Node* curr = sentinel->next;

		while (curr != NULL) {
			if (curr->val >= val)
				break;
			curr = curr->next;
		}

		return ((curr != NULL) && (curr->val == val && !curr->marked));
	}

	/**
	 *  To remove from the list, we need to keep a pointer to the previous
	 *  node, too.  Note that this is much easier on account of us having a
	 *  sentinel
	 */
	void remove(int val)
	{
		while(true){
			Node* prev = sentinel;
			Node* curr = prev->next;
			while(curr != NULL){
				if(curr->val >= val)
					break;
				prev = curr;
				curr = prev->next;
			}

			prev->lock();
			if(curr != NULL){
				curr->lock();
				if(validate(prev,curr)){
					if(curr->val == val){
						curr->marked = true;
						prev->next = curr->next;
						curr->unlock();
						prev->unlock();
						//free(curr);
						return;
					}
					else{
						curr->unlock();
						prev->unlock();
						return;
					}
				}
				curr->unlock();
			}
			if(curr == NULL){
				prev->unlock();
				return;
			}
			prev->unlock();
		}
	}

};

#endif // LIST_HPP__
