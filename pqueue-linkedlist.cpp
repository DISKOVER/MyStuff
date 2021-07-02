/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

//initializes new empty head.
LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	logLen = 0; //helps us to track down the size.
}
//deletes list when its no longer used.
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while(head!=NULL){
		Node* next = head->next;
		delete head;
		head = next;
	}
}
int LinkedListPriorityQueue::size() {
	return logLen;
}

bool LinkedListPriorityQueue::isEmpty() {
	return head == NULL;
}
//adds new element to the list, in a way that it's always sorted( E.G first element is always lexicographically lowest)
void LinkedListPriorityQueue::enqueue(string value) {
	Node* node = new Node;
	node->name = value;
	if(head==NULL){
		node->next = NULL;
		head = node;
		logLen++;
		return;
	}
	if(size()==1){
		addSecondElement(head,node,value);
		return;
	}
	int lastChecker = 0; //if lastChecker > 0 after calculateIndex function, element needs to be inserted at the end.
	int firstChecker = 0; //if firstChecker = 0 after calculateIndex function, element needs to be inserted at the start.
	int index = 0; //after calculateIndex function, this int will gives us the index at which the element needs to be inserted.
	calculateIndex(head,value,index,firstChecker,lastChecker);
	addElementAccordingly(head,node,index,lastChecker,firstChecker);
	logLen++;
}
//returns first element.
string LinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("This list is empty");
	}
	return head->name;
}

//removes first element.
string LinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("This list is empty");
	}
	string str = head->name;
	Node* next = head->next;
	delete head;
	head = next;
	logLen--;
	return str;
	
}

//edge case, if list has only one element, adds the second one accordingly, either before, or after it.
void LinkedListPriorityQueue::addSecondElement(Node*& head, Node*& node, string value){
	if(value<head->name){
		node->next = head;
		head = node;
		logLen++;
	} else {
		node->next=NULL;
		head->next=node;
		logLen++;
	}
}

//calculates index at which the new element should be added.
void LinkedListPriorityQueue::calculateIndex(Node*& head, string value, int& index, int& firstChecker, int& lastChecker){
	Node* tmp = head;
	while(true){
		if(value > tmp->name){
			firstChecker++; 
			tmp = tmp ->next;
			index++;
			if(tmp==NULL){
				lastChecker++; 
				break;
			}
		} else {
			break;
		}
	}
}

//edge case, if element needs to be inserted at the first index, this function is used.
void LinkedListPriorityQueue::insertAtFirst(Node*& head, Node*& node){
	node->next = head;
	head = node;
}
//edge case, if element needs to be inserted at the last index, this function is used.
void LinkedListPriorityQueue::insertAtLast(Node*& head, Node*& node){
	Node* current = head;
	while(current->next!=NULL){
		current = current->next;
	}
	node->next=NULL;
	current->next=node;
}

//if element needs to be inserted at the middle(E.G neither first or last index) this function is used.
void LinkedListPriorityQueue::insertAtMiddle(Node*& head, Node*& node, int& index){
	Node* current = head;
	for(int i = 0; i <index-1; i++){
		current = current->next;
	}
	node->next = current->next;
	current->next = node;
}

//calls insert functions accordingly.
void LinkedListPriorityQueue::addElementAccordingly(Node*& head, Node*& node, int& index, int& lastChecker, int& firstChecker){
	if(lastChecker>0){
      insertAtLast(head,node);
	} else if(firstChecker==0){
		insertAtFirst(head,node);
	} else insertAtMiddle(head,node,index);
}




