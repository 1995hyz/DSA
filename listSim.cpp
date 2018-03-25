//Author:Yingzhi Hao --ECE264 Project1
//This program acts as a simple stack and queue simultor. It takes an input file containing stack and queue operations.
//Then it executes each command-line and outputs the result to the specified output file.
//To run this program, simply just using g++ to compile and run the executable file without any arguments.
//For example, 
//g++ listSim.cpp -o listSim
//./listSim
//The user will need to input the input command-file and the output result-file. Input a non-existing file will lead to 
//immediate termination of the program.


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <list>
#include <errno.h>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

//class simpleList is the base class of a singly-linked list. It contains a special "theSize" data member
//to indicate whether is empty or not.

template <typename Object>
class simpleList
{
	private:
		class Node {
			public:	
				Node *nextNode;
				Object dataField;
			public:
				Node(Object data=Object(),Node *next=NULL)	
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
		virtual void push(Object i){
			cout<<"Not Supposed to Run!"<<endl;
		}
		virtual Object pop(){
			cout<<"Not Supposed to Run!"<<endl;
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
				delete temp;
				theSize--;
			}
		}
		Object getHeadData(){
			return head->dataField;
		}
	private:
		int theSize;
		Node *head;
		Node *tail;
		string listName;
};

//class stack can create singly-linked LIFO lists

template <typename Object>
class stack: public simpleList<Object>
{
	public:
		stack(){
			simpleList<Object>::setTheSize(0);
		}
		void push(Object i){
			if(simpleList<Object>::getTheSize()==0){
				simpleList<Object>::create(i);
				simpleList<Object>::setTheSize(1);
			}
			else{
				simpleList<Object>::pushAtStart(i);
			}
		}
		Object pop(){
			Object returnValue;
			if(simpleList<Object>::getTheSize()>0){
				returnValue=simpleList<Object>::getHeadData();
			}
			simpleList<Object>::removeFromStart();
			return returnValue;
		}
};

//class queue can create singly-linked FIFO lists

template <typename Object>
class queue: public simpleList<Object>
{
	public:
		queue(){
			simpleList<Object>::setTheSize(0);
		}
		void push(Object i){
			if(simpleList<Object>::getTheSize()==0){
				simpleList<Object>::create(i);
				simpleList<Object>::setTheSize(1);
			}
			else{
				simpleList<Object>::pushAtEnd(i);
			}
		}
		Object pop(){
			Object returnValue;
			if(simpleList<Object>::getTheSize()>0){
				returnValue=simpleList<Object>::getHeadData();
			}
			simpleList<Object>::removeFromStart();
			return returnValue;
		}
};

//function checkAndPush takes a string and does a linear search through a name list to find the correct pointer to 
//the list that has that string as its name. Once it finds the correct pointer, a value passed to the function is
//pushed onto the list.

template <typename Object>
void checkAndPush(string listName, string listValue, list<simpleList<Object>* > *toEachList){
	typename list<simpleList<Object>* >::iterator it;
	for(it=toEachList->begin();it!=toEachList->end();it++){
		if(listName.compare((*it)->getName())==0){
			stringstream converting(listValue);
			Object x;
			converting>>x;
			(*it)->push(x);
		}
	}
}

//function checkAndPop basicly does the same thing as checkAndPush, except that it pop and return a value from the 
//corresponding list rather than pushing.

template <typename Object>
void checkAndPop(string listName, list<simpleList<Object>* > *toEachList){
	typename list<simpleList<Object>* >::iterator it;
	for(it=toEachList->begin();it!=toEachList->end();it++){
		if(listName.compare((*it)->getName())==0){
			if((*it)->getTheSize()>0){
				Object popReturn;
				popReturn=(*it)->pop();
				cout<<"Value popped: "<<popReturn<<endl;
			}
			else{
				cout<<"ERROR: This list is empty!"<<endl;
			}
		}
	}
}

