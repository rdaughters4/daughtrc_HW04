#pragma once
#include "Starbucks.h"
#include "Node.h"

class daughtrcStarbucks : public Starbucks {
private:
	Node* root;

public:
	daughtrcStarbucks();
	~daughtrcStarbucks(void);

	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);
	Node* insert(Entry e, Node* r, bool isXlevel);
	Entry* search(double x, double y, Node* r, bool isXlevel);

};
