/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	if(size()==0){
		return true;
	} else {
		return false;
	}
}

void VectorPriorityQueue::enqueue(string value) {
	vec.add(value);
}

//iterates over an array, finds element with lowest value, then returns it.
string VectorPriorityQueue::peek() {
	if(size()>0){
		int index = 0;
		string tmpStr = vec[0];
		for(int i = 1; i < vec.size(); i++){
			if(vec[i]<tmpStr){
				tmpStr=vec[i];
				index = i;
			}
		}
		string str = vec[index];
		index = 0;
		return str;

	} else {
		error("This queue is empty");
	}
}

//iterates over an array, finds element with lowest value, then deletes it.
string VectorPriorityQueue::dequeueMin() {
	if(size()>0){
		int index = 0;
		string tmpStr = vec[0];
		for(int i = 1; i < vec.size(); i++){
			if(vec[i]<tmpStr){
				tmpStr=vec[i];
				index = i;
			}
		}
		string str = vec[index];
		vec.remove(index);
		index = 0;
		return str;
	} else {
		error("This queue is empty");
	}
}

