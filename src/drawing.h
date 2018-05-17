#ifndef DRAWING_H
#define DRAWING_H


#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "drawbase.h"
#include "image.h"
#include "triangle.h"
// forward reference
class GraphicsContext;
class drawing : public DrawingBase
{
public:

/**
 * General constructor
 */
drawing();

/**
 * destructor
 */
~drawing();

/**
 * repaint the image upon an exposure event
 * @param gc : graphics context to repaint
 */
virtual void paint(GraphicsContext* gc);

/**
 * event that is activated upon a key being pressed down
 * @param gc      : graphics context object that may be affected
 * @param keycode : code of key that was pressed
 */
virtual void keyDown(GraphicsContext* gc, unsigned int keycode);

virtual void mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y);

virtual void mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y);

virtual void mouseMove(GraphicsContext* gc, int x, int y);

/**
 * this is a helper method to decode the current context color to R, G, and B values
 * @param color
 */
void decodeColor(unsigned int color);

void parseFile(string inFile, image& picture);

private:
// We will only support one "remembered" line
// In an actual implementation, we would also have one of our "image"
// objects here to store all of our drawn shapes.

void drawAxes();

//State switch variables
bool dragging; // flag to know if we are dragging
bool dot;      // flag to know if in point mode
bool seg;	   // flag to know if in line mode
bool tri;      // flag to know if in triangle mode

//data for storing picture information
unsigned int RED;
unsigned int GREEN;
unsigned int BLUE;

char tState;
image picture;
viewcontext* vc;

float x0, y0, z0, x1, y1, z1, x2, y2, z2;

};
#endif
