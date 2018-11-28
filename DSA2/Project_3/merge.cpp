#include <iostream>
#include <string>

using namespace std;

int matrix[1001][1001];

int findPath(const string & rowString, const string & columnString, const string & mergeString, int rowNum, int columnNum){
	int mergeLength = mergeString.length();
	for(int i = 0; i<mergeLength; i++){
		if((matrix[rowNum+1][columnNum] == 0) && (matrix[rowNum][columnNum+1] == 0) && (rowString[rowNum+1] == mergeString[i]) && (columnString[columnNum+1] == mergeString[i])){
			matrix[rowNum][columnNum+1] = 2;
			string newRow = rowString.substr(columnNum+2, rowString.length()-columnNum-2);
			string newColumn = columnString.substr(rowNum, columnString.length()-rowNum);
			int result = findPath(newRow, newColumn, rowNum, columnNum+2);
			if(! result){
				break;
			}
			else{
				matrix[rowNum+1][columnNum] = 1;
				newRow = rowString.substr(columnNum, rowString.length()-columnNum);
				newColumn = columnString.substr(rowNum+2, columnString.length-rowNum-2);
				result = findPath(newRow, newColumn, rowNum+2, columnNum);
				if(! result){
					break;
				}
				else{
					return 1
				}
			}
		}
		else if((matrix[rowNum+1][columnNum] == 0) && (rowString[rowNum+1] == mergeString[i])){
			rowNum++;
			matrix[rowNum][columnNum] = 1;
		}
		else if((matrix[rowNum][columnNum+1] == 0) && (columnString[columnNum+1] == mergeString[i])){
			columnNum++;
			matrix[rowNum][columnNum] = 2;
		}
		else{
			return 1;
		}
	}
	return 0;
}

int main(){
	string A = "abc";
	string B = "efg";
	matrix[0][0] = 0;
	return 0;
}
