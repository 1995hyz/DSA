#include <iostream>
#include <string>

using namespace std;

int matrix[1001][1001];

int findPath(const string & rowString, const string & columnString, const string & mergeString, int rowNum, int columnNum){
	int mergeLength = mergeString.length();
	int rowLength = rowString.length();
	int columnLength = columnString.length();
	for(int i = 0; i<mergeLength; i++){
		if((columnNum+1 <= rowLength) && (rowNum+1 <= columnLength) && (matrix[rowNum+1][columnNum] == 0) && (matrix[rowNum][columnNum+1] == 0) && (rowString[rowNum] == mergeString[i]) && (columnString[columnNum] == mergeString[i])){
			matrix[rowNum][columnNum+1] = 1;
			string newMerge = mergeString.substr(i+1, mergeLength-i-1);
			int result = findPath(rowString, columnString, newMerge, rowNum, columnNum+1);
			if(! result){
				return 0;
			}
			else{
				matrix[rowNum+1][columnNum] = 2;
				result = findPath(rowString, columnString, newMerge, rowNum+1, columnNum);
				if(! result){
					return 0;
				}
				else{
					return 1;
				}
			}
		}
		else if((columnNum+1 <= rowLength) && (matrix[rowNum][columnNum+1] == 0) && (rowString[columnNum] == mergeString[i])){
			columnNum++;
			matrix[rowNum][columnNum] = 1;
		}
		else if((rowNum+1 <= columnLength) && (matrix[rowNum+1][columnNum] == 0) && (columnString[rowNum] == mergeString[i])){
			rowNum++;
			matrix[rowNum][columnNum] = 2;
		}
		else{
			return 1;
		}
	}
	return 0;
}

void printMatrix(int rowNum, int columnNum){
	for(int i=0; i<rowNum; i++){
		for(int j=0; j<columnNum; j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main(){
	string A = "abc";
	string B = "gbe";
	string C = "agbebc";
	matrix[0][0] = 3;
	findPath(A, B, C, 0, 0);
	printMatrix(4, 4);
	return 0;
}
