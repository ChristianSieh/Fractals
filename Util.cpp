 /************************************************************************
   Program: Fractals
   Author: Charles Bonn and Christian Sieh
   Class: CSC433
   Instructor: Dr. John Weiss
   Date: 10/21/16
   Description: This file contains the functions that are used across
            multiple files and are not exclusive to the Julia and Mandel
            sets.
   Known bugs/missing features: N/A
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

 /************************************************************************
   Function: printPoint
   Author: Charles Bonn
   Description: This function takes a point and outputs it's values. Used
                for debugging purposes.
   Parameters:
        point z - The point's values we are trying to print.
 ************************************************************************/
void printPoint (point z)
{
    cerr << "Point position: (" << z.x << "," << z.y << ")\n";
    cerr << "ColorPoint: " << z.colorSpot << endl;
    cerr << "R: " << z.r << endl;
    cerr << "G: " << z.g << endl;
    cerr << "B: " << z.b << endl;
}
