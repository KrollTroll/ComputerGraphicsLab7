/*
 * STLReader.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: ckroll
 *
 *      This is a lab for computer graphics that parses STL files
 */

#include "STLReader.h"
using namespace std;

int total = 0;

bool initialized = false;
bool validFile = false;

//TODO: figure out how to handle color
STLReader::STLReader(image& picture){
	x0 = y0 = z0 = x1 = y1 = z1 = x2 = y2 = z2 = 0;
	myPicture = picture;
}

/**
 * This function parses through an input file and calls printAndCheck
 * @param inFile : the file to be parsed in a string format
 */
void STLReader::parseFile(string inFile){
	int vertT = 0;
	ifstream myFile;
	myFile.open(inFile);

	//Print error if file does not open for whatever reason
	if(!myFile){
		cerr << "\n**Unable to open file " << inFile;
		cout << "**\n**File may be missing, incorrect format, or corrupted**\n\n";
		validFile = false;
	}
	//If the file is valid
	else{
		//boolean switch for later logic
		validFile = true;

		string holder;
		bool vertComplete = false;

		//as long as there is more in the file
		while(getline(myFile, holder, ' ')){
			//if entering an outer loop
			if(!holder.compare("outer")){
				//increment the total number of facets
				total++;
			}
			//if entering a vertex range
			if(!holder.compare("vertex")){
				string vertX;
				getline(myFile, vertX, ' ');
				while(!vertX.compare("")){
					getline(myFile, vertX, ' ');
				}

				//check vertices, modify appropriate value
				if(vertT == 0){
					x0 = stof(vertX);
				}
				else if(vertT == 1){
					x1 = stof(vertX);
				}
				else if(vertT == 2){
					x2 = stof(vertX);
				}

				string vertY;
				getline(myFile, vertY, ' ');
				while(!vertY.compare("")){
					getline(myFile, vertY, ' ');
				}

				//check vertices, modify appropriate value
				if(vertT == 0){
					y0 = stof(vertX);
				}
				else if(vertT == 1){
					y1 = stof(vertX);
				}
				else if(vertT == 2){
					y2 = stof(vertX);
				}

				string vertZ;
				getline(myFile, vertZ, ' ');
				while(!vertZ.compare("")){
					getline(myFile, vertZ, ' ');
				}

				//check vertices, modify appropriate value
				if(vertT == 0){
					z0 = stof(vertX);
				}
				else if(vertT == 1){
					z1 = stof(vertX);
				}
				else if(vertT == 2){
					z2 = stof(vertX);
				}

				//it's screwing up here, this is causing it to only print every third
				vertT++;
				vertComplete = true;

			}

			//mod t1 when 3 vertices are found
			if(vertComplete){
				//if on the third vertex of a triangle
				if(vertT == 3){
					triangle t1(x0, y0, 0, 255, 0, x1, y1, x2, y2);
					myPicture.add(&t1);
					vertT = 0;
				}
			}
		}

		//close file to save memory
		myFile.close();
	}
}




