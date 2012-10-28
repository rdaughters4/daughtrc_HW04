#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class daughtrc_HW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void daughtrc_HW04App::setup()
{
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
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( daughtrc_HW04App, RendererGl )
