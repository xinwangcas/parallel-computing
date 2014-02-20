#include <iostream>
#include <assert.h>

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
private:
	bool check_buckets_size() {
		for(int i = 0; i < TableSize; ++i) {
			if (table[i] != NULL) {
				int count = 0;
				for (HashEntry * e = table[i]; e != NULL; e = e->next) {
					count++;
				}
				if(count > BucketCapacity)
					return false;
			}
		}
		return true;
	}

	void resize() {
		while(check_buckets_size() == false) {
			HashTable * new_table = new HashTable(TableSize << 1);

			for(int i = 0; i < TableSize; ++i) {
				if (table[i] != NULL) {
					for(HashEntry * e = table[i]; e != NULL; e = e->next) {
						new_table->insert(e->key, e->value);
					}
				}
			}
			delete this->table;
			delete this->buckets_size;

			this->table = new_table->table;
			this->buckets_size = new_table->buckets_size;
			this->TableSize = new_table->TableSize;
		}
	}
public:
	HashEntry** table;
	int TableSize;
	int BucketCapacity;
	
	int * buckets_size;

	HashTable(int _size = 1024, int _bucketCap = 8) : TableSize(_size), BucketCapacity(_bucketCap) {
		assert(BucketCapacity > 0);
		assert(TableSize > 0);

		table = new HashEntry*[TableSize];
		buckets_size = new int[TableSize];

		for(int i = 0 ; i < TableSize ; i ++ ){
			table[i] = NULL;
			buckets_size[i] = 0;
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
				buckets_size[num]++;
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
					buckets_size[num]++;
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
					buckets_size[num]++;
				}
			}
		}

		__transaction_atomic {
			resize();
			return true;
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
					if(pre_entry == NULL)
						table[num] = NULL;
					else
						pre_entry->next = entry->next;

					delete entry;
					buckets_size[num]--;
					return true;
				}else
					return false;
			}
		}
	}

	~HashTable() {
		delete[] table;
		delete[] buckets_size;
	}
};
