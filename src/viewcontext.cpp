/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to the viewcontext class
 */
#include "viewcontext.h"
#include <math.h>

using namespace std;

/**
 * General Constructor
 */
viewcontext::viewcontext():dTp(4,4), pTv(4,4), vTm(4,4), homo(4,4), threeDHomo(4,4){
	//initalize necessary matrices to be identities
	for(int i = 0; i < 4; i++){
		dTp[i][i] = 1;
		pTv[i][i] = 1;
		vTm[i][i] = 1;
		homo[i][i] = 1;
		threeDHomo[i][i] = 1;
	}

	//set x transformations
	dTp[0][3] = 400;
	//set y transformations
	dTp[1][3] = 300;
	//flip y
	dTp[1][1] = -1;

	//cout << dTp << endl;

	Zf = 60.0;

	pTv[2][2] = 0;
	pTv[3][2] = -1.0/Zf;

	//cout << pTv << endl;


	vTm[0][0] = 2/sqrt(5);
	vTm[0][2] = -1/sqrt(5);
	vTm[1][0] = -2/(3*sqrt(5));
	vTm[1][1] = 5/(3*sqrt(5));
	vTm[1][2] = -4/(3*sqrt(5));
	vTm[2][0] = 1.0/3.0;
	vTm[2][1] = 2.0/3.0;
	vTm[2][2] = 2.0/3.0;
	vTm[2][3] = -60.0;

	//cout << vTm << endl;
	beta = 26.565 * M_PI/180.0;
	theta = 0.0;

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
	//operate on homogenous and inver homogenous matrices
	homo = dummy * homo;
}

/**
 * increment or decrement y position based on input
 * @param sign : decrement if -, increment if +
 */
void viewcontext::changeY(char sign){
	//need two dummy matrices for inverse and forward operations
	matrix dummy = matrix::identity(4);
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
	//operate on homogenous and inverse homogenous matrices
	homo = dummy * homo;
}

/**
 * increment or decrement angle of rotation based on input
 * @param sign : decrement if -, increment if +
 */
void viewcontext::changeDegY(char sign){
	matrix dummy = matrix::identity(4);
	float deg = 0.0;
	if(sign == '-'){
		deg = -10.0 * M_PI/180.0;
	}
	else{
		deg = 10.0 * M_PI/180.0;
	}
	theta += deg;
	//assign rotations values to homogenous matrix
	dummy[0][0] =  cos(deg);
	dummy[0][2] =  sin(deg);
	dummy[2][0] = -sin(deg);
	dummy[2][2] =  cos(deg);
	//cout << dummy << endl;

	//do forward  and invers operations on homogenous and inverse matrices
	threeDHomo = dummy * threeDHomo;
}

void viewcontext::changeDegHor(char sign){
	matrix dummy1 = matrix::identity(4);
	matrix dummy2 = matrix::identity(4);
	matrix dummy3 = matrix::identity(4);

	float deg = 0.0;
	if(sign == '-'){
		deg = -10.0 * M_PI/180.0;
	}
	else{
		deg = 10.0 * M_PI/180.0;
	} 

	//assign horizontal transform matrix 1
	dummy1[0][0] =  cos(beta + theta);
	dummy1[0][2] = -sin(beta + theta);
	dummy1[2][0] =  sin(beta + theta);
	dummy1[2][2] =  cos(beta + theta);

	//assign horizontal transform matrix 2
	dummy2[1][1] =  cos(deg);
	dummy2[1][2] = -sin(deg);
	dummy2[2][1] =  sin(deg);
	dummy2[2][2] =  cos(deg);

	//assign horizontal transform matrix 3
	dummy3[0][0] =  cos(beta + theta);
	dummy3[0][2] =  sin(beta + theta);
	dummy3[2][0] = -sin(beta + theta);
	dummy3[2][2] =  cos(beta + theta);

	threeDHomo = dummy3 * dummy2 * dummy1 * threeDHomo;
}

void viewcontext::changeFocus(char sign){
	float foc = 0.0;
	if(sign == '-'){
		foc = -10.0;
	}
	else{
		foc = 10.0;
	}

	if((Zf + foc) <= 20){
		Zf = 20;
	}
	else{
		Zf += foc;
	}
	
	pTv[3][2] = -1.0/Zf;
}

/**
 * scale up or down based on input
 * @param sign : scale by .5 if -, scale by 2 if +
 */
void viewcontext::scale(char sign){
	matrix dummy = matrix::identity(4);
	//default scale factor is 1 just in case
	double scaleFact = 1;
	//assign scale factor according to input
	if(sign == '-'){
		scaleFact = .5;
	}
	else{
		scaleFact = 2;
	}
	for(int i = 0; i < 3; i++){
		//asign forward scale factor
		dummy[i][i] = scaleFact;
	}
	//perform forward and inverse operations on homogenous matrices
	homo = dummy * homo;
}

/**
 * converts the matrix from display mode to model mode
 * @param oldMat : matrix in display mode
 * @return 		 : new matrix in model mode
 */
matrix viewcontext::convert(const matrix oldMat){

	matrix m1 = dTp*homo*pTv*vTm*threeDHomo*oldMat;

	m1[0][0] = m1[0][0]/m1[3][0];
	m1[1][0] = m1[1][0]/m1[3][0];
	m1[3][0] = 1;

	m1[0][1] = m1[0][1]/m1[3][1];
	m1[1][1] = m1[1][1]/m1[3][1];
	m1[3][1] = 1;

	m1[0][2] = m1[0][2]/m1[3][2];
	m1[1][2] = m1[1][2]/m1[3][2];
	m1[3][2] = 1;

	return m1;

}

/**
 * revert displayed image to non-transformed state
 */
void viewcontext::undo(){
	homo	   = matrix::identity(4);
	threeDHomo = matrix::identity(4);
	beta = 0.0;
}
