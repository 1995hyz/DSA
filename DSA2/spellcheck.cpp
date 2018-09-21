#include <iostream>
#include <fstream>
#include "hash.h"
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void loadDict(const string &dictName){
	ifstream input(dictName.c_str());
	if(!input){
		cerr<<"Error: couldn't open "<<endl;
		exit(1);
	}
	string word;
	hashTable dictionary(25000);
	while(getline(input, word)){
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
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
	clock_t t1 = clock();
	loadDict(dictName);
	clock_t t2 = clock();
	double timeDiff = ((double)(t2 - t1) / CLOCKS_PER_SEC);
	cout<<"Total time (in seconds) to load dictionary: "<<timeDiff<<endl;
}
