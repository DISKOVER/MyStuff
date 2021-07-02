/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include "strlib.h"

//initializes an empty head.
DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	logLen = 0; //helps us to track down the size.
}
//deletes linked list when it's no longer used.
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Node* ptr = head;
	while (ptr != NULL) {
	Node* tmp = ptr;
	ptr = ptr -> next;
	delete tmp;
	}
}
int DoublyLinkedListPriorityQueue::size() {
	return logLen;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return head==NULL;
}
//ads new element at the top of the list.
void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* newNode = new Node;
	newNode -> name = value;
	if(head==NULL){
		head = newNode;
		newNode->prev=NULL;
		newNode->next=NULL;
	} else {
		head->prev=newNode;
		newNode->prev=NULL;
		newNode->next=head;
		head = newNode;
	}
	logLen++;
}

//returns lexicographically lowest element from list.
string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("This list is empty");
	}
	Node* tmp = head;
	string curName = tmp->name;
	while(tmp!=NULL){
		if(tmp->name<curName){
			curName = tmp->name;
		}
		tmp = tmp->next;
	}
	return curName;
}

//removes lexicographically lowest element from list.
string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("This list is empty");
	}
	Node* tmp = head;
	Node* toDelete = head;
	string curName = tmp->name;
	string str;
	while(tmp!=NULL){
		if(tmp->name<curName){
			curName = tmp->name;
			toDelete = tmp;
		}
		tmp = tmp->next;
	}
	removeAccordingly(head,toDelete,str);
	return str;
}

//edge case, if the size of a list is 1, removes the only element.
void DoublyLinkedListPriorityQueue::removeOnlyElement(Node*& head,string& str){
	Node* smth = head;
	str = smth->name;
	head = NULL;
	delete smth;
	logLen--;
}

//edge case, removes element at the start of the head.
void DoublyLinkedListPriorityQueue::removeAtFirst(Node*& head,Node*& toDelete,string& str){
	toDelete->next->prev=NULL;
	head = toDelete->next;
	str = toDelete->name;
	logLen--;
	delete toDelete;
}

//edge case, removes element if its at the end of the list.
void DoublyLinkedListPriorityQueue::removeAtLast(Node*& head,Node*& toDelete,string& str){
	toDelete->prev->next=NULL;
	str = toDelete ->name;
	logLen--;
	delete toDelete ;
}

// removes element if its neither last, or first.
void DoublyLinkedListPriorityQueue::removeAtMiddle(Node*& head,Node*& toDelete,string& str){
	Node* tmp = toDelete;
	toDelete->prev->next=toDelete->next;
	toDelete->next->prev=toDelete->prev;
	str = tmp->name;
	logLen--;
	delete tmp;
}

//calls removal functions accordingly.
void DoublyLinkedListPriorityQueue::removeAccordingly(Node*& head,Node*& toDelete,string& str){
	if(size()==1){
		removeOnlyElement(head,str);
	} else if (toDelete->prev==NULL){
		removeAtFirst(head,toDelete,str);
	} else if(toDelete->next==NULL){
		removeAtLast(head, toDelete,str);
	} else removeAtMiddle(head,toDelete,str);
}




