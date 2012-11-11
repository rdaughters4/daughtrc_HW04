#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Starbucks.h"
#include "daughtrcStarbucks.h"
#include "Resources.h"
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class daughtrc_HW04App : public AppBasic {
  public:
	void prepareSettings(Settings* settings);
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void drawLocations(Entry* locations, int numOfLocations);
	void clearWindow(uint8_t* pixels);
	void zoom();
	void keyDown( KeyEvent event );

private:
	// declare window size
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kSurfaceSize=1024;

	// variables
	Surface* mySurface_;
	uint8_t* myPixels_;
	Surface* zoomSurface;
	uint8_t* zoomPixels;

	// variables used for nearest location
	double oldX;
	double oldY;

	// variables used for zoom function
	int zoomAmount;

	// delacare data structure variables
	daughtrcStarbucks* myTree;
	Entry* bestLocation;
};

void daughtrc_HW04App::prepareSettings(Settings* settings)
{
	settings->setWindowSize(kAppWidth,kAppHeight);
	settings->setResizable(false);
}

void daughtrc_HW04App::setup()
{
	// initialize surfaces
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,false);
	myPixels_ = (*mySurface_).getData();
	zoomSurface = new Surface(kSurfaceSize,kSurfaceSize,false);
	zoomPixels = (*zoomSurface).getData();
	
	// clear window
	clearWindow(myPixels_);

	// initialize nearest location variables
	oldX = NULL;
	oldY = NULL;

	// initialize zoomAmount
	zoomAmount = 1;

	// logic taken from Matthew Dwyer
	// read in starbucks locations from a file
	myTree = new daughtrcStarbucks();
	ifstream in("Starbucks_2006.csv");
	vector <Entry> storage;

	string line;
	double x_value;
	double y_value;
	char separator;
	int count = 0;

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

	}

	Entry* list = new Entry[storage.size()];

	for (int i = 0; i < storage.size(); i++)
		list[i] = storage[i];

	// draw locations
	drawLocations(list, count);

	// build kd tree
	myTree->build(list, count);
	bestLocation = myTree->getNearest(0.323472,0.621797);

	console() << bestLocation->identifier << std::endl;


	
}

void daughtrc_HW04App::mouseDown( MouseEvent event )
{
	// redraw the old location back to green
	if (oldX != NULL && oldY != NULL) {
		Color c = Color(0,250,0);
		int index = 3 * ((oldX/zoomAmount) + (oldY/zoomAmount) * kSurfaceSize);
		myPixels_[index] = c.r;
		myPixels_[index+1] = c.g;
		myPixels_[index+2] = c.b;
	}

	// store users click
	double userX = event.getX();
	double userY = event.getY();

	//convert to floats
	userX = userX/800;
	userY = 1-(userY/600);

	// change the color of the nearest starbucks location
	Entry* nearestStarbucks = myTree->getNearest(userX, userY);
	Color c = Color(250,0,0);
	double xd = nearestStarbucks->x*800;
	int x = floor(xd);
	double yd = nearestStarbucks->y*600;
	int y = floor(600-yd);
	int index = 3 * ((x/zoomAmount) + (y/zoomAmount) * kSurfaceSize);
	myPixels_[index] = c.r;
	myPixels_[index+1] = c.g;
	myPixels_[index+2] = c.b;

	oldX = x;
	oldY = y;

}

void daughtrc_HW04App::update()
{
	zoom();
}

void daughtrc_HW04App::drawLocations(Entry* locations, int numOfLocations) {
	Color c = Color(0,250,0);
	for (int i = 0; i < numOfLocations; i++) {
		double xd = locations[i].x*800;
		int x = floor(xd);
		double yd = locations[i].y*600;
		int y = floor(600-yd);
		int index = 3 * (x + y * kSurfaceSize);
		myPixels_[index] = c.r;
		myPixels_[index+1] = c.g;
		myPixels_[index+2] = c.b;
	}
}

void daughtrc_HW04App::keyDown( KeyEvent event ) {
	if (event.getCode() == KeyEvent::KEY_1) {
		console() << "plus pressed" << endl;
		zoomAmount *= 2;
	}

	if (event.getCode() == KeyEvent::KEY_2) {
		if (zoomAmount != 1) {
			console() << "minus pressed" << endl;
			zoomAmount /= 2;
		}
	}
}

void daughtrc_HW04App::clearWindow(uint8_t* pixels){
	Color c = Color(0, 0, 0);
	for(int y = 0; y < kSurfaceSize; y++){
		for(int x = 0; x < kSurfaceSize; x++){
			int index = 3*(x + y*kAppWidth);
			pixels[index] = c.r;
			pixels[index+1] = c.g;
			pixels[index+2] = c.b;
		}
	}
}

void daughtrc_HW04App::zoom() {
	for (int i = 0; i < kSurfaceSize; i++) {
		for (int j = 0; j < kSurfaceSize; j++) {
			int index = 3*(i + j * kSurfaceSize);
			int index2 = 3*((i/zoomAmount) + (j/zoomAmount) * kSurfaceSize);

			zoomPixels[index] = myPixels_[index2];
			zoomPixels[index+1] = myPixels_[index2+1];
			zoomPixels[index+2] = myPixels_[index2+2];
		}
	}
}

void daughtrc_HW04App::draw()
{
	// clear out the window with black
	gl::draw(*zoomSurface);
}

CINDER_APP_BASIC( daughtrc_HW04App, RendererGl )
