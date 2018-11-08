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

int graph::insert(const string &id, const string &edge, int cost){
	if(checkExist(id)){
		return 2;
	}
	Vertex newVertex = Vertex(id);
	vertecies.push_back(newVertex);
	Edge newEdge = Edge(id, edge, cost);
	adjacentEdge.push_back(newEdge);
}
