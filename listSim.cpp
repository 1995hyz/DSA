#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <errno.h>

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
		char* getName(){
			return listName;
		}
		void setName(char* name){
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
				std::cerr<<"Value popped: "<<temp->dataField<<std::endl;
				delete temp;
				theSize--;
			}
			else{	
				std::cerr<<"ERROR: This list is empty!"<<std::endl;
			}
		}	
	protected:
		int theSize;
		Node *head;
		Node *tail;
		char *listName;
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

char testName[16]="aQueue\0";
char* linepointer=NULL;
int readSize=0;
size_t len=0;
FILE* commandFile;

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
	std::cerr<<"Enter name of input file: ";
	while(!readSize){
		if((readSize=(int)getline(&linepointer,&len,stdin))<0){
			std::cerr<<"Reading Input Error: "<<strerror(errno)<<std::endl;
			return EXIT_FAILURE;
		}
	}
	linepointer[readSize-1]=0;		//Truncate the \n that getline() gets
	readSize=0;
	if((commandFile=fopen(linepointer,"r"))==NULL){
		std::cerr<<"Reading Input File Error: "<<strerror(errno)<<std::endl;
		return EXIT_FAILURE;
	}
	while((readSize=(int)getline(&linepointer,&len,commandFile))>0){
		std::cerr<<linepointer;
	}
	if((readSize<0)&&(errno!=0)){
		std::cerr<<"Read Command File Error: "<<strerror(errno)<<std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
