#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <errno.h>
#include <fstream>
#include <string.h>

using namespace std;
template <typename Object>
class simpleList
{
	protected:
		class Node {
			public:	
				Node *nextNode;
				Object dataField;
			public:
				Node(Object data=Object(),Node *next=NULL)	//Copy value and set pointer
				:dataField(data),nextNode(next){}
		};
	public:
		simpleList(){
			theSize=0;
		}
		string getName(){
			return listName;
		}
		void setName(string name){
			listName=name;
		}	
	protected:
		void create(Object i){
			Node* firstNode=new Node(i,NULL);
			head=firstNode;
			tail=firstNode;
			firstNode=NULL;
		}
		void pushAtStart(Object i){
			Node *newHead=new Node(i,head);
			head=newHead;
			theSize++;
		}
		void pushAtEnd(Object i){
			Node *newTail=new Node(i,NULL);
			tail->nextNode=newTail;
			tail=newTail;
			theSize++;	
		}
		void removeFromStart(){
			if(theSize>0){
				Node *temp=head;
				head=head->nextNode;
				//cerr<<"Value popped: "<<temp->dataField<<endl;
				delete temp;
				theSize--;
			}
			else{	
				cerr<<"ERROR: This list is empty!"<<endl;
			}
		}	
	protected:
		int theSize;
		Node *head;
		Node *tail;
		string listName;
};

template <typename Object>
class stack: public simpleList<Object>
{
	public:
		stack(){
			simpleList<Object>::theSize=0;
		}
		void push(Object i){
			if(simpleList<Object>::theSize==0){
				simpleList<Object>::create(i);
				simpleList<Object>::theSize=1;
			}
			else{
				simpleList<Object>::pushAtStart(i);
			}
		}
		Object pop(){
			simpleList<Object>::removeFromStart();
		}
};

template <typename Object>
class queue: public simpleList<Object>
{
	public:
		queue(){
			simpleList<Object>::theSize=0;
		}
		void push(Object i){
			if(simpleList<Object>::theSize==0){
				simpleList<Object>::create(i);
				simpleList<Object>::theSize=1;
			}
			else{
				simpleList<Object>::pushAtEnd(i);
			}
		}
		Object pop(){
			Object returnValue=simpleList<Object>::head->dataField;
			simpleList<Object>::removeFromStart();
			return returnValue;
		}
};

std::string linepointer;

int main(int argc,char* argv[]){

	cerr<<"Enter name of input file: ";
	getline(std::cin,linepointer);
	ifstream commandFile;
	const char *inputFile=linepointer.c_str();
	char *token=NULL;
	commandFile.open(inputFile,ios::in);
	while(getline(commandFile,linepointer)){
		cerr<<linepointer<<endl;
		char* wholeCommand=strdup(linepointer.c_str());
		queue<string> lineCommand=queue<string>();
		token=strtok(wholeCommand," ");
		while(token!=NULL){
			lineCommand.push(string(token));
			//cerr<<token<<endl;
			token=strtok(NULL," ");
		}
		string popValue=lineCommand.pop();
		cerr<<popValue<<endl;
		if(popValue.compare("create")==0){
			cerr<<"Got It"<<endl;
		}
		free(wholeCommand);	
	}
	return EXIT_SUCCESS;
}
