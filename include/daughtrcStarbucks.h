#pragma once
#include <string>
#include "Starbucks.h"
#include "Resources.h"
#include "cinder/Rand.h"
using namespace std;

class daughtrcStarbucks : public Starbucks {

  public:
	  virtual void build(Entry* c, int n);
	  virtual Entry* getNearest(double x, double y);
	  double getDistance(double x, double y, double x2, double y2);
	  Entry* dataStructureArray;
	  int arrayLength;
};
