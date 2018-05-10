#include "matrix.h"
#include <string>
#include <cmath>
#include <iostream>

/**
 * Connor Kroll
 * Lab 2 - Computer Graphics
 *
 * This project supplies functionality for a matrix class and operators
 */

/**
 * This is the "standard" prioritized constructor
 * @param rows : number of rows in a matrix
 * @param cols : number of columns in a matrix
 */
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	//throw exception if matrix too small
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	}
	else{
		//set array size
		int size = rows*cols;
		//following the one array method - makes things easier in the long run
		the_matrix = new double[size];
		//initialize array to 0
		for(int i = 0; i < size; i++){
			the_matrix[i] = 0;
		}
	}
}

/**
 * copy constructor
 * @param from : matrix to copy the new one from
 */
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	int size = rows*cols;
	//create array
	the_matrix = new double[size];
	//copy over
	for(int i = 0; i < size; i++){
		the_matrix[i] = (from.the_matrix)[i];
	}
}

/**
 * destructor
 */
matrix::~matrix()
{
	if(the_matrix != NULL){
		//ha. delete the matrix. ha.
		delete []the_matrix;
	}
}

/**
 * assignment operator -- makes one matrix a copy of another
 * @param rhs : the right hand side matrix to copy
 * @return    : the new array copied over
 */
matrix& matrix::operator=(const matrix& rhs)
{
	if(this->the_matrix != NULL){
		//delete
		delete []the_matrix;
	}
	//reset size
	rows = rhs.rows;
	cols = rhs.cols;
	int size = rows*cols;
	the_matrix = new double[size];
	//copy
	for(int i = 0; i < size; i++){
		the_matrix[i] = rhs.the_matrix[i];
	}
	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	//throw exception if size is too small
	if(size < 1){
		throw matrixException("identity constructor bad argument");
	}
	else{
		//make empty array
		matrix ident(size, size);
		int side = size;
		//iterate through and assign ones on the diagonal
		for(int i = 0; i < side; i++){
			ident[i][i] = 1;
		}
		return ident;
	}
}


/**
 * binary operator -- adds two marices together
 * @param rhs : right hand side matrix to add to the left
 * @return    : the new combined matrix
 */
matrix matrix::operator+(const matrix& rhs) const
{
	//throw exception if matrices are no the same size
	if(cols != rhs.cols || rows!= rhs.rows){
		throw matrixException("addition matrix sizes different!");
	}
	//do linear add operation if they are
	else{
		matrix retVal(rhs);
		int size = rhs.cols * rhs.rows;
		for(int i = 0; i < size; i++){
			(retVal.the_matrix)[i] = (retVal.the_matrix)[i] + (the_matrix)[i];
		}
		return retVal;
	}
}

/**
 * multiplication operator -- matrix by matrix, multiplies two matrices together
 * 		throws exception if the two matrices are not compatible
 * @param rhs : right hand matrix to multiply left by
 * @return    : the new product matrix
 */
matrix matrix::operator*(const matrix& rhs) const
{
	//throw exception if the matrices are incompatible
	if(cols != rhs.rows){
		throw matrixException("left matrix and right matrix not compatible!");
	}
	else{
		int rows_lhs = rows;
		//int rows_rhs = rhs.rows;
		int cols_lhs = cols;
		int cols_rhs = rhs.cols;
		matrix product(rows_lhs, cols_rhs);
		//perform multiplication
		//for each row in the right-hand matrix
		for(int i = 0; i < rows_lhs; i++){
			//iterate through each column in the right-hand matrix
			for(int j = 0; j < cols_rhs; j++){
				//iterate through each column in the left-hand matrix
				for(int k = 0; k < cols_lhs; k++){
					//assign the new matrix the values of each product added together
					product[i][j] += (((*this)[i][k])*(rhs[k][j]));
				}
			}
		}
		return product;
	}
}

/**
 * multiplication operator -- matrix by scalar, multiplies a matrix by a scalar
 * @param scale : scalar to multiply matrix by
 * @return		: the new product matrix
 */
matrix matrix::operator*(const double scale) const
{
	matrix retVal(*this);
	int pos = rows*cols;
	//linear multiplication -- multiply each array index by scalar
	for(int i = 0; i < pos; i++){
		retVal.the_matrix[i] *= scale;
	}
	return retVal;
}


/**
 * unary operator -- transposes a given matrix
 * @return : the new transposed matrix
 */
matrix matrix::operator~() const
		{
	//clone target
	matrix dupe(*this);
	//create new matrix with opposite measurements
	matrix retVal(cols, rows);
	int row = rows;
	int col = cols;

	//iterate through the rows
	for(int i = 0; i < row; i++){
		//iterate through the columns
		for(int j = 0; j < col; j++){
			//swap values
			retVal[j][i]=dupe[i][j];
		}
	}
	return retVal;
}

/**
 * clears a matrix and assigns all values to 0
 */
void matrix::clear()
{
	int size = rows*cols;
	//iterate through the array and assign each index 0
	for(int i = 0; i < size; i++){
		the_matrix[i] = 0;
	}
	return;
}

/**
 * operator to return the pointer to the first element of specified row
 * @param row : specified row
 * @return
 */
double* matrix::operator[](unsigned int row)
{
	//throw exception if out of bounds
	if(row > this->rows){
		throw matrixException("[] argument invalid");
	}
	//return pointer to first member of that row
	else{
		return &(the_matrix[(row)*cols]);
	}
}

/**
 * same as other [] op, but const for other const methods
 * @param row : specified row
 * @return
 */
double* matrix::operator[](unsigned int row) const
{
	//throw exception if out of bounds
	if(row > this->rows){
		throw matrixException("[] argument invalid");
	}
	//return pointer to the first member of that row
	else{
		return &(the_matrix[(row)*cols]);
	}
}

/**
 * This is the true print operator, it does the work
 */
std::ostream& matrix::out(std::ostream& os) const
{
	int col = cols;
	int row = rows;
	int pos = 0;

	//for each row
	for(int i = 0; i < row; i++){
		//print out start bracket
		os << "\t[";
		//print each matrix location
		for(int j = 0; j < col; j++){
			os << "\t" << the_matrix[pos] << "\t";
			pos++;
		}
		//print closing bracket
		os << "]\n";
	}
	return os;	
}



/**
 * This is basically the print operator, just make it look pretty and you should be gucci
 * @param os
 * @param rhs
 * @return
 */
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	//call output method
	rhs.out(os);
	return os;
}

/**
 * global scalar function
 * @param scale
 * @param rhs
 * @return
 */
matrix operator*(const double scale, const matrix& rhs)
{
	//do basic scalar multiplication
	matrix retval(rhs);
	return (retval*scale);
}


