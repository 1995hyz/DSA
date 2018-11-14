#include <iostream>
#include <string>
#include "dijkstra.h"

using namespace std;

int main(){
	int size = 3;
	graph testGraph = graph(size);
	if(testGraph.addEdge("v1", "v2", 2)==0){
		cout<<"Insertion Succeed."<<endl;
	}
	if(testGraph.addEdge("v1", "v4", 1)==0){
		cout<<"Insertion Succeed."<<endl;
	}
	if(testGraph.addEdge("v2", "v4", 3)==0){
		cout<<"Insertion Succeed."<<endl;
	}
	testGraph.addEdge("v2", "v5", 10);
	testGraph.addEdge("v3", "v1", 4);
	testGraph.addEdge("v3", "v6", 5);
	testGraph.addEdge("v4", "v3", 2);
	testGraph.addEdge("v4", "v5", 2);
	testGraph.addEdge("v4", "v6", 8);
	testGraph.addEdge("v4", "v7", 4);
	testGraph.addEdge("v5", "v7", 6);
	testGraph.addEdge("v7", "v6", 1);
	/*graph::iterator itr = testGraph.begin();
	for(; itr != testGraph.end(); itr++){
		cout<<(*itr).id<<endl;
		for(int i=(*itr).adjacentEdge.size(); i>0; i--){
			cout<<(*itr).adjacentEdge.front().destination<<endl;
			(*itr).adjacentEdge.pop_front();
		}
	}*/
	testGraph.searchPath("v5");
}
