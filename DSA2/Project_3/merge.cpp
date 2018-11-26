#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
	string A, B, C;
	A = "bcd";
	B = "ace";
	C = "bcadce";
	string subA, subB, subC;
	subA = A;
	subB = B;
	subC = C;
	int charLength = 1;
	string result = "";
	while(subC.length()){
		string CComp = subC.substr(0, charLength);
		string AComp = subA.substr(0, charLength);
		string BComp = subB.substr(0, charLength);
		if((CComp == AComp) && (CComp == BComp)){
			charLength++;
			continue;
		}
		if(CComp == AComp){
			string upperCase = CComp;
			transform(upperCase.begin(), upperCase.end(), upperCase.begin(), ::toupper);
			result = result.append(upperCase);
			subA = subA.substr(charLength, subA.length()-charLength);
		}
		else if(CComp == BComp){
			result += CComp;
			subB = subB.substr(charLength, subB.length()-charLength);
		}
		else{
			cout<<"Not a Merge."<<endl;
			break;
		}
		subC = subC.substr(charLength, subC.length()-charLength);
	}	
	cout<<result<<endl;
	return 0;
}
