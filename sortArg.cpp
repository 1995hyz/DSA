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
#include <cstring>
void insertSort1(list<Data *> &l);
void radixSort1(list<Data *> &l);
void radixSort2(list<Data *> &l);
void radixSort3(list<Data *> &l);
void fillArray(list<Data *> &l,Data** filledArray,int arraySize);
void swap(Data** d1,Data** d2);

void sortDataList(list<Data *> &l, int field) {
  // Fill in this function
	if(field==1){
		insertSort1(l);
	}
	else if(field==2){
		radixSort1(l);
	}
	else if(field==3){
		radixSort2(l);
	}
	else if(field==4){
		radixSort3(l);
	}	
}

void insertSort1(list<Data *> &l){
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
	while(it1!=l.end()){		
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
	unsigned int listSize=l.size();
	Data** dataArray=new Data*[listSize];
	Data** tempArray=new Data*[listSize];
	fillArray(l,dataArray,listSize);
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

void radixSort2(list<Data *> &l){
	unsigned int listSize=l.size();
	Data** dataArray=new Data*[listSize];
	Data** tempArray=new Data*[listSize];
	fillArray(l,dataArray,listSize);
	unsigned int count[94]={};
	for(unsigned int i=0;i<listSize;i++){
		count[int(dataArray[i]->val3)-33]++;
	}
	unsigned int accArray[94]={};
	accArray[0]=count[0];
	for(int i=1;i<94;i++){
		accArray[i]=accArray[i-1]+count[i];
	}
	for(unsigned int i=listSize-1;i>=0;i--){
		tempArray[accArray[int(dataArray[i]->val3)-33]-1]=dataArray[i];
		int test=accArray[int(dataArray[i]->val3)-33]--;
		if(i==0){
			break;
		}
	}
	for(unsigned int i=0;i<listSize;i++){
		dataArray[i]=tempArray[i];
	}
	for(unsigned int i=0;i<listSize;i++){
		l.push_back(dataArray[i]);
	}
}

unsigned int countHuge[6118750];
unsigned int accArrayHuge[6118750];
void radixSort3(list<Data *> &l){
	unsigned int listSize=l.size();
	Data** dataArray=new Data*[listSize];
	Data** tempArray=new Data*[listSize];
	fillArray(l,dataArray,listSize);
	for(int shift=0;shift>=0;shift-=3){
		for(unsigned int i=0;i<listSize;i++){
			char tempStr[4]={};
			strcpy(tempStr,((dataArray[i]->val4.substr(shift,3)).c_str()));
			unsigned int* pointer=reinterpret_cast<unsigned int*>(tempStr);
			countHuge[((__builtin_bswap32(*pointer))>>8)-0x212121]++;
		}
		accArrayHuge[0]=countHuge[0];
		for(int i=1;i<6118750;i++){
			accArrayHuge[i]=accArrayHuge[i-1]+countHuge[i];
		}
		for(unsigned int i=listSize-1;i>=0;i--){
			char tempStr[4]={};
			strcpy(tempStr,(dataArray[i]->val4.substr(shift,3)).c_str());
			unsigned int* pointer=reinterpret_cast<unsigned int*>(tempStr);
			tempArray[accArrayHuge[((__builtin_bswap32(*pointer))>>8)-0x212121]-1]=dataArray[i];
			int test=accArrayHuge[((__builtin_bswap32(*pointer))>>8)-0x212121]--;
			if(i==0){
				break;
			}
		}
		for(unsigned int i=0;i<listSize;i++){
			dataArray[i]=tempArray[i];
		}
		for(unsigned int i=0;i<6118750;i++){
			accArrayHuge[i]=0;
		}
	}
	accArrayHuge[0]=countHuge[0];
	for(int i;i<6118750;i++){
		accArrayHuge[i]=accArrayHuge[i-1]+countHuge[i];
	}
	for(int i=0;i<6118750;i++){
		int j=countHuge[i];
		if(j==1){
			continue;
		}
		else{
			int range=accArrayHuge[i];
			for(int k=0;k<j-1;k++){
				for(int n=0;n<j-k-1;n++){
					if((dataArray[range-j+n]->val4).compare(0,25,dataArray[range-j+n+1]->val4)>0){
						swap(&dataArray[range-j+n],&dataArray[range-j+n+1]);
					}
				}
			}
		}
	}
	for(unsigned int i=0;i<listSize;i++){
		l.push_back(dataArray[i]);
	}
	delete dataArray;
	delete tempArray;
}

void fillArray(list<Data *> &l, Data** filledArray,int arraySize){
	for(unsigned int i=0;i<arraySize;i++){
		filledArray[i]=l.front();
		l.pop_front();
	}
}

void swap(Data** d1,Data** d2){
	Data* temp=*d1;
	*d1=*d2;
	*d2=temp;
}
