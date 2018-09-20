#include <iostream>
#include <fstream>
#include "hash.h"
#include <string>
#include <cstdlib>

using namespace std;

void loadDict(const string &dictName){
	ifstream input(dictName.c_str());
	if(!input){
		cerr<<"Error: couldn't open "<<endl;
		exit(1);
	}
	string word;
	hashTable dictionary(5);
	while(getline(input, word)){
		int insertResult = dictionary.insert(word);
		if(insertResult==0){
			//cout<<"Add "<<word<<endl;
			int temp = 0;
		}
		else if (insertResult==1){
			cout<<"Already exist"<<endl;
		}
	}
}

int main(){
	string dictName;
	cout<<"Enter name of dictionary: ";
	cin>>dictName;
	loadDict(dictName);
}
