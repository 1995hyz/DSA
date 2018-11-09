#include <iostream>
#include <string>
#include <cstdlib>
#include "hash.h"
#include "dijkstra.h"

using namespace std;

int graph::graph(int size){
	capacity = size;
	vertexTable = new hashTable(capacity);
	
}

int graph::insert(const string &id){
	if(checkExist(id)){
		return 2;
	}
	Vertex newVertex = Vertex(id);
	vertecies.push_back(newVertex);
	vertexTable.insert(id, &newVertex);
	return 0;
}

int graph::addEdge(const string &id, const string &source, int cost){
	if(! checkExist(id)){
		insert(id);	
	}
	currentVertex = static_cast<Vertex*> (getPointer(id));
	
}
