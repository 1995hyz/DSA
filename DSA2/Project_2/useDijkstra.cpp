#include <iostream>
#include <string>
#include "dijkstra.h"

using namespace std;

int main(){
	int size = 10;
	graph testGraph = graph(size);
	if(testGraph.addEdge("v1", "v2", 1)==0){
		cout<<"Insertion Succeed."<<endl;
	}
	if(testGraph.addEdge("v1", "v3", 2)==0){
		cout<<"Insertion Succeed."<<endl;
	}
	if(testGraph.addEdge("v2", "v3", 5)==0){
		cout<<"Insertion Succeed."<<endl;
	}
	/*graph::iterator itr = testGraph.begin();
	for(; itr != testGraph.end(); itr++){
		cout<<(*itr).id<<endl;
		for(int i=(*itr).adjacentEdge.size(); i>0; i--){
			cout<<(*itr).adjacentEdge.front().destination<<endl;
			(*itr).adjacentEdge.pop_front();
		}
	}*/
	testGraph.searchPath("v1");
}
