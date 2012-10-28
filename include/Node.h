#pragma once
#include "Starbucks.h"

class Node {
public:
	  node(Entry e);

	  node* left_;
	  node* right_;
	  bool isXlevel;

	  static void insert();

};