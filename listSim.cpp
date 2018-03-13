#include <iostream>
#include <string>
#include <cstdio>

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
int main(){
	int a=1;
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
	simStack.pop();
	return 1;
}
