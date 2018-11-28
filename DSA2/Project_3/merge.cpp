#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int matrix[1001][1001];

string findPath(const string & rowString, const string & columnString, const string & mergeString, int rowNum, int columnNum){
	int mergeLength = mergeString.length();
	int rowLength = rowString.length();
	int columnLength = columnString.length();
	string resultString = "";
	for(int i = 0; i<mergeLength; i++){
		if((columnNum+1 <= rowLength) && (rowNum+1 <= columnLength) && (matrix[rowNum+1][columnNum] == 0) && (matrix[rowNum][columnNum+1] == 0) && (rowString[rowNum] == mergeString[i]) && (columnString[columnNum] == mergeString[i])){
			matrix[rowNum][columnNum+1] = 1;
			string newMerge = mergeString.substr(i+1, mergeLength-i-1);
			string partialResult = findPath(rowString, columnString, newMerge, rowNum, columnNum+1);
			if(! partialResult.empty()){
				return resultString + char(mergeString[i] - 32) + partialResult;
			}
			else{
				matrix[rowNum+1][columnNum] = 2;
				partialResult = findPath(rowString, columnString, newMerge, rowNum+1, columnNum);
				if(! partialResult.empty()){
					return resultString + mergeString[i] + partialResult;
				}
				else{
					return "";
				}
			}
		}
		else if((columnNum+1 <= rowLength) && (matrix[rowNum][columnNum+1] == 0) && (rowString[columnNum] == mergeString[i])){
			columnNum++;
			resultString = resultString + char(mergeString[i] - 32);
			matrix[rowNum][columnNum] = 1;
		}
		else if((rowNum+1 <= columnLength) && (matrix[rowNum+1][columnNum] == 0) && (columnString[rowNum] == mergeString[i])){
			rowNum++;
			resultString = resultString + mergeString[i];
			matrix[rowNum][columnNum] = 2;
		}
		else{
			return "";
		}
	}
	return resultString;
}

void printMatrix(int rowNum, int columnNum){
	for(int i=0; i<rowNum; i++){
		for(int j=0; j<columnNum; j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

void clearMatrix(int rowNum, int columnNum){
	for(int i=0; i<rowNum; i++){
		for(int j=0; j<columnNum; j++){
			matrix[i][j] = 0;
		}
	}
}

int main(){
	/*string A = "abc";
	string B = "ebg";
	string C = "aebbcg";*/
	string inputFile;
	string outputFile;
	cout<<"Enter name of input file: ";
	cin>>inputFile;
	ifstream input(inputFile.c_str());
	if(! input){
		cerr<<"Error: Couldn't open input file, "<<inputFile<<endl;
		return 1;
	}
	cout<<"Enter name of output file: ";
	cin>>outputFile;
	ofstream output(outputFile.c_str());
	if(! output){
		cerr<<"Error: Couldn't open output file, "<<outputFile<<endl;
		return 1;
	}
	//matrix[0][0] = 3;
	string A;
	string B;
	string C;
	while(getline(input, A)){
		getline(input, B);
		getline(input, C);
		string path = findPath(A, B, C, 0, 0);
		//printMatrix(4, 4);
		cout<<path<<endl;
		clearMatrix(A.length()+1, B.length()+1);
	}
	return 0;
}
