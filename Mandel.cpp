/************************************************************************
  Program: Fractals
  Author: Charles Bonn and Christian Sieh
  Class: csc433
  Instructor: John Weiss
  Date: 10/27/2016
  Description:  mandelbrot functions
  Known bugs/missing features:
  Modifications:
  Date                Comment
  ----    ------------------------------------------------
************************************************************************/

#include "Mandel.h"

/* Calculate the square of a complex number. */
/************************************************************************
   Function: complexSquare
   Author: taken from book
   Description: calculates the square of a complex number
   Parameters:
 complexNum z - a complex number of a point
 ************************************************************************/
complexNum complexSquare ( complexNum z )
{
    complexNum zSquare;
    zSquare.x = z.x * z.x - z.y * z.y;
    zSquare.y = 2 * z.x * z.y;
    return zSquare;
}

/************************************************************************
  Function: mandelSqTransf
  Author: taken from book
  Description: squares complex values
  Parameters:
 complexNum z0 -
       Glint maxIter -
************************************************************************/
GLint mandelSqTransf ( complexNum z0, GLint maxIter )
{
    complexNum z = z0;
    GLint count = 0;

    /* Quit when z * z > 4 */
    while ( ( z.x * z.x + z.y * z.y <= 4.0 ) && ( count < maxIter ) )
    {
        z = complexSquare ( z );
        z.x += z0.x;
        z.y += z0.y;
        count++;
    }
    return count;
}

/************************************************************************
  Function: mandelbrot
  Author: taken from book and modified by Charles Bonn and Christian Sieh
  Description: calculates mandelbrot points
  Parameters:
 GLint nx - x points
       Glint ny - y points 
       Glint maxIter - number of iterations per point
       vector<complexNum> &points - vector of points
************************************************************************/
void mandelbrot ( GLint nx, GLint ny, GLint maxIter, vector<point> &points )
{
    complexNum z, zIncr;
    point currPoint;
    GLint iterCount;

    zIncr.x = complexWidth / GLfloat ( nx );
    zIncr.y = complexHeight / GLfloat ( ny );

    for ( z.x = xComplexMin; z.x < xComplexMax; z.x += zIncr.x )
    {
        for ( z.y = yComplexMin; z.y < yComplexMax; z.y += zIncr.y )
        {
	        /* Calculate point value */ 
            iterCount = mandelSqTransf ( z, maxIter );

	        /* Save point values to point */
	        currPoint.x = z.x;
	        currPoint.y = z.y;
	
	        currPoint.colorSpot = iterCount;
               
	        points.push_back ( currPoint );
        }
    }
}

/************************************************************************
  Function: mandelInit
  Author: takenfrom book and modified by Charles Bonn and Christian Sieh
  Description: init for mandelbrot points
  Parameters: vector<point> &points - vector of points
************************************************************************/
void mandelInit ( vector<point> &points )
{

    /* Set number of x and y subdivisions and the max iterations. */
    GLint nx = 1000, ny = 1000, maxIter = 1000;
    glClear ( GL_COLOR_BUFFER_BIT );

    points.clear();

    /* Clear display window. */
    mandelbrot ( nx, ny, maxIter, points );
}

