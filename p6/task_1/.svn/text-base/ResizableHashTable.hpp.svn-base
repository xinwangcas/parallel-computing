#include <iostream>
#include <assert.h>
#include <functional>
#include <utility>

using namespace std;

template <class K, class V>
class HashEntry {
	pair<K,V> kvpair;
public:
	HashEntry* next;
	HashEntry(K k, V v) : kvpair(k, v), next(NULL) {
	}
	K key(){
		return kvpair.first;
	}
	V value(){
		return kvpair.second;
	}
};


template <class K, class V>
class HashTable{
private:
	bool check_buckets_size() {
		for(int i = 0; i < TableSize; ++i) {
			if (table[i] != NULL) {
				int count = 0;
				for (HashEntry<K,V> * e = table[i]; e != NULL; e = e->next) {
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
			HashTable<K,V> * new_table = new HashTable<K,V>(TableSize << 1);

			for(int i = 0; i < TableSize; ++i) {
				if (table[i] != NULL) {
					for(HashEntry<K,V> * e = table[i]; e != NULL; e = e->next) {
						new_table->insert(e->key(), e->value());
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

	int hash(K key) {
		std::hash<K> k_hash;
		return k_hash(key) % TableSize;
	}
public:
	HashEntry<K,V>** table;
	int TableSize;
	int BucketCapacity;
	
	int * buckets_size;

	HashTable(int _size = 1024, int _bucketCap = 8) : TableSize(_size), BucketCapacity(_bucketCap) {
		assert(BucketCapacity > 0);
		assert(TableSize > 0);

		table = new HashEntry<K,V>*[TableSize];
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
					for (HashEntry<K,V> * e = table[i]; e != NULL; e = e->next) {
						cout << "[" << e->key() << ", " << e->value() << "]";
					}
					cout << endl;
				}
			}
		}
	}

	V lookup(K key) {
		int num = hash(key);

		__transaction_relaxed {
			if(table[num] == NULL){
				return V();
			}
			else{
				HashEntry<K,V>* entry = table[num];
				while(entry != NULL) {
					if(entry->key() == key){
						return entry->value();
					}
					entry = entry->next;
				}

				return V();
			}
		}
	}

	bool insert(K key, V val) {
		int num = hash(key);

		__transaction_relaxed {
			if(table[num] == NULL){
				table[num] = new HashEntry<K,V>(key, val);
				buckets_size[num]++;
				return true;
			}
			else{
				HashEntry<K,V> * entry = table[num];
				HashEntry<K,V> * pre_entry = NULL;
				while (entry != NULL) {
					if(entry->key() >= key)
						break;
					pre_entry = entry;
					entry = entry->next;
				}

				if(entry == NULL) {
					pre_entry->next = new HashEntry<K,V>(key, val);
					buckets_size[num]++;
				}
				else if (entry->key() == key)	//the key has already in the table
					return false;
				else {	//entry->key > key
					HashEntry<K,V> * e = new HashEntry<K,V>(key, val);
					e->next = entry;
					if(pre_entry)
						pre_entry->next = e;
					else
						table[num] = e;
					buckets_size[num]++;
				}
			}
		}

		__transaction_relaxed {
			resize();
			return true;
		}
	}

	bool remove(K key) {
		int num = hash(key);

		__transaction_relaxed {
			if(table[num] == NULL){
				return false;
			}
			else{
				HashEntry<K,V>* entry = table[num];
				HashEntry<K,V>* pre_entry = NULL;

				while(entry != NULL) {
					if(entry->key() == key)
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
