 /************************************************************************
   Program: 
   Author: 
   Class:
   Instructor:
   Date:
   Description:    (program requirements)
   Input:
   Output:
   Compilation instructions:
   Usage:
   Known bugs/missing features:
   Modifications:
   Date                Comment            
   ----    ------------------------------------------------
 ************************************************************************/
#include "Util.h"

 /************************************************************************
   Function: plotPoint
   Author: Charles Bonn and Christian Sieh
   Description: This function takes a point and plots it to the screen
                based on the point's x and y value as well as it's color
                values.
   Parameters:
        point z - The point that will be plotted on the screen.
 ************************************************************************/
void plotPoint (point z)
{
    /*set color to point color*/
    glColor3f (z.r, z.g, z.b);

    /*plot point*/
    glBegin (GL_POINTS);
        glVertex2f (z.x, z.y);
    glEnd ( );

}

void printPoint (point z)
{
    cerr << "Point position: (" << z.x << "," << z.y << ")\n";
    cerr << "ColorPoint: " << z.colorSpot << endl;
    cerr << "R: " << z.r << endl;
    cerr << "G: " << z.g << endl;
    cerr << "B: " << z.b << endl;
}
