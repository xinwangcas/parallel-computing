#ifndef LIST_HPP__
#define LIST_HPP__
#include <mutex>
#include <chrono>
#include <unistd.h>


/**
 *  A simple sorted linked list holding integers.  Note that we insert a
 *  "dummy" node at the head of each list, which makes the rest of the code
 *  much simpler.
 */
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


		/**
		 *  Basic constructor
		 */
		Node(int _val = -1, Node* _next = NULL) : val(_val), next(_next) { }
	};

	/**
	 *  The head of the list
	 */
	Node* sentinel;

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
		// traverse the list to find the insertion point
		sentinel->lock();
		Node* prev =sentinel;
		Node* curr = prev->next;
		if(curr!=NULL)
			curr->lock();
		while (curr != NULL) {
			if (curr->val >= val)
				break;
			prev->unlock();
			prev = curr;
			curr = prev->next;
			if(curr!=NULL)
				curr->lock();
		}

		// now insert new_node between prev and curr
		//
		// NB: if the test fails, it means we quit the above loop on account
		// of /finding/ val, in which case we just exit
		if (!curr || ((curr->val) > val)) {
			// create the new node
			Node* i = (Node*)malloc(sizeof(Node));
			i->val = val;
			i->next = curr;
			prev->next = i;
			// insert it
		}
		if(curr!=NULL)
			curr->unlock();
		if(prev!=NULL)
			prev->unlock();
	}

	/**
	 * lookup method: just traverse the list in order, and see if we find the
	 * val
	 */
	bool lookup(int val)
	{
		sentinel->lock();
		Node* prev = sentinel;
		Node* curr = prev->next;
		if(curr!=NULL)
			curr->lock();
		while (curr != NULL) {
			if (curr->val >= val)
				break;
			prev->unlock();
			prev = curr;
			curr = prev->next;
			if(curr!=NULL)
				curr->lock();
		}

		bool tmp =  ((curr != NULL) && (curr->val == val));
		if(curr!=NULL)
			curr->unlock();
		if(prev!=NULL)
			prev->unlock();
		return  tmp;
	}

	/**
	 *  To remove from the list, we need to keep a pointer to the previous
	 *  node, too.  Note that this is much easier on account of us having a
	 *  sentinel
	 */
	void remove(int val)
	{
		// find the node whose val matches the request
		sentinel->lock();
		Node* prev = sentinel;
		Node* curr = prev->next;
		if(curr!=NULL)
			curr->lock();
		while (curr != NULL) {
			// if we find the node, disconnect it and end the search
			if (curr->val == val) {
				prev->next = curr->next;

				// delete curr...
				free(curr);
				break;
			}
			else if (curr->val > val) {
				// this means the search failed
				break;
			}
			// advance one node
			prev->unlock();
			prev = curr;
			curr = prev->next;
			if(curr!=NULL)
			curr->lock();
		}
		if(curr!=NULL)
			curr->unlock();
		prev->unlock();
	}
};

#endif // LIST_HPP__
