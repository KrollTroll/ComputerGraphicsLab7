#ifndef DRAWING_H
#define DRAWING_H
#include "drawbase.h"
#include "image.h"
#include "point.h"
#include "line.h"
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

/**
 * event that is activated upon the mouse being pressed down
 * @param gc     : graphics context object that may be affected
 * @param button : mouse button that was pressed
 * @param x		 : x coordinate of mouse pointer
 * @param y		 : y coordinate of mouse pointer
 */
virtual void mouseButtonDown(GraphicsContext*gc, unsigned int button,int x, int y);

/**
 * event that is activated upon the mouse being released
 * @param gc     : graphics context object that may be affected
 * @param button : mouse button that was pressed
 * @param x		 : x coordinate of mouse pointer
 * @param y		 : y coordinate of mouse pointer
 */
virtual void mouseButtonUp(GraphicsContext*gc, unsigned int button,int x, int y);

/**
 * event that is activated upon the mouse being moved
 * @param gc : graphics context object that may be affected
 * @param x  : x coordinate of mouse pointer
 * @param y  : y coordinate of mouse pointer
 */
virtual void mouseMove(GraphicsContext*gc, int x, int y);

/**
 * this is a helper method to decode the current context color to R, G, and B values
 * @param color
 */
void decodeColor(unsigned int color);

private:
// We will only support one "remembered" line
// In an actual implementation, we would also have one of our "image"
// objects here to store all of our drawn shapes.

//State switch variables
bool dragging; // flag to know if we are dragging
bool dot;      // flag to know if in point mode
bool seg;	   // flag to know if in line mode
bool tri;      // flag to know if in triangle mode

//variables for line drawing
int x0; // x0 and y0 are starting point
int y0;
int x1; // x1 and y1 are ending points
int y1;

//variable for triangle drawing
int tVert;	// this is used to keep track of how many vertices have been drawn
int xOrg;   // xOrg and yOrg are vert 1
int yOrg;
int xVert2; // second vertex
int yVert2;
int xVert3; // third vertex
int yVert3;

//data for storing picture information
image picture;
unsigned int RED;
unsigned int GREEN;
unsigned int BLUE;
unsigned int currentColor;

viewcontext* vc;
char tState;

};
#endif
