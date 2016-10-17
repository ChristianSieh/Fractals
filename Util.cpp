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
   Function:
   Author:
   Description:
   Parameters:
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
