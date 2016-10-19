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

complexNum juliaComplexSquare ( complexNum z )
{
    complexNum zSquare;
    zSquare.x = z.x * z.x - z.y * z.y;
    zSquare.y = 2 * z.x * z.y;
    return zSquare;
}

GLint juliaSqTransf ( complexNum z0, complexNum z, GLint maxIter )
{
    GLint count = 0;

    /* Quit when z * z > 4 */
    while ( ( z.x * z.x + z.y * z.y <= 4.0 ) && ( count < maxIter ) )
    {
        z = juliaComplexSquare(z);
        z.x += z0.x;
        z.y += z0.y;
        count++;
    }

    return count;
}

void julia ( GLint nx, GLint ny, GLint maxIter, vector<point> &points, point initialPoint )
{
    complexNum z0 = { -0.7, 0.27015 };

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
            iterCount = juliaSqTransf ( z0, z, maxIter );

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
void juliaInit(vector<point> &points, point initialPoint)
{
    /* Set number of x and y subdivisions and the max iterations. */
    GLint nx = 1000, ny = 1000, maxIter = 1000;
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

    points.clear();

    julia(nx, ny, maxIter, points, initialPoint);
}
