#include "x11context.h"
#include <unistd.h>
#include <iostream>
#include "drawing.h"
int main(void)
{
GraphicsContext*gc = new X11Context(800,600,GraphicsContext::BLACK);
gc->setColor(GraphicsContext::GREEN);
// make a drawing
drawing md;
// start event loop - this function will return when X is clicked
// on window
gc->runLoop(&md);
delete gc;
return 0;
}
