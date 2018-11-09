#include <iostream>
#include <string>
#include <cstdlib>
#include "hash.h"
#include "dijkstra.h"

using namespace std;

graph::graph(int size){
	capacity = size;
	vertexTable = new hashTable(capacity);
}

int graph::checkExist(const string &id){
	if(vertexTable->contains(id)){
		return true;
	}
	else{
		return false;
	}
}

int graph::insert(const string &id){
	if(checkExist(id)){
		return 2;
	}
	Vertex newVertex = Vertex();
	vertecies.push_back(newVertex);
	Vertex* theVertex = &vertecies.back();
	theVertex->id = id;
	if(vertexTable->insert(id, theVertex) != 0){
		cerr<<"Error: Fail to insert vertex "<<id<<" to the hashTable."<<endl;
		return 1;
	}
	return 0;
}

int graph::addEdge(const string &id, const string &des, int cost){
	if(! checkExist(id)){
		if(insert(id)==1){
			return 1;
		}	
	}
	Vertex* currentVertex = static_cast<Vertex* >(vertexTable->getPointer(id));
	Edge newEdge = Edge();
	currentVertex->adjacentEdge.push_back(newEdge);
	Edge theEdge = currentVertex->adjacentEdge.back(); 
	theEdge.source = id;
	theEdge.destination = des;
	theEdge.cost = cost;
	return 0;
}
