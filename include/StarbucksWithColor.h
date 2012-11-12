#pragma once
#include "EntryColor.h"

class StarbucksWithColor {
public:
	void build(EntryColor* c, int n);
	EntryColor* getNearest(double x, double y);
	double getDistance(double x, double y, double x2, double y2);
	EntryColor* dataStructureArray;
	int arrayLength;
};