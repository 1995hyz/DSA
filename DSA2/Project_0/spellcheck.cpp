#include <iostream>
#include <fstream>
#include "hash.h"
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int checkWord(const string &word, hashTable *dictionary){
	if(dictionary->contains(word)){
		return 1;
	}
	else{
		return 0;
	}
}

//This function load a dictionary into a hashtable.
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
			int temp = 0;
		}
		else if(insertResult==2){
			cerr<<"Error: rehash fails"<<endl;
			exit(1);
		}
	}
}

//This function loads a file and check every word with the dictionary.
void loadFile(const string &fileName, hashTable *dictionary){
	ifstream input(fileName.c_str());
	if(!input){
		cerr<<"Error: couldn't open "<<endl;
		exit(1);
	}
	string singleLine;
	unsigned int lineCounter = 1;
	while(getline(input, singleLine)){
		std::transform(singleLine.begin(), singleLine.end(), singleLine.begin(), ::tolower);
		string temp = "";
		int wordCounter = 0;
		bool containNumber = false;
		bool numberFlag = false;
		for(int i=0; i<singleLine.length(); i++){
			containNumber = (47<singleLine[i] && singleLine[i]<58);
			if(containNumber){
				numberFlag = true;
			}
			if(singleLine[i]==39 || singleLine[i]==45 || containNumber || (96<singleLine[i] && singleLine[i]<123)){
				temp = temp + singleLine[i];
				wordCounter++;
			}
			else{
				if(!temp.empty()){
					if(wordCounter > 20){
						cout<<"Long word at line "<<lineCounter<<", starts: "<<temp.substr(0,20)<<endl;
					}
					else{	
						if(!numberFlag && !checkWord(temp, dictionary)){
							cout<<"Unknown word at line "<<lineCounter<<": "<<temp<<endl;
						}
					}
				}
				temp = "";
				wordCounter = 0;
				numberFlag = false;
			}
		}
		if(!temp.empty()){
			if(wordCounter > 20){
				cout<<"Long word at line "<<lineCounter<<", starts: "<<temp.substr(0,20)<<endl;
			}
			else{	
				if(!numberFlag && !checkWord(temp, dictionary)){
					cout<<"Unknown word at line "<<lineCounter<<": "<<temp<<endl;
				}
			}
			temp = "";
		}
		lineCounter++;
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
	clock_t t3 = clock();
	ofstream output(outputName.c_str());
	if(!output){
		cerr<<"Error: couldn't open: "<<outputName<<endl;
		exit(1);
	}
	streambuf* oldCout = cout.rdbuf();
	streambuf* newCout = output.rdbuf();
	cout.rdbuf(newCout);
	loadFile(inputName, &dictionary);
	cout.rdbuf(oldCout);
	output.close();
	clock_t t4 = clock();
	double timeDiff2 = ((double)(t4 - t3) / CLOCKS_PER_SEC);
	cout<<"Total time (in seconds) to check document: "<<timeDiff2<<endl;
	return 0;
}
