#pragma once
#include "daughtrcStarbucks.h"
#include <math.h>
#include "cinder/Rand.h"

Node::Node() {
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
	if (currentNode->e->x == newEntry->x && currentNode->e->y == newEntry->y)
		return currentNode;

	// on x level and new x is less than current x
	if ((isXlevel == true) && (newEntry->x < currentNode->e->x)) {
		currentNode->left = insert(newEntry, currentNode, !isXlevel);
	} else {
		currentNode->right = insert(newEntry, currentNode, !isXlevel);
	}

	// on y level and new y is less than current y
	if (isXlevel == false && newEntry->y < currentNode->e->y) {
		currentNode->left = insert(newEntry, currentNode, !isXlevel);
	} else {
		currentNode->right = insert(newEntry, currentNode, !isXlevel);
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

	// create sentinel node
	sentinel = new Node(e);

	//build the k-d tree
	for (int i = 1; i < n; i++)
		insert(&e[i], sentinel, true);
}

Entry* daughtrcStarbucks::getNearest(double x, double y) {
	return search(x, y, sentinel, true);
}

Entry* daughtrcStarbucks::search(double x, double y, Node* currentNode, bool isXlevel) {
	// if currentNode is null return currentNode
	if (currentNode == NULL)
		return currentNode->e;

	// check if the currentNode is equal to the new position
	if ((abs(currentNode->e->x-x) <= 0.00001) && (abs(currentNode->e->y-y) <= 0.00001))
		return currentNode->e;

	// create two node* pointers
	Node* bestLeft = NULL;
	Node* bestRight = NULL;

	// determine which side to go down
	if (isXlevel == true && currentNode->e->x < x) {
		bestLeft->e = search(x, y, currentNode->left, !isXlevel);
	} else {
		bestRight->e = search(x, y, currentNode->right, !isXlevel);
	}

	if (isXlevel == false && currentNode->e->y < y) {
		bestLeft->e = search(x, y, currentNode->left, !isXlevel);
	} else {
		bestRight->e = search(x, y, currentNode->right, !isXlevel);
	}

	//decide which node to return
	if (bestLeft == NULL && bestRight != NULL) {
		if (getDistance(x, y, currentNode) > getDistance(x, y, bestRight))
			return bestRight->e;
		else
			return currentNode->e;
	} else if (bestLeft != NULL && bestRight == NULL) {
		if (getDistance(x, y, currentNode) > getDistance(x, y, bestLeft))
			return bestLeft->e;
		else
			return currentNode->e;
	} else {
		double shortestDistance = min(getDistance(x,y,currentNode),min(getDistance(x,y,bestRight),getDistance(x,y,bestLeft)));
		if(shortestDistance == getDistance(x,y,currentNode))
			return currentNode->e;
		else if(shortestDistance == getDistance(x,y,bestRight))
			return bestRight->e;
		else
			return bestLeft->e;
	}

}

double daughtrcStarbucks::getDistance(double x, double y, Node* currentNode) {
	return sqrt((x-currentNode->e->x)*(x-currentNode->e->x)+(y-currentNode->e->y)*(y-currentNode->e->y));
}


