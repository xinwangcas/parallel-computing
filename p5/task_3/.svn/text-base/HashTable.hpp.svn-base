#include <iostream>

class HashEntry{
public:
	int key;
	int value;
	HashEntry* next;
	HashEntry(int k, int v) : key(k), value(v), next(NULL) {
	}
};

class HashTable{
	int hash(int key) {
		std::hash<int> k_hash;
		return k_hash(key) % TableSize;
	}
public:
	HashEntry** table;
	int TableSize;

	HashTable(int _size = 1024): TableSize(_size) {
		table = new HashEntry*[TableSize];		
		for(int i = 0 ; i < TableSize ; i ++ ){
			table[i] = NULL;
		}
	}

	bool isSane() {
		return true;
	}

	void print() {
		__transaction_relaxed {
			for(int i = 0; i < TableSize; ++i) {
				if(table[i] != NULL) {
					cout << i << ": ";
					for (HashEntry * e = table[i]; e != NULL; e = e->next) {
						cout << "[" << e->key << ", " << e->value << "]";
					}
					cout << endl;
				}
			}
		}
	}

	int lookup(int key) {
		int num = hash(key);

		__transaction_atomic {
			if(table[num] == NULL){
				return -1;
			}
			else{
				HashEntry* entry = table[num];
				while(entry != NULL) {
					if(entry->key == key){
						return entry->value;
					}
					entry = entry->next;
				}

				return -1;
			}
		}
	}

	bool insert(int key, int val) {
		int num = hash(key);

		__transaction_atomic {
			if(table[num] == NULL){
				table[num] = new HashEntry(key, val);
				return true;
			}
			else{
				HashEntry * entry = table[num];
				HashEntry * pre_entry = NULL;
				while (entry != NULL) {
					if(entry->key >= key)
						break;
					pre_entry = entry;
					entry = entry->next;
				}

				if(entry == NULL) {
					pre_entry->next = new HashEntry(key, val);
					return true;
				}
				else if (entry->key == key)	//the key has already in the table
					return false;
				else {	//entry->key > key
					HashEntry * e = new HashEntry(key, val);
					e->next = entry;
					if(pre_entry)
						pre_entry->next = e;
					else
						table[num] = e;
					return true;
				}
			}
		}
	}

	bool remove(int key) {
		int num = hash(key);

		__transaction_atomic {
			if(table[num] == NULL){
				return false;
			}
			else{
				HashEntry* entry = table[num];
				HashEntry* pre_entry = NULL;

				while(entry != NULL) {
					if(entry->key == key)
						break;
					pre_entry = entry;
					entry = entry->next;
				}

				if(entry != NULL) {	//found the key
					if(pre_entry == NULL){
						table[num] = NULL;
						delete entry;
						return true;
					}
					else{
						pre_entry->next = entry->next;
						delete entry;
						return true;
					}
				}else
					return false;
			}
		}
	}

	~HashTable() {
		delete[] table;
	}
};
