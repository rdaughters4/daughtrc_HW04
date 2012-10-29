#include "daughtrcStarbucks.h"
#include <math.h>

daughtrcStarbucks::daughtrcStarbucks() {}

daughtrcStarbucks::~daughtrcStarbucks(void) {}

void daughtrcStarbucks::build(Entry* c, int n) {
	//create new array
	Entry arrayData = new Entry(n);

	//copy the array to another array
	for (int i = 0; i < n; i++) {
		arrayData[i] = c[i];
	}
	c = arrayData;

	// create sentinel node
	sentinel = new Node(c);

	//build the k-d tree
	for (int i = 1; i < n; i++)
		insert(&c[i], sentinel, true);
}

void daughtrcStarbucks::getNearest(double x, double y) {
	return search(x, y, sentinel, true)->e;
}

node* daughtrcStarbucks::insert(Entry* newEntry, Node* currentNode, bool isXlevel) {
	// check for empty node
	if (currentNode == NULL)
		return new node(newEntry); 

	// check for duplicates
	if (currentNode->e->x == NewEntry->x && currentNode->e->y == newEntry->y)
		return currentNode;

	// on x level and new x is less than current x
	if (bool isXlevel == true && newEntry->x < currentNode->e->x) {
		r->left = insert(newEntry, currentNode, !isXlevel);
	} else {
		r->right = insert(newEntry, currentNode, !isXlevel);
	}

	// on y level and new y is less than current y
	if (bool isXlevel == false && newEntry->y < currentNode->e->y) {
		r->left = insert(newEntry, currentNode, !isXlevel);
	} else {
		r->right = insert(newEntry, currentNode, !isXlevel);
	}

	return currentNode;
}

void daughtrcStarbucks::search(double x, double y, Node* currentNode, bool isXlevel) {
	// if currentNode is null return currentNode
	if (currentNode == NULL)
		return currentNode;

	// check if the currentNode is equal to the new position
	if ((abs(currentNode->e->x-x) <= 0.00001) && (abs(currentNode->e->y-y) <= 0.00001))
		return currentNode;

	// create two node* pointers
	node* bestLeft = NULL;
	node* bestRight = NULL;

	// determine which side to go down
	if (isXlevel == true && currentNode->e->x < x) {
		bestLeft = search(x, y, currentNode->left, !isXlevel);
	} else {
		bestright = search(x, y, currentNode->right, !isXlevel);
	}

	if (isXlevel == false && currentNode->e->y < y) {
		bestLeft = search(x, y, currentNode->left, !isXlevel);
	} else {
		bestright = search(x, y, currentNode->right, !isXlevel);
	}

	//decide which node to return
	if (bestLeft == NULL && bestRight != NULL) {
		if (distanceTo(x, y, currentNode) > distanceTo(x, y, bestRight))
			return bestRight;
		else
			return currentNode;
	} else if (bestLeft != NULL && bestRight == NULL) {
		if (distanceTo(x, y, currentNode) > distanceTo(x, y, bestLeft))
			return bestLeft;
		else
			return currentNode;
	} else {
		double shortestDistance = min(getDistance(x,y,currentNode),min(getDistance(x,y,bestRight),getDistance(x,y,bestLeft)));
		if(shortestDistance == getDistance(x,y,currentNode))
			return currentNode;
		else if(shortestDistance == getDistance(x,y,bestRight))
			return bestRight;
		else
			return bestLeft;
	}

}

double daughtrcStarbucks::distanceTo(double x, double y, Node* currentNode) {
	return sqrt((x-currentNode->e->x)*(x-currentNode->e->x)+(y-currentNode->x->y)*(y-currentNode->e->y));
}


