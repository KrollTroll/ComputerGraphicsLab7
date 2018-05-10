/*
 * STLReader.h
 *
 *  Created on: May 9, 2018
 *      Author: ckroll
 */

#ifndef STLREADER_H_
#define STLREADER_H_

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "image.h"
#include "triangle.h"

using namespace std;

class STLReader{

public:
	/**
	 * Constructor
	 */
	STLReader(image& picture);

	/**
	 * Destructor
	 */
	~STLReader();

	/**
	 * Method to parse through an STL file
	 * @param inFile : file to parse through
	 */
	void parseFile(string inFile);

private:
	float x0, y0, z0, x1, y1, z1, x2, y2, z2;
	image myPicture;

};



#endif /* STLREADER_H_ */
