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

static const GLfloat xxComplexMin = -5.00, xxComplexMax = 5.00;
static const GLfloat yyComplexMin = -5.00, yyComplexMax = 5.00;
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

void changeView(viewMod view)
{
    cerr << "view.z: " << view.z << endl; 
    xComplexMin = (xxComplexMin / view.z) + view.x;
    xComplexMax = (xxComplexMax / view.z) + view.x;
    yComplexMin = (yyComplexMin / view.z) + view.y;
    yComplexMax = (yyComplexMax / view.z) + view.y;

    complexWidth = fabs(xComplexMax - xComplexMin);
    complexHeight = fabs(yComplexMax - yComplexMin); 
    cerr << "xmin: " << xComplexMin << endl;
    cerr << "xmax: " << xComplexMax << endl;
    cerr << "ymin: " << yComplexMin << endl;
    cerr << "ymax: " << yComplexMax << endl;
    cerr << "Width: " << complexWidth << endl;
    cerr << "Height: " << complexHeight << endl;
}

float getXMin()
{
    return xComplexMin;
}

float getXMax()
{
    return xComplexMax;
}

float getYMin()
{
    return yComplexMin;
}

float getYMax()
{
    return yComplexMax;
}

float getWidth()
{
    return complexHeight;
}

float getHeight()
{
    return complexHeight;
}
