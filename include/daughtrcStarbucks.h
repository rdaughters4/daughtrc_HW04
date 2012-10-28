#pragma once
#include "Starbucks.h"
using namespace std;

class daughtrcStarbucks : public Starbucks {
public:
	daughtrcStarbucks();
	~daughtrcStarbucks(void);

	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);

};
