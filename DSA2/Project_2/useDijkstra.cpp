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
}
