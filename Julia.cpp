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

#include "Julia.h"

 /************************************************************************
   Function: juliaComplexSquare
   Author:
   Description: This function squares a complex number and returns it
   Parameters:
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
   Author: Christian Sieh
   Description: This function computes z = z^2 + c repeatedly until z is
             greater than 4 or we reach maxIter. We then return count
             so we are able to tell how long it took z to diverge.
   Parameters:
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
   Description: This function goes throught the complex name a zIncr number
                of times in order to calulate the point for that pixel.
                The iterCount is how long it takes for the point to diverge
                and colorspot is used by Color.cpp to create a color map.
   Parameters:
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
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
void juliaInit(vector<point> &points, complexNum c)
{
    /* Set number of x and y subdivisions and the max iterations. */
    GLint nx = 1000, ny = 1000, maxIter = 1000;
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

    points.clear();

    julia(nx, ny, maxIter, points, c);
}
