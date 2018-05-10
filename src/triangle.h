/**
 * Connor Kroll
 * Graphics
 *
 * This file implements prototypes for the triangle object
 */
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class triangle : public shape{
public:

	/**
	 * basic triangle constructor
	 * @param x  : origin x coordinate
	 * @param y  : origin y coordinate
	 * @param R  : RED value
	 * @param G  : GREEN value
	 * @param B  : BLUE value
	 * @param x2 : second point x coordinate
	 * @param y2 : second point y coordinate
	 * @param x3 : third point x coordinate
	 * @param y3 : third point y coordinate
	 */
	triangle(float x, float y, int R, int G, int B, float x2, float y2, float x3, float y3);

	/**
	 * basic triangle constructor with added viewcontext for conversions
	 * @param x  : origin x coordinate
	 * @param y  : origin y coordinate
	 * @param R  : RED value
	 * @param G  : GREEN value
	 * @param B  : BLUE value
	 * @param x2 : second point x coordinate
	 * @param y2 : second point y coordinate
	 * @param x3 : third point x coordinate
	 * @param y3 : third point y coordinate
	 * @param vc : viewcontext for image/display conversions
	 */
	triangle(float x, float y, int R, int G, int B, float x2, float y2, float x3, float y3, viewcontext* vc);

	/**
	 * copy constructor
	 * @param from : triangle to copy data from
	 */
	triangle(const triangle& from);

	/**
	 * destructor
	 */
	~triangle();

	/**
	 * draws a triangle to a target graphics context interface
	 * @param GC : target interface
	 */
	void draw(GraphicsContext* GC);

	/**
	 * draw method with added viewcontext for conversion
	 * @param GC : graphicscontext interface to draw to
	 * @param vc : viewcontext for image/display conversion
	 */
	void draw(GraphicsContext* GC, viewcontext* vc);

	/**
	 * assignment operator - assigns one triangle the data of another
	 * @param from : triangle to assign from
	 * @return     : address of the triangle assigned to
	 */
	triangle& operator=(const triangle& from);

	/**
	 * copies a triangle into a different location in memory
	 * @return : address of newly allocated triangle
	 */
	triangle& clone();

	/**
	 * outputs data from the triangle to the desired output stream
	 * @param os : desired output stream
	 * @return   : address of that same stream
	 */
	std::ostream& out(std::ostream& os) const;

	/**
	 * reads in a single triangle from an input stream
	 * @param in : desired input stream
	 */
	void in(std::istream& in);

protected:
	float x2;
	float y2;
	float x3;
	float y3;
};

/**
 * over-written global operator for easy output
 * @param os  : desired output stream
 * @param rhs : object to output
 * @return    : address of the output stream
 */
std::ostream& operator<<(std::ostream& os, const triangle& rhs);

#endif
