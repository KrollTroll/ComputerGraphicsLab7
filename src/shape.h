/**
 * Connor Kroll
 * Graphics
 *
 * This ifle implements prototypes for the shape class
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "gcontext.h"
#include "matrix.h"
#include "viewcontext.h"

#include <iostream>

class shape{

public:

	/**
	 * Generic Consructor
	 * @param R : RED color data
	 * @param G : GREEN color data
	 * @param B : BLUE color data
	 */
	shape(float x, float y, int R, int G, int B);

	/**
	 * copy constructor
	 * @param from : shape to copy from
	 */
	shape(const shape& from);

	/**
	 * Need a virtual destructor
	 */
	virtual ~shape();

	/**
	 * assignment operator
	 * @param rhs : shape o assign from
	 * @return    : address of newly assigned shape
	 */
	virtual shape& operator=(const shape& rhs);

	/**
	 * draw the shape
	 */
	virtual void draw(GraphicsContext* GC) = 0;

	/**
	 * modified shape drawing to account for viewcontext conversion
	 * @param GC : target graphicscontext interface
	 * @param vc : viewcontext object for conversion
	 */
	virtual void draw(GraphicsContext* GC, viewcontext* vc) = 0;

	/**
	 * print the shape out to a terminal
	 */
	virtual std::ostream& out(std::ostream& os) const = 0;

	/**
	 * read the shape in from a file
	 */
	virtual void in(std::istream& in) = 0;

	/**
	 * clone the shape onto another
	 */
	virtual shape& clone() = 0;

protected:
	float x;
	float y;
	matrix coor;
	//color variables
	int RED;
	int GREEN;
	int BLUE;
};

/**
 * This is a global operator for output
 * @param os  : target output stream
 * @param rhs : shape to output
 * @return    : the same output stream
 */
std::ostream& operator<<(std::ostream& os, const shape& rhs);

#endif
