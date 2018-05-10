/**
 * Connor Kroll
 * Graphics
 *
 * This header implements prototypes for the image class
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "shape.h"
#include <vector>

class image{
public:

	/**
	 * blank constructor
	 */
	image();

	/**
	 * copy constructor
	 * @param from
	 */
	image(const image& from);

	/**
	 * destructor
	 */
	~image();

	/**
	 * assignment operator
	 * @param rhs : image to assign from
	 * @return    : address of newly assigned image
	 */
	image& operator=(const image& rhs);

	/**
	 * add a shape to the image
	 * @param s : shape to add
	 */
	void add(shape* s);

	/**
	 * draw an image
	 * @param gc : target graphics context interface
	 */
	void draw(GraphicsContext* gc);

	/**
	 * draw an image using a viewcontext to convert
	 * @param gc : graphicscontext interface
	 * @param vc : viewcontext for conversion
	 */
	void draw(GraphicsContext* gc, viewcontext* vc);

	/**
	 * print output to output stream
	 * @param os : target stream
	 * @return   : address of same stream
	 */
	std::ostream& out(std::ostream& os) const;

	/**
	 * reads in shapes from a file
	 * @param in : input stream to read from
	 */
	void in(std::ifstream& in);

	/**
	 * erase shape members of an image
	 */
	void erase();


private:
	//vector to store images
	std::vector<shape*> shapes;
};

/**
 * over-written global operator for output
 * @param os : target output stream
 * @return   : address of the same stream
 */
std::ostream& operator<<(std::ostream& os, const image& rhs);

#endif
