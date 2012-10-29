#pragma once
#include "Starbucks.h"
#include "Node.h"

class daughtrcStarbucks : public Starbucks {
private:
	Node* root;

public:
	daughtrcStarbucks();
	~daughtrcStarbucks(void);

	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	Node* insert(Entry* newEntry, Node* currentNode, bool isXlevel);
	Entry* search(double x, double y, Node* currentNode, bool isXlevel);
	double distanceTo(double x, double y, Node* currentNode);

};
