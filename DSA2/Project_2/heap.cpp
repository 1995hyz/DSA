#include "heap.h"
#include "hash.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

heap::heap(int size){
	capacity = size;
	currentSize = 0;
	searchTable = new hashTable(capacity * 2);
	data.resize(capacity+1);
}

int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}

void heap::percolateDown(int hole){
	int child = 0;
	node temp = data[hole];
	for(; hole*2 <= currentSize; hole=child){
		child = hole * 2;
		if((child != currentSize) && (data[child+1].key < data[child].key)){
			child++;
		}
		if(data[child].key < temp.key){
			data[hole] = data[child];
			searchTable->setPointer(data[hole].id, &data[hole]);
		}
		else{	
			break;
		}
	}
	data[hole] = temp;
	searchTable->setPointer(data[hole].id, &data[hole]);
}

int heap::insert(const string &id, int key, void* pv){
	if(currentSize == capacity){
		return 1;
	}
	if(searchTable->contains(id)){
		return 2;
	}
	int hole = ++currentSize;
	for(; hole>1 && key<data[hole/2].key; hole/=2){
		data[hole] = data[hole/2];
		searchTable->setPointer(data[hole].id, &data[hole]);
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
	node* pn = static_cast<node *> (searchTable->getPointer(id));
	int oldKey = pn->key;
	if(key < oldKey){
		int hole = getPos(pn);
		data[hole].key = key;
		node temp = data[hole];
		for(; hole>1 && key<data[hole/2].key; hole/=2){
			data[hole] = data[hole/2];
			searchTable->setPointer(data[hole].id, &data[hole]);
		}
		data[hole] = temp;
		searchTable->setPointer(data[hole].id, &data[hole]);
	}
	else if(key > oldKey){
		int position = getPos(pn);
		data[position].key = key;
		percolateDown(position);
	}
	return 0;
}

int heap::deleteMin(string *pId, int *pKey, void *ppData){
	if(currentSize == 0){
		return 1;
	}
	if(! (pId==NULL)){
		*pId = data[1].id;
	}
	if(! (pKey==NULL)){
		*pKey = data[1].key;
	}
	if(! (ppData==NULL)){
		*(void **)ppData = data[1].pv;
	}
	searchTable->remove(data[1].id);
	data[1] = data[currentSize--];
	searchTable->setPointer(data[1].id, &data[1]);
	percolateDown(1);
	data[currentSize+1].id = "";
	data[currentSize+1].key = 0;
	data[currentSize+1].pv = NULL;
	return 0;
}

int heap::remove(const string &id, int *pKey, void *ppData){
	if(! searchTable->contains(id)){
		return 1;
	}
	int oldKey = (static_cast<node*> (searchTable->getPointer(id)))->key;
	int minKey = data[1].key - 1;
	setKey(id, minKey);
	*pKey = oldKey;
	deleteMin(NULL, NULL, ppData);
	return 0;
}
