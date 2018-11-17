#include <iostream>
#include <fstream>
#include <string>
#include "dijkstra.h"
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

//How come we never have a split function in std...
vector<string> split(string &line, const string &delimiter){
	int n = line.length();
	char lineChar[n+1];
	vector<string> arguments;
	strcpy(lineChar, line.c_str());
	string source = strtok(lineChar, " ");
	string des = strtok(NULL, " ");
	string cost = strtok(NULL, " ");
	arguments.push_back(source);
	arguments.push_back(des);
	arguments.push_back(cost);
	return arguments;
}

int generateGraph(string &filename, graph* myGraph){
	ifstream input(filename.c_str());
	if(!input){
		cerr<<"Error: Cannot Open file "<<filename<<endl;
		return 1;
	}
	string singleLine;
	while(getline(input, singleLine)){
		vector<string> arguments = split(singleLine, " ");
		const string cost = arguments[2];
		myGraph->addEdge(arguments[0], arguments[1], atoi(arguments[2].c_str()));
	}
	return 0;
}

int main(){
	int size = 10;
	string inputFile;
	cout<<"Enter name of graph file: ";
	cin>>inputFile;
	graph *dijkstraGraph = new graph(size);
	generateGraph(inputFile, dijkstraGraph);
	string id;
	cout<<"Enter a valid vertex id for the starting vertex: ";
	cin>>id;
	clock_t t1 = clock();
	dijkstraGraph->searchPath(id);
	clock_t t2 = clock();
	double timeDiff = ((double)(t2 - t1) / CLOCKS_PER_SEC);
	cout<<"Total time (in seconds) to apply Dijkstra's algorithm: "<<timeDiff<<endl;
	string outputFile;
	cout<<"Enter name of output file: ";
	cin>>outputFile;
	ofstream output(outputFile.c_str());
	if(!output){
		cerr<<"Error: Cannot open file "<<outputFile<<endl;
		exit(1);
	}
	streambuf* oldCout = cout.rdbuf();
	streambuf* newCout = output.rdbuf();
	cout.rdbuf(newCout);
	dijkstraGraph -> printResult();
	cout.rdbuf(oldCout);
	output.close();
}
