#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
#include <iterator>
void mergeSort1(list<Data *> &l, int field);
void radixSort1(list<Data *> &l);
void countSort1(list<Data *> &l, int exp);

void sortDataList(list<Data *> &l, int field) {
  // Fill in this function
	if(field==1){
		mergeSort1(l,field);
	}
	else if(field ==2){
		radixSort1(l);
	}	
	cout<<"*****"<<endl;	
}

void mergeSort1(list<Data *> &l, int field){
	list<Data *>::iterator it1=l.begin();
	list<Data *>::iterator it2=l.begin();
	it1=next(it1,1);
	for(int i=1;i<10;i++){
		int j=i-1;
		it2=l.begin();
		it2=next(it2,i-1);
		for(j;j>=0;j--){
			if((*it1)->val1>=(*it2)->val1){
				l.insert(next(it2,1),*it1);
				it1=l.erase(it1);
				break;
			}
			else{
				if(j!=0){
					it2=prev(it2,1);
				}
				else{
					l.insert(it2,*it1);
					it1=l.erase(it1);
				}
			}
		}
	}
	it1=next(l.begin(),10);
	while(it1!=l.end()){		//The last element may be skipped?
		it2=prev(it1,1);
		for(int i=0;i<10;i++){
			if((*it1)->val1>=(*it2)->val1){
				l.insert(next(it2,1),*it1);
				it1=l.erase(it1);
				break;
			}
			else{
				if(i!=9){
					it2=prev(it2,1);
				}
				else{
					l.insert(it2,*it1);
					it1=l.erase(it1);
				}
			}
		}	
	}
}

void radixSort1(list<Data *> &l){
	int shift=0;
	countSort1(l,shift);
}

void countSort1(list<Data *> &l,int shift){
	unsigned int listSize=l.size();
	Data** dataArray=new Data*[listSize];
	Data** tempArray=new Data*[listSize]; 
	for(unsigned int i=0;i<listSize;i++){
		dataArray[i]=l.front();
		l.pop_front();
		if(l.empty()){
			break;
		}
	}
	for(shift;shift<32;shift+=16){
		unsigned int count[65536]={};
		for(unsigned int i=0;i<listSize;i++){
			count[((dataArray[i]->val2)>>shift)&0xFFFF]++;
		}
		unsigned int accArray[65536]={};
		accArray[0]=count[0];
		for(int i=1;i<65536;i++){
			accArray[i]=accArray[i-1]+count[i];
		}
		for(unsigned int i=listSize-1;i>=0;i--){
			tempArray[accArray[((dataArray[i]->val2)>>shift)&0xFFFF]-1]=dataArray[i];
			int test=accArray[((dataArray[i]->val2)>>shift)&0xFFFF]--;
			if(i==0){
				break;
			}
		}
		for(unsigned int i=0;i<listSize;i++){
			dataArray[i]=tempArray[i];
		}
	}
	for(unsigned int i=0;i<listSize;i++){
		l.push_back(dataArray[i]);
	}
}
