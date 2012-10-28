#include "daughtrcStarbucks.h"

daughtrcStarbucks::daughtrcStarbucks() {}

daughtrcStarbucks::~daughtrcStarbucks(void) {}

void daughtrcStarbucks::build(Entry* e, int n) {
}

void daughtrcStarbucks::getNearest(double x, double y) {
}

node* daughtrcStarbucks::insert(Entry* newEntry, Node* currentNode, bool isXlevel) {
	if (currentNode == NULL) // check for empty node
		return new node(newEntry); 

	if (currentNode->e->x == NewEntry->x && currentNode->e->y == newEntry->y) // check for duplicates
		return currentNode;

	if (bool isXlevel == true && newEntry->x < currentNode->e->x) { // on x level and new x is less than current x
		r->left = insert(newEntry, currentNode, !isXlevel);
	} else {
		r->right = insert(newEntry, currentNode, !isXlevel);
	}

	if (bool isXlevel == false && newEntry->y < currentNode->e->y) {
		r->left = insert(newEntry, currentNode, !isXlevel);
	} else {
		r->right = insert(newEntry, currentNode, !isXlevel);
	}

	return currentNode;
}

void daughtrcStarbucks::search(double x, double y, Node* r, bool isXlevel) {
}

