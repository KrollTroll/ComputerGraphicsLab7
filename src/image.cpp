/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to an image object
 * 		The image can store and draw shapes
 */

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "image.h"
#include "shape.h"
#include "triangle.h"

using namespace std;

/**
 * default constructor
 */
image::image(){
	shapes.clear();
}

/**
 * copy constructor
 * @param from : image to copy from
 */
image::image(const image& from){
	shapes.clear();
	//deep copy each element
	for(int i = 0; i < (int)from.shapes.size(); i++){
		shapes.push_back(&from.shapes[i]->clone());
	}
}

/**
 * destructor
 */
image::~image(){
	//delete each shape
	for(int i = 0; i < (int)shapes.size(); i++){
				delete(shapes[i]);
	}

	//clear the matrix
	shapes.clear();
};

void import(string fileName){}

/**
 * assignment operator
 * @param from : image ot copy from
 * @return     : address of the returned image
 */
image& image::operator=(const image& from){
	//delete each member of the vector
	for(int i = 0; i < (int)shapes.size(); i++){
		delete(shapes[i]);
	}
	//clear the vector
	shapes.clear();

	//deep copy new members onto the vector
	for(int i = 0; i < (int)shapes.size(); i++){
		shapes.push_back(&from.shapes[i]->clone());
	}

	return *this;
};

/**
 * add a shape to an image
 * @param s : pointer to shape to add
 */
void image::add(shape* s){
	//add an allocated clone to the vector
	shapes.push_back(&(s->clone()));
}

/**
 * draw the shapes in an image
 * @param gc : target graphics context interface
 */
void image::draw(GraphicsContext* gc){
	//draw each member of the vector
	for(int i = 0; i < (int)shapes.size(); i++){
		shapes[i]->draw(gc);
	}
}

/**
 * draw an image using a viewcontext to convert
 * @param gc : graphicscontext interface
 * @param vc : viewcontext for conversion
 */
void image::draw(GraphicsContext* gc, viewcontext* vc){
	//draw each member of the vector
	for(int i = 0; i < (int)shapes.size(); i++){
		shapes[i]->draw(gc, vc);
	}
	gc->setColor(GraphicsContext::GREEN);
}

/**
 * print out the image to a target output
 * @param os : the target output stream
 * @return   : address of the same output stream
 */
std::ostream& image::out(std::ostream& os) const{
	for(int i = 0; i < (int)shapes.size(); i++){
		shapes[i]->out(os);
	}
	return os;
}

/**
 * erase the shapes in the image
 */
void image::erase(){
	for(int i = 0; i < (int)shapes.size(); i++){
			delete(shapes[i]);
	}
	shapes.clear();
}

/**
 * over-written global operator for output
 * @param os  : target output stream
 * @param rhs : object to output
 * @return    : address of the same output stream
 */
std::ostream& operator<<(std::ostream& os, const image& rhs){
	rhs.out(os);
	return os;
}
