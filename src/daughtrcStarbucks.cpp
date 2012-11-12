#pragma once
#include "daughtrcStarbucks.h"
#include <math.h>
#include "cinder/Rand.h"

double daughtrcStarbucks::getDistance(double x, double y, double x2, double y2) {
	return sqrt(((x-x2)*(x-x2))+((y-y2)*(y-y2)));
}

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


