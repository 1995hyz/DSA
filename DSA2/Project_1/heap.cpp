#include "heap.h"
#include "hash.h"
#include <iostream>

using namespace std;

heap::heap(int capacity){
	capacity = capacity;
	currentSize = 0;
	searchTable = new hashTable(capacity * 2);
	data.resize(capacity);
}

int heap::insert(const string &id, int key, void* pv){
	if(currentSize == capacity){
		return 1;
	}
	if(searchTable->contains(id)){
		return 2;
	}
	int hole = currentSize++;
	for(; hole>1 && key<data[hole].key; hole/=2){
		data[hole] = data[hole/2];
	}
	data[hole].key = key;
	data[hole].id = id;
	data[hole].pv = pv;
	searchTable->insert(id, &data[hole]);
	return 0;
}

int heap::setKey(const string &id, int key){
	if(! searchTable->contains(id)){
		return 1;
	}
}

int heap::deleteMin(string *pId, int *pKey, void *ppData){
	
}

int heap::remove(const string &id, int *pKey, void *ppData){
	
}
