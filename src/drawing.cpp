#include "drawing.h"
#include "gcontext.h"

#include <iostream>
#include <fstream>

/**
 * constructor
 */
drawing::drawing()
{
	//initalize variables
	dragging = false;

	dot = true;
	seg = false;
	tri = false;

	tVert = 0;
	xOrg = xVert2 = yVert2 = xVert3 = yVert3 = 0;
	yOrg = 0;

	x0 = x1 = y0 = y1 = 0;
	RED = GREEN = BLUE = 0;
	//decode default color value
	decodeColor(GraphicsContext::GREEN);
	vc = new viewcontext();
	tState = 'x';
	return;
}

/**
 * destructor
 */
drawing::~drawing(){
	delete vc;
}

/**
 * repaint the image upon an exposure event
 * @param gc : graphics context to repaint
 */
void drawing::paint(GraphicsContext*gc)
{
	//erase windows and redraw
	gc->clear();
	picture.draw(gc, vc);
	return;
}

/**
 * event that is activated upon a key being pressed down
 * @param gc      : graphics context object that may be affected
 * @param keycode : code of key that was pressed
 */
void drawing::keyDown(GraphicsContext* gc, unsigned int keycode){
	//this ensures that state cannot be changed if currently drawing
	if(!dragging){
			//p point
			if(keycode == 112){
				dot = true;
				seg = false;
				tri = false;
				//tState = 'x';
				tVert = 0;
			}
			//l line
			else if(keycode == 108){
				dot = false;
				seg = true;
				tri = false;
				//tState = 'x';
				tVert = 0;
			}
			//t triangle
			else if(keycode == 116){
				dot = false;
				seg = false;
				tri = true;
				//tState = 'x';
				tVert = 0;
			}
			//hit 1 for red
			else if(keycode == 49){
				gc->setColor(GraphicsContext::RED);
				decodeColor(GraphicsContext::RED);
			}
			//hit 2 for yellow
			else if(keycode == 50){
				gc->setColor(GraphicsContext::YELLOW);
				decodeColor(GraphicsContext::YELLOW);
			}
			//hit 3 for green
			else if(keycode == 51){
				gc->setColor(GraphicsContext::GREEN);
				decodeColor(GraphicsContext::GREEN);
			}
			//hit 4 for blue
			else if(keycode == 52){
				gc->setColor(GraphicsContext::BLUE);
				decodeColor(GraphicsContext::BLUE);
			}
			//hit 5 for magenta
			else if(keycode == 53){
				gc->setColor(GraphicsContext::MAGENTA);
				decodeColor(GraphicsContext::MAGENTA);
			}
			//hit 6 for cyan
			else if(keycode == 54){
				gc->setColor(GraphicsContext::CYAN);
				decodeColor(GraphicsContext::CYAN);
			}
			//hit 7 for gray
			else if(keycode == 55){
				gc->setColor(GraphicsContext::GRAY);
				decodeColor(GraphicsContext::GRAY);
			}
			//hit 8 for white
			else if(keycode == 56){
				gc->setColor(GraphicsContext::WHITE);
				decodeColor(GraphicsContext::WHITE);
			}
			//hit s to save an image
			else if(keycode == 115){
				std::ofstream output;
				output.open("PictureOutput.txt");
				output << "PICTURE OUTPUT" << std::endl;
				output << picture << std:: endl;
				output.close();
			}
			//hit o to open an image
			else if(keycode == 111){
				picture.erase();
				std::ifstream input;
				input.open("PictureOutput.txt");
				while(input){
					picture.in(input);
				}
				input.close();
				gc->clear();
				vc->undo();
				picture.draw(gc, vc);

				dot = true;
				seg = false;
				tri = false;
				tVert = 0;
				tState = 'x';
				gc->setColor(GraphicsContext::GREEN);
				decodeColor(GraphicsContext::GREEN);
			}
			//reset pressed
			else if(keycode == 114){
				vc->undo();
				gc->clear();
				picture.draw(gc, vc);
			}


			//transformation select
			// b is translate
			else if(keycode == 98){
				tState = 't';
			}
			// n is rotate
			else if(keycode == 110){
				tState = 'r';
			}
			// m is scale
			else if(keycode == 109){
				tState = 's';
			}

			if(tState != 'x'){
				if(tState == 't'){
					//> pressed
					if(keycode == 46){
						vc->changeX('+');
						gc->clear();
						picture.draw(gc, vc);
					}
					//k pressed
					else if(keycode == 107){
						vc->changeY('-');
						gc->clear();
						picture.draw(gc, vc);
					}
					//< pressed
					else if(keycode == 44){
						vc->changeX('-');
						gc->clear();
						picture.draw(gc, vc);
					}
					//i pressed
					else if(keycode == 105){
						vc->changeY('+');
						gc->clear();
						picture.draw(gc, vc);
					}
				}
				//rotation state
				else if(tState == 'r'){
					//< pressed
					if(keycode == 44){
						vc->changeDeg('+');
						gc->clear();
						picture.draw(gc, vc);
					}
					//> pressed
					else if(keycode == 46){
						vc->changeDeg('-');
						gc->clear();
						picture.draw(gc, vc);
					}
				}
				//scaling state
				else if(tState == 's'){
					//k pressed
					if(keycode == 107){
						vc->scale('-');
						gc->clear();
						picture.draw(gc, vc);
					}
					//i pressed
					else if(keycode == 105){
						vc->scale('+');
						gc->clear();
						picture.draw(gc, vc);
					}
				}
			}
	}
}

/**
 * event that is activated upon the mouse being pressed down
 * @param gc     : graphics context object that may be affected
 * @param button : mouse button that was pressed
 * @param x		 : x coordinate of mouse pointer
 * @param y		 : y coordinate of mouse pointer
 */
void drawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y)
{
		//if in line-drawing mode
		if(seg){
			// mouse button pushed down
			// - clear context
			// - set origin of new line
			// - set XOR mode for rubber-banding
			// - draw new line in XOR mode.  Note, at this point, the line is
			//   degenerate (0 length), but need to do it for consistency
			x0 = x1 = x;
			y0 = y1 = y;
			gc->setMode(GraphicsContext::MODE_XOR);
			gc->drawLine(x0,y0,x1,y1);
			//reset dragging mode
			dragging = true;
		}
		//if in triangle drawing mode
		else if(tri){
			//if the first verte has not been decided
			if(tVert == 0){
				xOrg = x0 = x1 = x;
				yOrg = y0 = y1 = y;
				gc->setMode(GraphicsContext::MODE_XOR);
				gc->drawLine(x0, y0, x1, y1);
				//turn dragging mode on
				dragging = true;
				//first vertex assigned
				tVert++;
			}
			//if the second vertex has not ben decided
			else if(tVert == 1){
				// undraw old line
				gc->drawLine(x0,y0,x1,y1);
				// just in x and y here do not match x and y of last mouse move
				xVert2 = x1 = x;
				yVert2 = y1 = y;
				// go back to COPY mode
				gc->setMode(GraphicsContext::MODE_NORMAL);
				// new line drawn in copy mode
				gc->drawLine(x0,y0,x1,y1);
				x0 = x1 = x;
				y0 = y1 = y;
				gc->setMode(GraphicsContext::MODE_XOR);
				gc->drawLine(x0, y0, x1, y1);
				if(x1!=xVert2&&y1!=yVert2){
						gc->drawLine(x1, y1, xOrg, yOrg);
				}
				//second vertex assigned
				tVert++;
			}
			//if the third vertex is not decided
			else if(tVert == 2){
				// undraw old line
				gc->drawLine(x1, y1, xOrg, yOrg);
				gc->drawLine(x0,y0,x1,y1);
				// just in x and y here do not match x and y of last mouse move
				xVert3 = x1 = x;
				yVert3 = y1 = y;
				// go back to COPY mode
				gc->setMode(GraphicsContext::MODE_NORMAL);
				// new line drawn in copy mode
				gc->drawLine(x0,y0,x1,y1);
				gc->drawLine(x1, y1, xOrg, yOrg);
				//reset to no vertices
				tVert = 0;
				//reset dragging
				dragging = false;
				//ad triangle to image
				triangle t1(xOrg, yOrg, RED, GREEN, BLUE, xVert2, yVert2, xVert3, yVert3, vc);
				picture.add(&t1);
			}
		}
		//assume pixel if other state somehow reached
		else{
			gc->setPixel(x, y);
			//add pixel to image
			point p1(x, y, RED, GREEN, BLUE, vc);
			//std::cout << x << ", " << y << std::endl;
			picture.add(&p1);
		}
}

/**
 * event that is activated upon the mouse being released
 * @param gc     : graphics context object that may be affected
 * @param button : mouse button that was pressed
 * @param x		 : x coordinate of mouse pointer
 * @param y		 : y coordinate of mouse pointer
 */
void drawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
	//if currently drawing a line
	if(dragging /*&& tState != 'x'*/)
	{
		//as long in line state
		if(seg){
			// undraw old line
			gc->drawLine(x0,y0,x1,y1);
			// just in x and y here do not match x and y of last mouse move
			x1 = x;
			y1 = y;
			// go back to COPY mode
			gc->setMode(GraphicsContext::MODE_NORMAL);
			// new line drawn in copy mode
			gc->drawLine(x0,y0,x1,y1);
			// clear flag
			dragging = false;
			// add line to image
			line l1(x0, y0, RED, GREEN, BLUE, x1, y1, vc);
			//std::cout << l1 << std::endl;
			picture.add(&l1);
		}
	}
return;
}

/**
 * event that is activated upon the mouse being moved
 * @param gc : graphics context object that may be affected
 * @param x  : x coordinate of mouse pointer
 * @param y  : y coordinate of mouse pointer
 */
void drawing::mouseMove(GraphicsContext* gc, int x, int y)
{
	//as long as the mouse is dragging the line
	if(dragging /*&& tState != 'x'*/)
	{
		//if in line-drawing mode
		if(seg){
			// mouse moved - "undraw" old line, then re-draw in new position
			// will already be in XOR mode if dragging
			// old line undrawn
			gc->drawLine(x0,y0,x1,y1);
			// update
			x1 = x;
			y1 = y;
			// new line drawn
			gc->drawLine(x0,y0,x1,y1);
		}
		//if in triangle-drawing mode
		else if(tri){
			//if second vertex has been decided
			// this is a special check that allows both end lines to be drawn
			if(tVert == 2){
				gc->drawLine(x0, y0, x1, y1);
				//this check prevents XORing the defined bas line
				if(x1!=xVert2&&y1!=yVert2)
				{
					gc->drawLine(x1, y1, xOrg, yOrg);
				}
				x1 = x;
				y1 = y;
				gc->drawLine(x0, y0, x1, y1);
				if(x1!=xVert2&&y1!=yVert2){
					gc->drawLine(x1, y1, xOrg, yOrg);
				}
			}
			else{
				gc->drawLine(x0, y0, x1, y1);
				x1 = x;
				y1 = y;
				gc->drawLine(x0, y0, x1, y1);
			}
		}
	}
return;
}

/**
 * this is a helper method to decode the current context color to R, G, and B values
 * @param color
 */
void drawing::decodeColor(unsigned int color){
	RED = (color >> 16) & 0xFF;
	GREEN = (color >> 8) & 0xFF;
	BLUE = color & 0xFF;
}

