#include "daughtrcStarbucks.h"

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
		insert(&c, sentinel, true);
}

void daughtrcStarbucks::getNearest(double x, double y) {
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

}

double daughtrcStarbucks::distanceTo(double x, double y, Node* currentNode) {
	return sqrt((x-currentNode->e->x)*(x-currentNode->e->x)+(y-currentNode->x->y)*(y-currentNode->e->y));
}


