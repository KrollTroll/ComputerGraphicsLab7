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
#include "point.h"
#include "line.h"
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
 * reads in shapes from a text file
 * @param in : input stream to read from
 */
void image::in(std::ifstream& in){
		//Print error if file does not open for whatever reason
		if(!in){
			cerr << "\n**Unable to open file " << endl;
			cout << "**\n**File may be missing, incorrect format, or corrupted**\n\n";
		}
		//If the file is valid
		else{
			string holder;
			//as long as there is more in the file
			while(getline(in, holder)){
				//if entering a shape
				if(!holder.compare("START TRIANGLE")){
					triangle dummyT(0,0,0,0,0,0,0,0,0);
					dummyT.in(in);
					this->add(&dummyT);
				}
				if(!holder.compare("START LINE")){
					line dummyL(0,0,0,0,0,0,0);
					dummyL.in(in);
					this->add(&dummyL);
				}
				if(!holder.compare("START POINT")){
					point dummyP(0,0,0,0,0);
					dummyP.in(in);
					this->add(&dummyP);
				}
			}
		}
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
