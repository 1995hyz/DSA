#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <string>
#include <list>
#include <iostream>
#include "heap.h"
#include "hash.h"

class graph {

	private:
	
	class Edge {
		public:
		std::string source;
		std::string destination;
		int cost;
	};
	
	class Vertex{
		public:
		int cost;
		std::string id;
		Vertex* path;
		std::list<Edge> adjacentEdge;
	};
	
	int capacity;
	std::list<Vertex> vertices;
	hashTable* vertexTable;
	heap* diHeap;
	
	//checkExist - Check if a vertex has already existed.
	//0 on not existed.
	//1 on has existed.
	int checkExist(const std::string &id);

	//insertVerticies - Insert a vertex into the graph.
 	//0 on success
	//1 on hashTable insertion error.
 	//2 if the vertex has already exists in the graph.
 	int insertVertices(const std::string &id);

	//insertHeap - Insert a node into the dijkstra heap.
	// 0 on success.
	// 1 if heap has already be filled to its capacity.                              	
	// 2 if the node has already exists but the heap hasn't reached to its capacity.
	int insertHeap(const std::string &id, void* pv);
	
	//buildHeap - Build a binary heap to operate Dijkstra algorithm.
	void buildHeap();

	//printResult - Print the Result of Dijkstra algorithm.
	void printResult();

	//returnPath - Return a string that is the path of the two vertices.
	std::string returnPath(Vertex* v, std::string vertexPath);
	
	public:

	//graph - The constructor.
	graph(int capacity);

	//addEdge - Add an edge into an existing vertex.
	//0 on success.
	//1 on fail.
	int addEdge(const std::string &id, const std::string &edge, int cost);

	//searchPath - Search the shortest cost to every vertex, given the provided start vertex.
	void searchPath(const std::string &id); 

	//Define iterator.
	typedef std::list<Vertex>::iterator iterator;
	typedef std::list<Vertex>::const_iterator const_iterator;
	iterator begin(){return vertices.begin();}
	iterator end(){return vertices.end();}

};

#endif
