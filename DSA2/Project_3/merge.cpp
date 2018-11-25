#include <iostream>
#include <string>

using namespace std;

int main(){
	string A = "QNZ";
	string B = "BZZI";
	string C = "QZNBZZI";

	string rest = "";
	int last_pos = -1;
	int m = 0;
	for(int i=0; i<A.length(); i++){
		for(int j=m; j<C.length(); j++){
			if (C[j] == A[i]){
				cout<<C[j]<<" == "<<A[i]<<endl;
				rest = rest + C.substr(last_pos+1, j-(last_pos+1));
				m = j + 1;
				last_pos = j;
				break;
			}
		}
	}
	rest = rest + C.substr(last_pos+1, C.length()-last_pos-1);
	cout<<"B: "<<B<<endl;
	cout<<"Rest: "<<rest<<endl;
	return 0;
}
