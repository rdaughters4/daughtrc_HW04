#pragma once
#include "StarbucksWithColor.h"
#include "EntryColor.h"

void StarbucksWithColor::build(EntryColor* c, int n) {
	arrayLength = n;
	dataStructureArray = new EntryColor[n];
	for (int i = 0; i < arrayLength; i++) {
		dataStructureArray[i] = c[i];
	}
}

EntryColor* StarbucksWithColor::getNearest(double x, double y) {
	EntryColor* temp = new EntryColor();
	EntryColor best = dataStructureArray[0];
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

double StarbucksWithColor::getDistance(double x, double y, double x2, double y2) {
	return sqrt(((x-x2)*(x-x2))+((y-y2)*(y-y2)));
}