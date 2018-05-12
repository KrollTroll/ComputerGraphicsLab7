#include <unistd.h>
#include <iostream>
#include "x11context.h"
#include "drawing.h"
#include "viewcontext.h"

int main(void)
{
	GraphicsContext*gc = new X11Context(800,600,GraphicsContext::BLACK);
	gc->setColor(GraphicsContext::GREEN);
	//make an stl reader
	drawing md;
	md.paint(gc);

	gc->runLoop(&md);

	// on window
	delete gc;
	return 0;
}