//function createNewList creates a new stack or queue and push its pointer to the corresponding lists that are used by
//function checkAndPush and checkAndPop

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
std::string outFile;

//function checkName takes a name list and a string. It searches through the list to check if the string
//exists in the list or not. It returns 0 if the string is in the list, and returns 1 if not. The name
//list is a queue that creates by the class queue. This function does a pop() to perform checking, and then
//does a push() to push the value back to the queue.

int checkName(queue<string> *nameLi,string theName){
	int nameListSize=nameLi->getTheSize();
	string checkName;
	while(nameListSize>0){
		checkName=nameLi->pop();
		if((theName.compare(checkName)==0)){
			nameLi->push(checkName);
			return 0;		
		}
		else{
			nameListSize=nameListSize-1;
			nameLi->push(checkName);
		}
	}
	return 1;				
}

int main(int argc,char* argv[]){
	cerr<<"Enter name of input file: ";
	getline(std::cin,linepointer);
	ifstream commandFile;
	const char *inputFile=linepointer.c_str();
	commandFile.open(inputFile,ios::in);
	cerr<<"Enter name of output file: ";
	getline(std::cin,outFile);
	ofstream outputResult(outFile.c_str());
	streambuf *coutbuf=cout.rdbuf();		//Save the old cout stream
	cout.rdbuf(outputResult.rdbuf());
	char *token=NULL;
	queue<string> nameList=queue<string>();		//Create a queue to hold the name of all current queue and stack
	list<simpleList<int> *> listSLi;
	list<simpleList<double> *> listSLd;
	list<simpleList<string> *> listSLs;
	while(getline(commandFile,linepointer)){
		cout<<"PROCESSING COMMAND: "<<linepointer<<endl;
		char* wholeCommand=strdup(linepointer.c_str());
		queue<string> lineCommand=queue<string>();
		token=strtok(wholeCommand," ");
		while(token!=NULL){			//Parse on comand line into two or three tokens and store them in a queue
			lineCommand.push(string(token));
			token=strtok(NULL," ");
		}
		string popValue1=lineCommand.pop();
		string popValue2=lineCommand.pop();
		string type=popValue2.substr(0,1);
		if(popValue1.compare("create")==0){
			if(checkName(&nameList,popValue2)==1){
				nameList.push(popValue2);
				string popValue3=lineCommand.pop();
				if(type.compare("i")==0){
					createNewList(popValue2,popValue3,&listSLi);	
				}
				else if(type.compare("d")==0){
					createNewList(popValue2,popValue3,&listSLd);
				}
				else if(type.compare("s")==0){
					createNewList(popValue2,popValue3,&listSLs);
				}
				else{
					cout<<"ERROR: Invalid type"<<endl;
				}
			}
			else{
				cout<<"ERROR: This name already exists!"<<endl;
			}	
		}
		if(popValue1.compare("push")==0){
			if(checkName(&nameList,popValue2)==0){
				string popValue3=lineCommand.pop();
				if(type.compare("i")==0){
					checkAndPush(popValue2,popValue3,&listSLi);
				}
				else if(type.compare("d")==0){
					checkAndPush(popValue2,popValue3,&listSLd);
				}
				else if(type.compare("s")==0){
					checkAndPush(popValue2,popValue3,&listSLs);
				}
			}
			else{
				cout<<"ERROR: This name does not exist!"<<endl;
			}
		}
		if(popValue1.compare("pop")==0){
			if(checkName(&nameList,popValue2)==0){
				if(type.compare("i")==0){
					checkAndPop(popValue2,&listSLi);
				}
				else if(type.compare("d")==0){
					checkAndPop(popValue2,&listSLd);
				}
				else if(type.compare("s")==0){
					checkAndPop(popValue2,&listSLs);
				}
			}
			else{
				cout<<"ERROR: This name does not exist!"<<endl;
			}
		}
		free(wholeCommand);	
	}
	cout.rdbuf(coutbuf);		//Restore to the old cout stream
	return EXIT_SUCCESS;
}
