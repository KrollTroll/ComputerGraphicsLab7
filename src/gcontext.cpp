/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#define _USE_MATH_DEFINES	// for M_PI
#include <cmath>	// for trig functions
#include "gcontext.h"	

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}

/**
 * This method draws a line using Bresenham's Line drawing algorithm
 * @param x0
 * @param y0 : x0 and y0 are the line origin
 * @param x1
 * @param y1 : x1 and y1 are the line terminal point
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	//if the change in y is less than the change in x
	if(abs(y1-y0) < abs(x1-x0)){
		//if the origin is above the terminal point
		if(x0 > x1){
			//draw a low gradient line from terminal to origin
			lowGradientLine(x1, y1, x0, y0);
		}
		//else if the terminal point is above the origin
		else{
			//draw a low gradient line from origin to terminal
			lowGradientLine(x0, y0, x1, y1);
		}
	}
	//else if the change in x is greater than the change in y
	else{
		if(y0 > y1){
			//draw a high gradient line from terminal to origin
			highGradientLine(x1, y1, x0, y0);
		}
		else{
			//draw a high gradient line from origin to terminal
			highGradientLine(x0, y0, x1, y1);
		}
	}
	return;
}

/**
 * draws a low gradient line
 * 	is a part of the larger line-drawing method using Bresenham's algorithm
 * @param x0
 * @param y0 : x0 and y0 are the origin point
 * @param x1
 * @param y1 : x1 and y1 are the terminal point
 */
void GraphicsContext::lowGradientLine(int x0, int y0, int x1, int y1){
	//determine slopes
	int dx = x1-x0;
	int dy = y1-y0;
	//set an intercept
	int interceptY = 1;
	//if the slope is smaller than 0
	if(dy < 0){
		//flip the intercept and slope
		interceptY = -1;
		dy = -dy;
	}
	int difference = 2*dy-dx;
	int y = y0;

	//for every x point between the origin and the terminal point
	for(int x = x0; x < x1; x++){
		setPixel(x, y);
		//if the difference is lerger than 0
		if(difference > 0){
			//adjust the y and difference values
			y = y+interceptY;
			difference = difference -2*dx;
		}
		difference = difference + 2*dy;
	}
}

/**
 * draws a high gradient line
 * 	is a part of the larger line-drawing method using Bresenham's algorithm
 * @param x0
 * @param y0 : x0 and y0 are the origin point
 * @param x1
 * @param y1 : x1 and y1 are the terminal point
 */
void GraphicsContext::highGradientLine(int x0, int y0, int x1, int y1){
	//determine slopes
	int dx = x1-x0;
	int dy = y1-y0;
	//set an intercept
	int interceptX = 1;
	interceptX = 1;
	//if the slope is smaller than 0
	if(dx < 0){
		interceptX = -1;
		dx = -dx;
	}
	int difference = 2*dx - dy;
	int x = x0;

	//for every y point between the origin and terminal
	for(int y = y0; y < y1; y++){
		setPixel(x, y);
		//if the difference is greater than 0
		if(difference > 0){
			//adjust the x value and difference value
			x = x + interceptX;
			difference = difference - 2*dy;
		}
		difference = difference + 2*dx;
	}
}

/**
 * This is a method that draws a circle using the midpoint algorithm
 * 	it is an extension of the Bresenham algorithm
 * @param x0
 * @param y0 : x0 and y0 are the center point
 * @param radius :radius of the circle
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	//assign x, y, difference, and error values
	int x = radius - 1;
	int y = 0;
	int differenceX = 1;
	int differenceY = 1;
	int error = differenceX - (radius << 1);
	
	//as long as the x value is greater or equal to y
	while(x >= y){
		//set pixels in a standard octant pattern
		setPixel(x0 + x, y0 + y);
		setPixel(x0 + y, y0 + x);
		setPixel(x0 - y, y0 + x);
		setPixel(x0 - x, y0 + y);
		setPixel(x0 - x, y0 - y);
		setPixel(x0 - y, y0 - x);
	    setPixel(x0 + y, y0 - x);
		setPixel(x0 + x, y0 - y);

		//if the error value falls below 0
		if(error <= 0){
			//adjust y and y difference values
			y++;
			error += differenceY;
			differenceY += 2;
		}

		//if the error falls above 0
		if(error > 0){
			//adjust the x and x difference values
			x--;
			differenceX += 2;
			error += differenceX - (radius << 1);
		}
	}
	
	return;	
}

void GraphicsContext::endLoop()
{
	run = false;
}


