/**
 * Connor Kroll
 * Graphics
 *
 * This file implements prototypes for the point object
 */

#ifndef POINT_H_
#define POINT_H_

#include "shape.h"

class point : public shape{
public:

	/**
	 * Constructor for a point object
	 * @param x : x coordinate of point
	 * @param y : y coordinate of point
	 * @param R : red color value for point
	 * @param G : green color value for point
	 * @param B : blue color value for point
	 */
	point(float x, float y, int R, int G, int B);

	/**
	 * constructor for point object utilizing a viewcontext
	 * 	allows easy conversion of model/image using VD
	 * @param x  : x coordinate of point
	 * @param y  : y coordinate of point
	 * @param R  : red color value for point
	 * @param G  : green color value for point
	 * @param B  : blue color value for point
	 * @param vc : viewcontext for model/display conversion
	 */
	point(float x, float y, int R, int G, int B, viewcontext* vc);

	/**
	 * copy constructor for point
	 * @param from : object to copy
	 */
	point(const point& from);

	/**
	 * destructor - doesn't do much
	 */
	~point();

	/**
	 * draws the point
	 * @param GC : graphicscontext interface to draw to
	 */
	void draw(GraphicsContext* GC);

	/**
	 * draws a point utilizing a viewcontext object for conversion
	 * @param GC : graphicscontext interface to draw to
	 * @param vc : viewcontext for image/display converison
	 */
	void draw(GraphicsContext* GC, viewcontext* vc);

	/**
	 * assignment operator
	 * @param from : object to assign from
	 * @return     : address of newly assigned object
	 */
	point& operator=(const point& from);

	/**
	 * copies a point to another location in memory
	 * @return : address of newly allocated point
	 */
	point& clone();

	/**
	 * outputs data from point to an os stream
	 * @param os : os stream to output to
	 * @return   : address of that same stream
	 */
	std::ostream& out(std::ostream& os) const;

	/**
	 * scan a single point from a file
	 * @param in : istream to scan from
	 */
	void in(std::istream& in);
};

/**
 * over-written global operator to print point data
 * @param os  : os stream to print to
 * @param rhs : point to output
 * @return    : adress of the same os stream
 */
std::ostream& operator<<(std::ostream& os, const point& rhs);

#endif
