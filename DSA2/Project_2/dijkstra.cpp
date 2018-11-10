#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include "hash.h"
#include "dijkstra.h"

using namespace std;

graph::graph(int size){
	capacity = 0;
	vertexTable = new hashTable(size);
}

int graph::checkExist(const string &id){
	if(vertexTable->contains(id)){
		return true;
	}
	else{
		return false;
	}
}

int graph::insertVertices(const string &id){
	if(checkExist(id)){
		return 2;
	}
	Vertex newVertex = Vertex();
	vertices.push_back(newVertex);
	Vertex* theVertex = &vertices.back();
	theVertex->id = id;
	capacity++;
	if(vertexTable->insert(id, theVertex) != 0){
		cerr<<"Error: Fail to insert vertex "<<id<<" to the hashTable."<<endl;
		return 1;
	}
	return 0;
}

int graph::addEdge(const string &id, const string &des, int cost){
	if(! checkExist(id)){
		if(insertVertices(id)==1){
			return 1;
		}	
	}
	Vertex* currentVertex = static_cast<Vertex* >(vertexTable->getPointer(id));
	Edge newEdge = Edge();
	currentVertex->adjacentEdge.push_back(newEdge);
	Edge* theEdge = &(currentVertex->adjacentEdge.back()); 
	theEdge->source = id;
	theEdge->destination = des;
	theEdge->cost = cost;
	return 0;
}

int graph::insertHeap(const string &id, void* pv){
	int max = std::numeric_limits<int>::max();
	return diHeap->insert(id, max, pv);
}

void graph::buildHeap(){
	diHeap = new heap(capacity);
	list<Vertex>::iterator ptr;
	ptr = vertices.begin();
	while(ptr != vertices.end()){
		if(insertHeap((*ptr).id, &(*ptr)) != 0){
			cerr<<"Error: Building heap error."<<endl;
		}
		ptr++;
	}
}

void graph::searchPath(const string &id){
	buildHeap();
	int keyValue = 0;
	int counter = capacity;
	diHeap->setKey(id, keyValue);
	while(counter > 0){
		int pCost;
		string pId;
		void* pNode;
		diHeap->deleteMin(&pId, &pCost, pNode);
		cout<<"Delete: "<<pId<<endl;
		counter--;
		Vertex* pVertex = static_cast<Vertex*> (pNode);
		while(! pVertex->adjacentEdge.empty()){
			if((keyValue + pVertex->adjacentEdge.front().cost) < pCost){
				diHeap->setKey(pVertex->adjacentEdge.front().destination, pVertex->adjacentEdge.front().cost + keyValue);
			}
			cout<<pVertex->adjacentEdge.front().destination<<endl;
			(pVertex->adjacentEdge).pop_front();
		}
	}
}
