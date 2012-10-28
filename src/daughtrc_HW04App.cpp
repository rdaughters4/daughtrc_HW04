#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include <fstream>
#include <iostream>
#include <string>
#include "daughtrcStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class daughtrc_HW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	bool anythingHappen;

};

void daughtrc_HW04App::setup()
{
	//logic taken from Matthew Dwyer
	ifstream in("Starbucks_2006.csv");
	vector <Entry> storage;

	string line;
	double x_value;
	double y_value;
	char separator;
	int count = 0;
	anythingHappen = false;

	while (in.good()) {
		Entry* e = new Entry();
		storage.push_back(*e);
		getline(in, line, ',');

		storage[count].identifier = line;
		in >> x_value;
		storage[count].x = x_value;
		in >> separator;
		in >> y_value;
		storage[count].y = y_value;
		count++;
		anythingHappen = true;
		console() << line;

	}

	Entry* list = new Entry[storage.size()];

	for (int i = 0; i < storage.size(); i++)
		list[i] = storage[i];

}

void daughtrc_HW04App::mouseDown( MouseEvent event )
{
}

void daughtrc_HW04App::update()
{
}

void daughtrc_HW04App::draw()
{
	// clear out the window with black
	if (anythingHappen == false) {
		gl::clear( Color( 0, 0, 0 ) ); 
	}
	if (anythingHappen == true) {
		gl::clear( Color(250, 250, 250) );
	}
}

CINDER_APP_BASIC( daughtrc_HW04App, RendererGl )
