#pragma once
#include <string>
#include "Starbucks.h"
#include "Resources.h"
#include <string>
#include "cinder/Rand.h"
using namespace std;

class Node {
  public:
	  Node* left;
	  Node* right;
	  Entry* e;

	  Node();
	  Node(Entry* e1);
};

class daughtrcStarbucks : public Starbucks {

  public:
	  Node* sentinel;
	  daughtrcStarbucks();
	  ~daughtrcStarbucks(void);
	  virtual void build(Entry* c, int n);
	  virtual Entry* getNearest(double x, double y);
	  Node* insert(Entry* newEntry, Node* currentNode, bool isXlevel);
	  Entry* search(double x, double y, Node* currentNode, bool isXlevel);
	  double getDistance(double x, double y, Node* currentNode);
	  void mix(Entry* entries, int length);

  private:
	  Entry* e;
	  bool isXlevel;
	  double x;
	  double y;
};
