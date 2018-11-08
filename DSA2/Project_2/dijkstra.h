#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <string>
#include <list>
#include <iostream>
#include "heap.h"

class dijkstraHeap {
	
	public:

	//dijkstraHeap - The constructor allocates space for the nodes of the heap.
	dijkstraHeap(int capacity);
	
	//insert - Insert a node into the dijkstra heap.
	// 0 on success
	// 1 if heap has already be filled to its capacity.
	// 2 if the node has already exists but the heap hasn't reached to its capacity.
	int insert(const std::string &id, int key, void* pv);

	//searchPath - Search the shortest cost to every vertex, given the provided start vertex.
	void searchPath(const std::string id); 
	
	private:
	
	heap* diHeap;
	int capacity;
}

class graph {
	public:
	
	//graph - The constructor.
	graph();
	
	//insert - Insert a vertex into the graph.
	//0 on success
	//2 if the vertex has already exists in the graph.
	int insert(const std::string &id, const std::string &edge, int cost);
	
	//addEdge - Add an edge into an existing vertex.
	//0 on success
	//1 if the vertex doesn't exist.
	//2 if the same edge has existed.
	int addEdge(const std::string &id, const std::string &edge, int cost);

	private:
	
	class edge {
		public:
		std::string source;
		std::string destination;
		int cost;
	}
	
	class vertex{
		public:
		std::string id;
		std::list<edge> adjacentEdge;
	}

	std::list<vertex> vertecies;
	hashtable* vertexTable;
	
	//checkExist - Check if a vertex has already existed.
	//0 on not existed.
	//1 on has existed.
	int checkExist(const std::string &id);
}
