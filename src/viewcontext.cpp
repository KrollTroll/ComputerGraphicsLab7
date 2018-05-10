/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to the viewcontext class
 */
#include "viewcontext.h"
#include <math.h>

/**
 * General Constructor
 */
viewcontext::viewcontext():transFWD(4,4), transBWD(4,4), homo(4,4), invHomo(4,4){
	//initalize necessary matrices to be identities
	for(int i = 0; i < 4; i++){
		transFWD[i][i] = 1;
		transBWD[i][i] = 1;
		homo[i][i] = 1;
		invHomo[i][i] = 1;
	}

	//set x transformations
	transFWD[0][3] =  -400;
	transBWD[0][3] = 400;
	//set y transformations
	transFWD[1][3] = 300;
	transBWD[1][3] = 300;
	//flip y
	transFWD[1][1] = -1;
	transBWD[1][1] = -1;
}

/**
 * Destructor
 */
viewcontext::~viewcontext(){}

/**
 * increment or decrement x position based on input
 * @param sign : decrement if -, increment if +
 */
void viewcontext::changeX(char sign){
	//need two dummy matrices for inverse and forward operations
	matrix dummy = matrix::identity(4);
	matrix dummyInv = matrix::identity(4);
	int xlate = 0;
	//assign xlate
	if(sign == '-'){
		xlate = -20;
	}
	else{
		xlate = 20;
	}
	//set necessary matrix values
	dummy[0][3] = xlate;
	dummyInv[0][3] = -xlate;
	//operate on homogenous and inver homogenous matrices
	homo = dummy * homo;
	invHomo = invHomo * dummyInv;

}

/**
 * increment or decrement y position based on input
 * @param sign : decrement if -, increment if +
 */
void viewcontext::changeY(char sign){
	//need two dummy matrices for inverse and forward operations
	matrix dummy = matrix::identity(4);
	matrix dummyInv = matrix::identity(4);
	int ylate = 0;
	//assign increment/decrement based on sign
	if(sign == '-'){
		ylate = -20;
	}
	else{
		ylate = 20;
	}
	//assign necessary values in dummy matrices
	dummy[1][3] = ylate;
	dummyInv[1][3] = -ylate;
	//operate on homogenous and inverse homogenous matrices
	homo = dummy * homo;
	invHomo = invHomo * dummyInv;
}

/**
 * increment or decrement angle of rotation based on input
 * @param sign : decrement if -, increment if +
 */
void viewcontext::changeDeg(char sign){
	matrix dummy = matrix::identity(4);
	matrix dummyInv = matrix::identity(4);
	float deg = 0.0;
	if(sign == '-'){
		deg = -10.0 * M_PI/180.0;
	}
	else{
		deg = 10.0 * M_PI/180.0;
	}
	//assign rotations values to homogenous matrix
	dummy[0][0] =  cos(deg);
	dummy[0][1] = -sin(deg);
	dummy[1][0] =  sin(deg);
	dummy[1][1] =  cos(deg);
	//assign opposite rotation values to inverse homogenous matrix
	dummyInv[0][0] =  cos(-deg);
	dummyInv[0][1] = -sin(-deg);
	dummyInv[1][0] =  sin(-deg);
	dummyInv[1][1] =  cos(-deg);

	//do forward  and invers operations on homogenous and inverse matrices
	homo = dummy * homo;
	invHomo = invHomo * dummyInv;
}

/**
 * scale up or down based on input
 * @param sign : scale by .5 if -, scale by 2 if +
 */
void viewcontext::scale(char sign){
	matrix dummy = matrix::identity(4);
	matrix dummyInv = matrix::identity(4);
	//default scale factor is 1 just in case
	double scaleFact = 1;
	//assign scale factor according to input
	if(sign == '-'){
		scaleFact = .5;
	}
	else{
		scaleFact = 2;
	}
	for(int i = 0; i < 2; i++){
		//asign forward scale factor
		dummy[i][i] = scaleFact;
		//assign inverse scale factor
		dummyInv[i][i] = 1/scaleFact;
	}
	//perform forward and inverse operations on homogenous matrices
	homo = dummy * homo;
	invHomo = invHomo * dummyInv;
}

/**
 * converts the matrix from display mode to model mode
 * @param oldMat : matrix in display mode
 * @return 		 : new matrix in model mode
 */
matrix viewcontext::convertToWindow(const matrix oldMat){
	return transBWD*homo*oldMat;
}

/**
 * converts the matrix from model mode to display mode
 * @param oldMat : matrix in model mode
 * @return		 : new matrix in display mode
 */
matrix viewcontext::convertToImage(const matrix oldMat){
	return invHomo*transFWD*oldMat;
}

/**
 * revert displayed image to non-transformed state
 */
void viewcontext::undo(){
	homo = matrix::identity(4);
	invHomo = matrix::identity(4);
}
