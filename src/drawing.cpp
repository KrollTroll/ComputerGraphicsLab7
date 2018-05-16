#include "drawing.h"
#include "gcontext.h"

#include <iostream>
#include <fstream>

/**
 * constructor
 */
drawing::drawing()
{
	//initalize variables
	dragging = false;

	dot = true;
	seg = false;
	tri = false;

	x0 = y0 = z0 = x1 = y1 = z1 = x2 = y2 = z2 = 0;
	RED = GREEN = BLUE = 0;
	vc = new viewcontext();
	tState = 'x';

	parseFile("word.stl", picture);
	
	return;
}

/**
 * destructor
 */
drawing::~drawing(){
	delete vc;
}

/**
 * repaint the image upon an exposure event
 * @param gc : graphics context to repaint
 */
void drawing::paint(GraphicsContext*gc)
{
	//erase windows and redraw
	gc->clear();
	picture.draw(gc, vc);
	return;
}

/**
 * event that is activated upon a key being pressed down
 * @param gc      : graphics context object that may be affected
 * @param keycode : code of key that was pressed
 */
void drawing::keyDown(GraphicsContext* gc, unsigned int keycode){
	//this ensures that state cannot be changed if currently drawing

	//reset pressed
	if(keycode == 114){
		vc->undo();
		gc->clear();
		picture.draw(gc, vc);
	}
	//transformation select
	// t is translate
	else if(keycode == 116){
		tState = 't';
	}
	// z is vertical orbit
	else if(keycode == 122){
		tState = 'z';
	}

	// y is horiz orbit
	else if(keycode == 121){
		tState = 'y';
	}

	// s is scale
	else if(keycode == 115){
		tState = 's';
	}

	if(tState != 'x'){
		if(tState == 't'){
			//> pressed
			if(keycode == 46){
				vc->changeX('+');
				gc->clear();
				picture.draw(gc, vc);
			}
			//k pressed
			else if(keycode == 107){
				vc->changeY('-');
				gc->clear();
				picture.draw(gc, vc);
			}
			//< pressed
			else if(keycode == 44){
				vc->changeX('-');
				gc->clear();
				picture.draw(gc, vc);
			}
			//i pressed
			else if(keycode == 105){
				vc->changeY('+');
				gc->clear();
				picture.draw(gc, vc);
			}
		}
		//horizontal orbig state
		else if(tState == 'y'){
			//< pressed
			if(keycode == 44){
				vc->changeDegY('+');
				gc->clear();
				picture.draw(gc, vc);
			}
			//> pressed
			else if(keycode == 46){
				vc->changeDegY('-');
				gc->clear();
				picture.draw(gc, vc);
			}
		}
		//rotation z state
		else if(tState == 'z'){
			//< pressed
			if(keycode == 44){
				vc->changeDegHor('+');
				gc->clear();
				picture.draw(gc, vc);
			}
			//> pressed
			else if(keycode == 46){
				vc->changeDegHor('-');
				gc->clear();
				picture.draw(gc, vc);
			}
		}
		//scaling state
		else if(tState == 's'){
			//k pressed
			if(keycode == 107){
				vc->scale('-');
				gc->clear();
				picture.draw(gc, vc);
			}
			//i pressed
			else if(keycode == 105){
				vc->scale('+');
				gc->clear();
				picture.draw(gc, vc);
			}
		}
	}

}

/**
 * This function parses through an input file and calls printAndCheck
 * @param inFile : the file to be parsed in a string format
 */
void drawing::parseFile(string inFile, image& picture){
	x0 = y0 = z0 = x1 = y1 = z1 = x2 = y2 = z2 = 0;
	int vertT = 0;
	ifstream myFile;
	myFile.open(inFile);

	//Print error if file does not open for whatever reason
	if(!myFile){
		cerr << "\n**Unable to open file " << inFile;
		cout << "**\n**File may be missing, incorrect format, or corrupted**\n\n";
	}
	//If the file is valid
	else{
		//boolean switch for later logic

		string holder;
		bool vertComplete = false;

		//as long as there is more in the file
		while(getline(myFile, holder, ' ')){
			//if entering a vertex range
			if(!holder.compare("vertex")){
				string vertX;
				getline(myFile, vertX, ' ');
				while(!vertX.compare("")){
					getline(myFile, vertX, ' ');
				}

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

				if(vertT == 0){
					y0 = stof(vertY);
				}
				else if(vertT == 1){
					y1 = stof(vertY);
				}
				else if(vertT == 2){
					y2 = stof(vertY);
				}

				string vertZ;
				getline(myFile, vertZ, ' ');
				while(!vertZ.compare("")){
					getline(myFile, vertZ, ' ');
				}

				if(vertT == 0){
					z0 = stof(vertZ);
				}
				else if(vertT == 1){
					z1 = stof(vertZ);
				}
				else if(vertT == 2){
					z2 = stof(vertZ);
				}

				//it's screwing up here, this is causing it to only print every third
				vertT++;
				vertComplete = true;
			}

			//output once all vertices found
			if(vertComplete){
				vertComplete = false;
				if(vertT == 3){
					triangle t1(x0, y0, z0, 0, 255, 0, x1, y1, z1, x2, y2, z2);
					picture.add(&t1);
					vertT = 0;
				}
			}
		}

		//close file to save memory
		myFile.close();
	}
}

void drawing::drawAxes(){
	triangle t1(255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0);
	triangle t2(0, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0);
	triangle t3(0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0);
	picture.add(&t1);
	picture.add(&t2);
	picture.add(&t3);
}





