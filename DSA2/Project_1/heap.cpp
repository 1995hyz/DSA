#include "heap.h"
#include "hash.h"
#include <iostream>

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
		searchTable->setPointer(id, &data[hole]);
	}
	data[hole].key = key;
	data[hole].id = id;
	data[hole].pv = pv;
	searchTable->insert(id, &data[hole]);
	
	for(int i=0; i<capacity+1; i++){
		cout<<data[i].id<<endl;
	}

	return 0;
}

int heap::setKey(const string &id, int key){
	if(! searchTable->contains(id)){
		return 1;
	}
	node* pn = static_cast<node *> (searchTable->getPointer(id));
	int oldKey = pn->key;
	cout<<"oldKey: "<<oldKey<<"newKey: "<<key<<endl;
	if(key < oldKey){
		int hole = getPos(pn);
		data[hole].key = key;
		node temp = data[hole];
		for(; hole>1 && key<data[hole/2].key; hole/=2){
			data[hole] = data[hole/2];
			searchTable->setPointer(id, &data[hole]);
		}
		data[hole] = temp;
		searchTable->setPointer(id, &data[hole]);
	}
	else if(key > oldKey){
		int position = getPos(pn);
		data[position].key = key;
		percolateDown(position);
	}

	for(int i=0; i<capacity+1; i++){
		cout<<data[i].id<<endl;
	}

	return 0;
}

int heap::deleteMin(string *pId, int *pKey, void *ppData){
	
}

int heap::remove(const string &id, int *pKey, void *ppData){
	
}
