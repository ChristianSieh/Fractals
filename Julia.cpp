 /************************************************************************
   Program: Fractals
   Author: Charles Bonn and Christian Sieh
   Class: CSC433
   Instructor: Dr. John Weiss
   Date: 10/21/2016
   Description: This file holds the functions used to compute the Julia Set
   Known bugs/missing features: N/A
 ************************************************************************/

#include "Julia.h"

 /************************************************************************
   Function: juliaComplexSquare
   Author: Taken from book
   Description: This function squares a complex number and returns it
   Parameters:
        complexNum z - The point that is used as z in z^2 + c
 ************************************************************************/
complexNum juliaComplexSquare ( complexNum z )
{
    complexNum zSquare;
    zSquare.x = z.x * z.x - z.y * z.y;
    zSquare.y = 2 * z.x * z.y;
    return zSquare;
}

 /************************************************************************
   Function: juliaSqTransf
   Author: Taken from book
   Description: This function computes z = z^2 + c repeatedly until z is
             greater than 4 or we reach maxIter. We then return count
             so we are able to tell how long it took z to diverge.
   Parameters:
        complexNum c - The initial point that is used as c in z^2 + c
        complexNum z - The point that is used as z in z^2 + c
        GLint maxIter - If count == maxIter then the point doesn't diverge
            and we return.
 ************************************************************************/
GLint juliaSqTransf ( complexNum c, complexNum z, GLint maxIter )
{
    GLint count = 0;

    /* Quit when z * z > 4 */
    while ( ( z.x * z.x + z.y * z.y <= 4.0 ) && ( count < maxIter ) )
    {
        z = juliaComplexSquare(z);
        z.x += c.x;
        z.y += c.y;
        count++;
    }

    return count;
}

 /************************************************************************
   Function: julia
   Author: Christian Sieh
   Description: This function goes through the complex plane a zIncr number
                of times in order to calculate the point for that pixel.
                The iterCount is how long it takes for the point to diverge
                and colorspot is used by Color.cpp to create a color map.
   Parameters:
        GLint nx - The number of x points our points vector will have
        Glint ny - The number of y points our points vector will have
        GLint maxIter - The maximum number of times we will run juliaSqTransf
        vector<point> points - A vector that will hold our computed points
            for the Julia set 
        complexNum c - The initial point that is used as c in z^2 + c
 ************************************************************************/
void julia ( GLint nx, GLint ny, GLint maxIter, vector<point> &points, complexNum c )
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
            iterCount = juliaSqTransf ( c, z, maxIter );

	        /* Save point values to point */
	        currPoint.x = z.x;
	        currPoint.y = z.y;
	
	        currPoint.colorSpot = iterCount;

	        points.push_back ( currPoint );
        }
    }
}

 /************************************************************************
   Function: juliaInit
   Author: Christian Sieh
   Description: This function sets the number of iterations and points that
                we will generate in the complex plane.
   Parameters:
		vector<point> points - A vector that will hold our computed points
            for the Julia set 
		complexNum c - The initial point that is used as c in z^2 + c
 ************************************************************************/
void juliaInit(vector<point> &points, complexNum c)
{
    /* Set number of x and y subdivisions and the max iterations. */
    GLint nx = 1000, ny = 1000, maxIter = 1000;
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

    points.clear();

    julia(nx, ny, maxIter, points, c);
}
