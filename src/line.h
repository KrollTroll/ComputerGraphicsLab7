/**
 * Connor Kroll
 * Graphics
 *
 * This file implements prototypes for the line object
 */

#ifndef LINE_H
#define LINE_H

#include "shape.h"

class line : public shape{
public:

	/**
	 * line consructor
	 * @param x  : start point x coordinate
	 * @param y  : start point y coordinate
	 * @param R  : line red color value
	 * @param G  : line green color value
	 * @param B  : line blue color value
	 * @param x2 : end point x coordinate
	 * @param y2 : end point y coordinate
	 */
	line(float x, float y, int R, int G, int B, float x2, float y2);

	/**
	 * line consructor that utilizes a viewcontext object for conversion
	 * @param x  : start point x coordinate
	 * @param y  : start point y coordinate
	 * @param R  : line red color value
	 * @param G  : line green color value
	 * @param B  : line blue color value
	 * @param x2 : end point x coordinate
	 * @param y2 : end point y coordinate
	 * @param vc : viewcontext object for image/display conversion
	 */
	line(float x, float y, int R, int G, int B, float x2, float y2,
														viewcontext* vc);

	/**
	 * copy constructor for a line
	 * @param from : line to copy from
	 */
	line(const line& from);

	/**
	 * line destructor
	 */
	~line();

	/**
	 * draws a line to the target grapics context inteface
	 * @param GC : target garphics context
	 */
	void draw(GraphicsContext* GC);

	/**
	 * draws a line to the target grapics context inteface using a viewcontext for conversion
	 * @param GC : target garphics context
	 * @param vc : viewcontext object for image/display conversion
	 */
	void draw(GraphicsContext* GC, viewcontext* vc);

	/**
	 * assignment operator
	 * @param from : object to assign from
	 * @return     : address of the newly assigned line
	 */
	line& operator=(const line& from);

	/**
	 * creates a new copy of a line in memory and returns its address
	 * @return : address of newly copie line
	 */
	line& clone();

	/**
	 * outputs text format of the line to an output stream
	 * @param os : target output stream
	 * @return   : address of the target output stream
	 */
	std::ostream& out(std::ostream& os) const;

	/**
	 * reads in a single line from a file
	 * @param in : the input stream to read from
	 */
	void in(std::istream& in);

private:
	float x2;
	float y2;
};

/**
 * over-written global operator to output to an output stream
 * @param os  : target output stream
 * @param rhs : shape to output
 * @return    : the address of that same output stream
 */
std::ostream& operator<<(std::ostream& os, const line& rhs);

#endif
