#pragma once
#include "daughtrcStarbucks.h"
#include <math.h>
#include "cinder/Rand.h"

/*Node::Node() {
	left = NULL;
	right = NULL;
	e = NULL;
}

Node::Node(Entry* e1) {
	left = right = NULL;
	e = e1;
}

daughtrcStarbucks::daughtrcStarbucks() {
}

daughtrcStarbucks::~daughtrcStarbucks(void){
}

Node* daughtrcStarbucks::insert(Entry* newEntry, Node* currentNode, bool isXlevel) {
	// check for empty node
	if (currentNode == NULL)
		return new Node(newEntry); 

	// check for duplicates
	if ((abs(currentNode->e->x-newEntry->x) <= 0.00001) && (abs(currentNode->e->y-newEntry->y) <= 0.00001))
		return currentNode;

	// on x level and new x is less than current x
	if (isXlevel) {
		if (newEntry->x < currentNode->e->x)
			currentNode->left = insert(newEntry, currentNode->left, !isXlevel);
		else 
			currentNode->right = insert(newEntry, currentNode->right, !isXlevel);
	}
	else {
		if (newEntry->y < currentNode->e->y)
			currentNode->left = insert(newEntry, currentNode->left, !isXlevel);
		else 
			currentNode->right = insert(newEntry, currentNode->right, !isXlevel);
	}

	return currentNode;
}


void daughtrcStarbucks::build(Entry* e, int n) {
	//create new array
	Entry* arrayData = new Entry[n];

	//copy the array to another array
	for (int i = 0; i < n; i++) {
		arrayData[i] = e[i];
	}
	e = arrayData;

	//randomize data
	mix(e, n);

	//create sentinel node
	sentinel = new Node(e);

	//build the k-d tree
	for (int i = 1; i < n; i++)
		insert(&e[i], sentinel, true);
}

Entry* daughtrcStarbucks::getNearest(double x, double y) {
	return search(x, y, sentinel, true)->e;
}

//logic based off of Youxuan
Node* daughtrcStarbucks::search(double x, double y, Node* sentinel, bool isXlevel) {
	// if currentNode is null return currentNode
	if (sentinel == NULL)
		return sentinel;

	// check if the currentNode is equal to the new position
	if ((abs(sentinel->e->x-x) <= 0.00001) && (abs(sentinel->e->y-y) <= 0.00001))
		return sentinel;

	// create two node* pointers
	Node* bestLeft = NULL;
	Node* bestRight = NULL;

	// determine which side to go down
	if (isXlevel) {
		if (sentinel->e->x < x) 
			bestLeft = search(x, y, sentinel->left, !isXlevel);
		else 
			bestRight = search(x, y, sentinel->right, !isXlevel);
	}
	else {
		if (sentinel->e->y < y)
			bestLeft = search(x, y, sentinel->left, !isXlevel);
		else
			bestRight = search(x, y, sentinel->right, !isXlevel);
	}

	if(bestLeft == NULL && bestRight == NULL)
		return sentinel;

	//decide which node to return
	if (bestLeft == NULL && bestRight != NULL) {
		if (getDistance(x, y, sentinel) > getDistance(x, y, bestRight))
			return bestRight;
		else
			return sentinel;
	} else if (bestLeft != NULL && bestRight == NULL) {
		if (getDistance(x, y, sentinel) > getDistance(x, y, bestLeft))
			return bestLeft;
		else
			return sentinel;
	} else {
		double shortestDistance = min(getDistance(x,y,sentinel),min(getDistance(x,y,bestRight),getDistance(x,y,bestLeft)));
		if(shortestDistance == getDistance(x,y,sentinel))
			return sentinel;
		else if(shortestDistance == getDistance(x,y,bestRight))
			return bestRight;
		else
			return bestLeft;
	}

}
*/
double daughtrcStarbucks::getDistance(double x, double y, double x2, double y2) {
	return sqrt(((x-x2)*(x-x2))+((y-y2)*(y-y2)));
}

//taken from Youxuan
/*void daughtrcStarbucks::mix(Entry* entries, int length){
	int pick = 0;
	for(int i=0;i<length-1;i++){
		pick = cinder::Rand::randInt(i+1,length);
		Entry temp = entries[i];
		entries[i] = entries[pick];
		entries[pick] = temp;
	}
}*/

void daughtrcStarbucks::build(Entry* c, int n) {
	arrayLength = n;
	dataStructureArray = new Entry[n];
	for (int i = 0; i < arrayLength; i++) {
		dataStructureArray[i] = c[i];
	}
}

Entry* daughtrcStarbucks::getNearest(double x, double y) {
	Entry* temp = new Entry();
	Entry best = dataStructureArray[0];
	double bestDistance = getDistance(dataStructureArray[0].x, dataStructureArray[0].y, x, y);
	for (int i = 1; i < arrayLength; i++) {
		double tempDistance = getDistance(dataStructureArray[i].x, dataStructureArray[i].y, x, y);
		if (tempDistance < bestDistance) {
			best = dataStructureArray[i];
			bestDistance = tempDistance;
		}
	}
	*temp = best;
	return temp;
}


