/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to a line object
 * 		Lines extend shape and add an endpoint
 */

#include "line.h"

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

	/**
 	 * line consructor
	 * @param x  : start point x coordinate
	 * @param y  : start point y coordinate
	 * @param R  : line red color value
	 * @param G  : line green color value
	 * @param B  : line blue color value
	 * @param x2 : end point x coordinate
	 * @param y2 : end point y coordinate
	 */
	line::line(float x, float y, int R, int G, int B, float x2, float y2)
															:shape(x,y,R,G,B){
		this->x2 = x2;
		this->y2 = y2;
		this->coor[0][1] = x2;
		this->coor[1][1] = y2;
		for(int i = 0; i < 4; i++){
			coor[2][i] = 1;
			coor[3][i] = 1;
		}
	}

	/**
	 * line consructor that utilizes a viewcontext object for conversion
	 * @param x  : start point x coordinate
	 * @param y  : start point y coordinate
	 * @param R  : line red color value
	 * @param G  : line green color value
	 * @param B  : line blue color value
	 * @param x2 : end point x coordinate
	 * @param y2 : end point y coordinate
	 * @param vc : viewcontext object for image/display conversion
	 */
	line::line(float x, float y, int R, int G, int B, float x2, float y2, viewcontext* vc)
																			:shape(x,y,R,G,B){
			//create display matrix
			//assign values not assigned thorugh inheritance
			this->x2 = x2;
			this->y2 = y2;
			coor[0][1] = this->x2;
			coor[1][1] = this->y2;
			//assign unneded values in matrices so multiplication works
			for(int i = 0; i < 4; i++){
					coor[2][i] = 1;
					coor[3][i] = 1;
			}
			//convert display matrix to image matrix
			matrix newCoor = vc->convertToImage(coor);
			coor = newCoor;
			//reassign values as necessary
			shape::x = coor[0][0];
			shape::y = coor[1][0];
			this->x2 = coor[0][1];
			this->y2 = coor[1][1];
	}

	/**
	 * copy constructor for a line
	 * @param from : line to copy from
	 */
	line::line(const line& from):shape(from){
		this->coor[0][1] = this->x2 = from.x2;
		this->coor[1][1] = this->y2 = from.x2;
	}

	/**
	 * Destructor - there is nothing to free
	 */
	line::~line(){}

	/**
	 * draws a line to a garphics context interface
	 * @param GC : target interface
	 */
	void line::draw(GraphicsContext* GC){
		int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
		GC->setColor(color);
		GC->drawLine(coor[0][0], coor[1][0], coor[0][1], coor[1][1]);
	}

	/**
	 * draws a line to the target grapics context inteface using a viewcontext for conversion
	 * @param GC : target garphics context
	 * @param vc : viewcontext object for image/display conversion
	 */
	void line::draw(GraphicsContext* GC, viewcontext* vc){
			//convert points to window format
			matrix drawCoor = vc->convertToWindow(coor);
			int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
			GC->setColor(color);
			GC->drawLine(drawCoor[0][0], drawCoor[1][0], drawCoor[0][1], drawCoor[1][1]);
	}

	/**
	 * assignment operator - sets one line equal to another
	 * @param from : line to assign from
	 * @return     :  address of newly assigned line
	 */
	line& line::operator=(const line& from){
		this->shape::operator=(from);
		this->coor[0][1] = this->x2 = from.x2;
		this->coor[1][1] = this->y2 = from.x2;
		return *this;
	}

	/**
	 * Copies one line into a new location in memory
	 * @return : address of newly allocated copy
	 */
	line& line::clone(){
		return *(new line(x, y, RED, GREEN, BLUE, x2, y2));
	}

	/**
	 * outputs line characteristics to desired output stream
	 * @param os : desired output stream
	 * @return   :  address of that same stream
	 */
	std::ostream& line::out(std::ostream& os) const{
		//std::cout << "OUT COOR : " << shape::x << "," << shape::y << " | " << x2 << "," << y2 << std::endl;
		os << "START LINE" << "\n";
		shape::out(os);
		os << "  " << coor[0][1] << "\n";
		os << "  " << coor[1][1] << "\n";
		os << "END" << endl << endl;

		//std::cout << this->coor[0][1] << " " << this->coor[1][1] << std::endl;
		return os;
	}

	/**
	 * read in a single line from a file
	 * @param in : istream to parse from
	 * @return   : the new triangle object
	 */
	void line::in(std::istream& in) {
		//placeholder string for read in
		string holder;
		//read in data line by line
		getline(in, holder);
		//remove spaces
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		//convert as necessary
		this->coor[0][0] = this->x = stof(holder);
		getline(in, holder);
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		this->coor[1][0] = this->y = stof(holder);
		getline(in, holder);
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		this->RED = stoi(holder);
		getline(in, holder);
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		this->GREEN = stoi(holder);
		getline(in, holder);
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		this->BLUE = stoi(holder);
		getline(in, holder);
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		this->coor[0][1] = this->x2 = stof(holder);
		getline(in, holder);
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		this->coor[1][1] = this->y2 = stof(holder);
	}

	/**
	 * over-written global operator for easy output
	 * @param os  : target output stream
	 * @param rhs : object to output
	 * @return    : address of the same output stream
	 */
	std::ostream& operator<<(std::ostream& os, const line& rhs){
		rhs.out(os);
		return os;
	}
