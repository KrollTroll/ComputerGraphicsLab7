/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to the abstract shape object
 * 		It contains a point, as well as RGB data
 */

#include "shape.h"
#include "matrix.h"

/**
 * Generic constructor
 * @param ORG : origin point matrix
 * @param R   : RED data
 * @param G   : GREEN data
 * @param B   : BLUE data
 */
shape::shape(float x, float y, int R, int G, int B):x(x), y(y), coor(4,4), RED(R),GREEN(G),BLUE(B){
	coor[0][0] = x;
	coor[1][0] = y;

	for(int i = 0; i < 4; i++){
		coor[2][i] = 1;
		coor[3][i] = 1;
	}
}

/**
 * Copy constructor
 * @param from : shape to copy information over from
 */
shape::shape(const shape& from):x(from.x),y(from.y), coor(3,3),
		RED(from.RED),GREEN(from.GREEN),BLUE(from.BLUE){
	coor[0][0] = x;
	coor[1][0] = y;

	for(int i = 0; i < 4; i++){
			coor[2][i] = 1;
			coor[3][i] = 1;
	}
}

/**
 * Destructor - does nothing
 * 	Ensures that things work down the line
 * 	Nothing to do here
 */
shape::~shape(){}

/**
 * Assignment operator
 * @param rhs
 * @return
 */
shape& shape::operator=(const shape& rhs){
	coor[0][0] = x = rhs.x;
	coor[1][0] = y = rhs.y;
	RED = rhs.RED;
	GREEN = rhs.GREEN;
	BLUE = rhs.BLUE;
	return *this;
}

/**
 * Outputs in desired format to the output stream
 * @param os : the os stream to output to
 * @return   : the same os stream
 */
std::ostream& shape::out(std::ostream& os) const{
	os << "  " << coor[0][0] << "\n";
	os << "  " << coor[1][0] << "\n";
	os << "  " << RED << "\n";
	os << "  " << GREEN << "\n";
	os << "  " << BLUE << "\n";
	return os;
}

/**
 * Operator to create terminal output
 * @param os  : output stream to send things to
 * @param rhs : shape to output
 * @return    : the same output stream
 */
std::ostream& operator<<(std::ostream& os, const shape& rhs){
	rhs.out(os);
	return os;
}





