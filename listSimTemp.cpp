#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <errno.h>
#include <fstream>
#include <string.h>

using namespace std;
template <typename T>
class simpleList
{
	protected:
		class Node {
			public:	
				Node *nextNode;
				T dataField;
				simpleList *corList;
			public:
				Node(T data=T(),Node *next=NULL,simpleList *corRef=NULL)	//Copy value and set pointer
				:dataField(data),nextNode(next),corList(corRef){}
			public: void setRef(simpleList* corRef){
				corList=corRef;
				}
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
		void create(T i,simpleList* corRef){
			Node* firstNode=new Node(i,NULL,corRef);
			head=firstNode;
			tail=firstNode;
			firstNode=NULL;
		}
		void pushAtStart(T i){
			Node *newHead=new Node(i,head,NULL);
			head=newHead;
			theSize++;
		}
		void pushAtEnd(T i,simpleList* corRef){
			Node *newTail=new Node(i,NULL,corRef);
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

template <typename T>
class stack: public simpleList<T>
{
	public:
		stack(){
			simpleList<T>::theSize=0;
		}
		void push(T i){
			if(simpleList<T>::theSize==0){
				simpleList<T>::create(i,NULL);
				simpleList<T>::theSize=1;
			}
			else{
				simpleList<T>::pushAtStart(i);
			}
		}
		T pop(){
			simpleList<T>::removeFromStart();
		}
};

template <typename T>
class queue: public simpleList<T>
{
	public:
		queue(){
			simpleList<T>::theSize=0;
		}
		void push(T i){
			if(simpleList<T>::theSize==0){
				simpleList<T>::create(i,NULL);
				simpleList<T>::theSize=1;
			}
			else{
				simpleList<T>::pushAtEnd(i,NULL);
			}
		}
		T pop(){
			T returnValue=simpleList<T>::head->dataField;
			simpleList<T>::removeFromStart();
			return returnValue;
		}
};

/*class nameList: public simpleList<string>
{
	public:
		 nameList(){
			simpleList<string>::theSize=0;
		}
}*/

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
			stack<int>* testStack=new stack<int>();
			testStack->setName("testName");
			cerr<<testStack->getName()<<endl;
		}
		free(wholeCommand);	
	}
	return EXIT_SUCCESS;
}
