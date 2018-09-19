#include "hash.h"
#include <iostream>

hashTable::hashTable(int size){
	int actualSize = getPrime(size);
	data.resize(actualSize);
	capacity = actualSize;
}

int checkPrime(int number){
	int i = 2;
	for(i; i<number; i++){
		if(number%i == 0){
			return 1;
		}
	}
	return 0;
}

unsigned int hashTable::getPrime(int size){
	int i = 2;
	int temp = size;
	while(true){
		if(checkPrime(temp) == 0){
			break;
		}
		temp++;
	}
	std::cout<<"Prime Number: "<<temp<<std::endl;
	return temp;
}

int hashTable::hash(const std::string &key){
	int hashValue = 0;
	int i = 0;
	for(i; i<key.length(); i++){
		hashValue = 37 * hashValue + key[i];
	}
	hashValue %= capacity;
	if (hashValue < 0){
		hashValue += capacity;
	}
	return hashValue;
}

int hashTable::insert(const std::string &key, void *pv){
	int hashValue = hash(key);
	hashItem *item = new hashItem();
	item->key = key;
	item->isOccupied = true;
	item->pv = pv;
	for(int i=hashValue; i<capacity; i++){
		if (!data[i].isOccupied){
			data[hashValue] = *item;
		}
	}
	std::cout<<"Add Successfully"<<std::endl;
	filled++;
}

int hashTable::findPos(const std::string &key){
	int hashValue = hash(key);
	return 0;
}

