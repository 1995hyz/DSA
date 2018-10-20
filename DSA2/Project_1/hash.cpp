#include "hash.h"
#include <iostream>
#include <vector>

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
	if(contains(key)){
		return 1;
	}
	int hashValue = hash(key);
	for(int i=hashValue; i<capacity; i++){
		if (!data[i].isOccupied){
			data[i].key = key;
			data[i].isOccupied = true;
			data[i].pv = pv;
			data[i].isDeleted = false;
			break;
		}
		if(i == (capacity-1)){
			i=-1;
		}
	}
	filled++;
	if(filled*2 > capacity){
		if(!rehash()){
			return 2;
		}
	}
	return 0;
}

int hashTable::findPos(const std::string &key){
	int position = hash(key);
	while(data[position].isOccupied){
		if(data[position].key == key){
			return position;
		}
		else{	
			if(position >= capacity-1){
				position = 0;
			}
			else{
				position++;
			}
			continue;
		}
	}
	return -1;
}

bool hashTable::contains(const std::string &key){
	if(findPos(key) != -1){
		return true;
	}
	return false;
}

bool hashTable::rehash(){
	try{
	std::vector<hashItem> old_data = data;
	int upgradeSize=getPrime(capacity*2);
	int oldCapacity = capacity;
	data.resize(upgradeSize);
	//Clear original hashtable.
	for(int i=0; i<oldCapacity; i++){
		data[i].key = "";
		data[i].isOccupied = false;
		data[i].isDeleted = false;
		data[i].pv = NULL;
	}
	capacity = upgradeSize;
	//Refill to new hashtable
	for(int i=0; i<oldCapacity; i++){
		if(old_data[i].isOccupied){
			int hashValue = hash(old_data[i].key);
			for(int j=hashValue; j<capacity; j++){
				if (!data[j].isOccupied){
					data[j].key = old_data[i].key;
					data[j].isOccupied = true;
					data[j].pv = old_data[i].pv;
					data[j].isDeleted = false;
					break;
				}
				if(j==(capacity-1)){
					j=-1;
				}
			}
		}
	}
	return true;
	}catch(...){
		return false;
	}
}
