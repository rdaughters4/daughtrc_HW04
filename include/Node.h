#pragma once
#include "Starbucks.h"

class Node {
public:
	  Node();
	  Node(Entry* e1);

	  Node* left_;
	  Node* right_;
	  Entry* e;

};