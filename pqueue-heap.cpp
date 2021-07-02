/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include "strlib.h"
const int kDefaultSize = 4;


//constructor, creates empty priority queue, which has "Dummy" at 0 index, to make calculations easier.
HeapPriorityQueue::HeapPriorityQueue() {
	allocatedLength = kDefaultSize;
	names = new string[allocatedLength];
	names[0] = "Dummy";
	logicalLength = 1; //int which was the value of the index, at which the next element should be inserted.
}

//destructor, deletes queue after it's not used anymore.
HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] names;
}

int HeapPriorityQueue::size() {
	return logicalLength-1;
}

bool HeapPriorityQueue::isEmpty() {
	return size() == 0;
}

//enqueues new element, if size is 0, just puts it in, otherwise calls bubbleUp function.
void HeapPriorityQueue::enqueue(string value) {
	if(allocatedLength==logicalLength){
		increaseSize();
	}
	if(size()==0){
		names[logicalLength]=value;
		logicalLength++;
	} else {
		names[logicalLength]=value;
		int tmpSize = logicalLength;
		logicalLength++;
		bubbleUp(names,tmpSize);
	}
}
//returns first element.
string HeapPriorityQueue::peek() {
	if(isEmpty()){
		error("This tree is empty");
	}
	return names[1];
}

//returns element which is at highest point in the tree, then calls bubbleDown function to make sure array stays sorted.
string HeapPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("This tree is empty");
	}
	string result = names[1];
	string tmpName = names[1];
	names[1] = names[logicalLength-1];
	names[logicalLength-1]=tmpName;
	logicalLength--;
	bubbleDown(names,logicalLength);
	return result;
}

//increases size by 2 once allocated length equals logicalLength.
void HeapPriorityQueue::increaseSize(){
	string* newArray = new string[allocatedLength*2];
	for (int i = 0; i < allocatedLength; i++) {
		newArray[i] = names[i];
	}
	allocatedLength =allocatedLength*2;
	delete[] names;
	names = newArray;
}

//swaps new element with its parent, if it has lower value.
void HeapPriorityQueue::bubbleUp(string* names, int tmpSize){
	while(true){
		if(names[tmpSize]<names[tmpSize/2]){
			string tmpName = names[tmpSize/2];
			names[tmpSize/2]= names[tmpSize];
			names[tmpSize] = tmpName;
			tmpSize = tmpSize/2;
			if(tmpSize==1){
				break;
			}
		} else {
			break;
		}
	}	
}

//swaps element at the top with its smallest childs, if such exists.
void HeapPriorityQueue::bubbleDown(string* names, int logicalLength){
	string leftChild;
	string rightChild;
	int smallestIndex;
	int index = 1;
	while(true){
		if(index*2<logicalLength){
			leftChild = names[index*2];
			if(index*2+1<logicalLength){
				rightChild = names[index*2+1];
				if(leftChild<=rightChild){
					smallestIndex = index*2;
				} else {
					smallestIndex = index*2+1;
				}
			} else {
				smallestIndex = index*2;
			}
		} else {
			break;
		}
		if(names[index]>names[smallestIndex]){
			string tmpName = names[index];
			names[index] = names[smallestIndex];
			names[smallestIndex] = tmpName;
			index = smallestIndex;
		} else {
			break;
		}
	}
}

