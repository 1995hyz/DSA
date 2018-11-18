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
	if(! checkExist(des)){
		if(insertVertices(des)==1){
			return 1;
		}
	}
	return 0;
}

int graph::insertHeap(const string &id, void* pv){
	int max = std::numeric_limits<int>::max();
	return diHeap->insert(id, max, pv);
}

void graph::buildHeap(){
	diHeap = new heap(capacity);
	int max = numeric_limits<int>::max();
	list<Vertex>::iterator ptr;
	ptr = vertices.begin();
	while(ptr != vertices.end()){
		if(insertHeap((*ptr).id, &(*ptr)) != 0){
			cerr<<"Error: Building heap error."<<endl;
		}
		(*ptr).cost = max;
		ptr++;
	}
}

string graph::returnPath(Vertex* v, string vertexPath){
	if(v->path != NULL && v->path != v){
		vertexPath = returnPath(v->path, vertexPath) +", " + v->id;
	}
	else{
		vertexPath = v->id;
	}
	return vertexPath;
}

void graph::printResult(){
	int max = numeric_limits<int>::max();
	list<Vertex>::iterator ptr;
	ptr = vertices.begin();
	while(ptr != vertices.end()){
		if((*ptr).cost == max){
			cout<<(*ptr).id<<": NO PATH"<<endl;
		}
		else{
			cout<<(*ptr).id<<": "<<(*ptr).cost<<" "<<"[" + returnPath(&(*ptr),"") + "]"<<endl;
		}
		ptr++;
	}	
}

int graph::searchPath(const string &id){
	buildHeap();
	if (diHeap->setKey(id, 0)){
		return 1;
	}
	Vertex* startVertex = static_cast<Vertex*> (vertexTable->getPointer(id));
	startVertex->cost = 0;
	startVertex->path = startVertex;
	int counter = capacity;
	while(counter > 0){
		int pCost;
		string pId;
		Vertex* pVertex;
		diHeap->deleteMin(&pId, &pCost, &pVertex);
		counter--;
		if (pCost == numeric_limits<int>::max()){
			break;
		}
		while(! pVertex->adjacentEdge.empty()){
			string destination = pVertex->adjacentEdge.front().destination;
			int cost = pVertex->adjacentEdge.front().cost;
			Vertex* desVertex = static_cast<Vertex*> (vertexTable->getPointer(destination));
			if((pCost + cost) < desVertex->cost){
				diHeap->setKey(destination, cost + pCost);
				desVertex->cost = cost + pCost;
				desVertex->path = pVertex;
			}
			pVertex->adjacentEdge.pop_front();
		}
	}
	return 0;
}
