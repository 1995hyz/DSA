#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <list>
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
		int getTheSize(){
			return theSize;
		}
		void setTheSize(int size){
			theSize=size;
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
				cerr<<"Value popped: "<<temp->dataField;
				delete temp;
				theSize--;
				cerr<<" Size: "<<theSize<<endl;
			}
			else{	
				cerr<<"ERROR: This list is empty!"<<endl;
			}
		}
		virtual void push(Object i){
		}
		virtual Object pop(){
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
			Object returnValue;
			if(simpleList<Object>::theSize>0){
				returnValue=simpleList<Object>::head->dataField;
			}
			simpleList<Object>::removeFromStart();
			return returnValue;
		}
};

template <typename Object>
void checkAndPush(queue<string> *lastTwoCommand, list<simpleList<Object>* > *toEachList){
	string popValue2=lastTwoCommand->pop();
	string popValue3=lastTwoCommand->pop();
	typename list<simpleList<Object>* >::iterator it;
	for(it=toEachList->begin();it!=toEachList->end();it++){
		if(popValue2.compare(it->listName)==0){
			stringstream converting(popValue3);
			Object x;
			converting>>x;
			it->push(x);
		}
	}
}

template <typename Object>
void createNewList(string listName, string listType, list<simpleList<Object>* > *toEachList){
	if(listType.compare("stack")==0){
		simpleList<Object> *pSLType=new stack<Object>();
		pSLType->setName(listName);
		toEachList->push_front(pSLType);
	}
	else if(listType.compare("queue")==0){
		simpleList<Object> *pSLType=new queue<Object>();
		pSLType->setName(listName);
		toEachList->push_front(pSLType);
	}
}	

std::string linepointer;

int checkName(queue<string> *nameLi,string theName){
	int nameListSize=nameLi->getTheSize();
	string checkName;
	while(nameListSize>0){
		checkName=nameLi->pop();
		//cerr<<"Comparing Name: "<<checkName<<endl;
		if((theName.compare(checkName)==0)){
			nameLi->push(checkName);
			return 1;		
		}
		else{
			nameListSize=nameListSize-1;
			nameLi->push(checkName);
		}
	}
	return 0;				
}

int main(int argc,char* argv[]){
	cerr<<"Enter name of input file: ";
	getline(std::cin,linepointer);
	ifstream commandFile;
	const char *inputFile=linepointer.c_str();
	char *token=NULL;
	queue<string> nameList=queue<string>();		//Create a queue to hold the name of all current queue and stack
	list<simpleList<int> *> listSLi;
	list<simpleList<double> *> listSLd;
	list<simpleList<string> *> listSLs;
	commandFile.open(inputFile,ios::in);
	while(getline(commandFile,linepointer)){
		cerr<<linepointer<<endl;
		char* wholeCommand=strdup(linepointer.c_str());
		queue<string> lineCommand=queue<string>();
		token=strtok(wholeCommand," ");
		while(token!=NULL){
			lineCommand.push(string(token));
			token=strtok(NULL," ");
		}
		string popValue1=lineCommand.pop();
		if(popValue1.compare("create")==0){
			string popValue2=lineCommand.pop();
			if(checkName(&nameList,popValue2)==0){
				nameList.push(popValue2);
				string type=popValue2.substr(0,1);
				string popValue3=lineCommand.pop();
				if(type.compare("i")==0){
					createNewList(popValue2,popValue3,&listSLi);	
				}
			}
			else{
				cerr<<"ERROR: This name already exists!"<<endl;
			}	
		}
		if(popValue1.compare("push")==0){
			checkAndPush(&lineCommand,&listSLi);
		}
		if(popValue1.compare("pop")==0){
			string popValue2=lineCommand.pop();
			if(checkName(&nameList,popValue2)==1){
				
			}
		}
		free(wholeCommand);	
	}
	return EXIT_SUCCESS;
}
