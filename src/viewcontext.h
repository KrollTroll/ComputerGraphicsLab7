/**
 * Connor Kroll
 * Graphics
 *
 * This header implements prototypes to the viewcontext class
 */

#ifndef VIEWCONTEXT_H_
#define VIEWCONTEXT_H_

#include "matrix.h"

class viewcontext{

public:

/**
 * General Constructor
 */
viewcontext();

/**
 * Destructor
 */
~viewcontext();

/**
 * increment or decrement x position based on input
 * @param sign : decrement if -, increment if +
 */
void changeX(char sign);

/**
 * increment or decrement y position based on input
 * @param sign : decrement if -, increment if +
 */
void changeY(char sign);

/**
 * increment or decrement angle of rotation based on input
 * @param sign : decrement if -, increment if +
 */
void changeDeg(char sign);

/**
 * scale up or down based on input
 * @param sign : scale by .5 if -, scale by 2 if +
 */
void scale(char sign);

/**
 * converts the matrix from display mode to model mode
 * @param oldMat : matrix in display mode
 * @return 		 : new matrix in model mode
 */
matrix convertToImage(const matrix oldMat);

/**
 * converts the matrix from model mode to display mode
 * @param oldMat : matrix in model mode
 * @return		 : new matrix in display mode
 */
matrix convertToWindow(const matrix oldMat);

/**
 * revert displayed image to non-transformed state
 */
void undo();

private:
//trans image to window
matrix transFWD;
//trans window to image
matrix transBWD;
//homogenous matrix
matrix homo;
//inverse homogenous matrix
matrix invHomo;

};
#endif
