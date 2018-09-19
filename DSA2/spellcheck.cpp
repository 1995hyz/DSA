#include <iostream>
#include "hash.h"
#include <string>

int main(){
	const std::string str1 = "Hello World!";
	hashTable hash_element(10);
	hash_element.insert(str1);
	return 0 ;
}
