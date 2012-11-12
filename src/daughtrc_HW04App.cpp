#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
#include "Starbucks.h"
#include "daughtrcStarbucks.h"
#include "Resources.h"
#include "CensusData.h"
#include "StarbucksWithColor.h"
#include "EntryColor.h"
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
	void drawCensusData(CensusData* locations, int numOfLocations);
	void drawCensusData2010(CensusData* locations, int numOfLocations);
	void drawColorLocations(EntryColor* locations, int numOfLocations);

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

	// variables used for colorEntry
	int redCount;
	int greenCount;
	int blueCount;

	// delacare data structure variables
	daughtrcStarbucks* myTree;
	StarbucksWithColor* entryColorArr;
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

	// initialize myTree and entryColorArr
	myTree = new daughtrcStarbucks();
	entryColorArr = new StarbucksWithColor();

	// logic taken from Matthew Dwyer
	// read in starbucks locations from a file
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
	} // end reading in starbucks locations

	// copy storage to an array of Entry objects
	Entry* list = new Entry[storage.size()];
	for (int i = 0; i < storage.size(); i++)
		list[i] = storage[i];

	// copy storage to an array of EntryColor objects
	redCount = 0;
	greenCount = 75;
	blueCount = 175;
	EntryColor* colorList = new EntryColor[storage.size()];
	for (int i = 0; i < storage.size(); i++) {
		if (redCount > 255)
			redCount = 0;
		if (greenCount > 255)
			greenCount = 0;
		if (blueCount > 255)
			blueCount = 0;
		colorList[i].identifier = storage[i].identifier;
		colorList[i].x = storage[i].x;
		colorList[i].y = storage[i].y;
		colorList[i].red = redCount;
		colorList[i].green = greenCount;
		colorList[i].blue = blueCount;
		redCount++;
		greenCount++;
		blueCount++;
	}


	// build kd tree
	myTree->build(list, count);

	// build entryColorArr
	entryColorArr->build(colorList, count);

	// read in census 2000 data
	ifstream in2("Census_2000.csv");
	vector <CensusData> census2000;
	int population;
	double x_val;
	double y_val;
	int garbage;
	char separate;
	int count2 = 0;

	while (in2.good()) {
		CensusData* census = new CensusData();
		census2000.push_back(*census);
		in2 >> garbage;		// first row
		in2 >> separate;
		in2 >> garbage;		// second row
		in2 >> separate;
		in2 >> garbage;		// third row
		in2 >> separate;
		in2 >> garbage;		// fourth row
		in2 >> separate;
		in2 >> population;	// population row
		census2000[count2].population = population;
		in2 >> separate;
		in2 >> x_val;		// x row
		census2000[count2].x = x_val;
		in2 >> separate;
		in2 >> y_val;		// y row
		census2000[count2].y = y_val;
		count2++;
	} // end reading in census 2000 data 

	// copy census2000 to an array of CensusData objects
	CensusData* censusData_2000 = new CensusData[census2000.size()];
	for (int i = 0; i < census2000.size(); i++)
		censusData_2000[i] = census2000[i];

	// read in census 2010 data
	ifstream in3("Census_2010.csv");
	vector <CensusData> census2010;

	int population2;
	double x_val2;
	double y_val2;
	int garbage2;
	char separate2;
	int count3 = 0;

	while (in3.good()) {
		CensusData* census2 = new CensusData();
		census2010.push_back(*census2);
		in3 >> garbage2;		// first row
		in3 >> separate2;
		in3 >> garbage2;		// second row
		in3 >> separate2;
		in3 >> garbage2;		// third row
		in3 >> separate2;
		in3 >> garbage2;		// fourth row
		in3 >> separate2;
		in3 >> population2;	// population row
		census2010[count3].population = population2;
		in3 >> separate2;
		in3 >> x_val2;		// x row
		census2010[count3].x = x_val2;
		in3 >> separate2;
		in3 >> y_val2;		// y row
		census2010[count3].y = y_val2;
		count3++;
	} // end reading in census 2010 data

	// copy census2010 to an array of CensusData objects
	CensusData* censusData_2010 = new CensusData[census2010.size()];
	for (int i = 0; i < census2010.size(); i++)
		censusData_2010[i] = census2010[i];

	// draw census2000
	//drawCensusData(censusData_2000, count2);

	// draw census2010
	//drawCensusData2010(censusData_2010, count3);

	// draw locations
	//drawLocations(list, count);

	// draw colorLocations
	drawColorLocations(colorList, count);
	
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
	double userX = event.getX()/zoomAmount;
	double userY = event.getY()/zoomAmount;

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

void daughtrc_HW04App::drawCensusData(CensusData* locations, int numOfLocations) {
	Color c = Color(0,0,255);
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

void daughtrc_HW04App::drawCensusData2010(CensusData* locations, int numOfLocations) {
	Color c = Color(255,75,0);
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

void daughtrc_HW04App::drawColorLocations(EntryColor* locations, int numOfLocations) {
	for (int i = 0; i < numOfLocations; i++) {
		Color c = Color(locations[i].red,locations[i].green,locations[i].blue);
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

void daughtrc_HW04App::draw()
{
	// clear out the window with black
	gl::draw(*zoomSurface);
}

CINDER_APP_BASIC( daughtrc_HW04App, RendererGl )
