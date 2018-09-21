#include <iostream>
#include <fstream>
#include "hash.h"
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void loadDict(const string &dictName, hashTable* dictionary){
	ifstream input(dictName.c_str());
	if(!input){
		cerr<<"Error: couldn't open "<<endl;
		exit(1);
	}
	string word;
	while(getline(input, word)){
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		int insertResult = dictionary->insert(word);
		if(insertResult==0){
			//cout<<"Add "<<word<<endl;
			int temp = 0;
		}
		else if (insertResult==1){
			cout<<"Already exist"<<endl;
		}
	}
}

void loadFile(const string &fileName, hashTable *dictionary){
	ifstream input(fileName.c_str());
	if(!input){
		cerr<<"Error: couldn't open "<<endl;
		exit(1);
	}
	string singleLine;
	while(getline(input, singleLine)){
		std::transform(singleLine.begin(), singleLine.end(), singleLine.begin(), ::tolower);
		string temp = "";
		for(int i=0; i<singleLine.length(); i++){
			if(48<singleLine[i],
	}
}

int checkWord(const string &word, hashTable *dictionary){
	if(dictionary->contains(word)){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	string dictName;
	cout<<"Enter name of dictionary: ";
	cin>>dictName;
	clock_t t1 = clock();
	hashTable dictionary(25000);
	loadDict(dictName, &dictionary);
	clock_t t2 = clock();
	double timeDiff = ((double)(t2 - t1) / CLOCKS_PER_SEC);
	cout<<"Total time (in seconds) to load dictionary: "<<timeDiff<<endl;
	string inputName;
	cout<<"Enter name of input file: ";
	cin>>inputName;
	string outputName;
	cout<<"Enter name of output file: ";
	cin>>outputName;
	
}
