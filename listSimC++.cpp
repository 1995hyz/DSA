#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <errno.h>
#include <fstream>
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
				cerr<<"Value popped: "<<temp->dataField<<endl;
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
			simpleList<Object>::removeFromStart();
		}
};

std::string linepointer;

int main(int argc,char* argv[]){
	/*int a=1;
	int b=2;
	int c=3;
	stack<int> simStack=stack<int>();
	simStack.setName(testName);
	simStack.push(a);
	printf("Execute from %s\n ",simStack.getName());
	simStack.push(b);
	simStack.push(c);
	simStack.pop();
	simStack.pop();
	simStack.pop();
	simStack.pop();
	simStack.push(a);
	simStack.push(b);
	simStack.pop();
	simStack.pop();
	simStack.pop();*/

	cerr<<"Enter name of input file: ";
	getline(std::cin,linepointer);
	ifstream commandFile;
	const char *inputFile=linepointer.c_str();
	commandFile.open(inputFile,ios::in);
	while(getline(commandFile,linepointer)){
		cerr<<linepointer<<endl;
	}
	return EXIT_SUCCESS;
}
