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
  Description:
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
  Author: taken from book
  Description:
  Parameters:
 GLint nx -
       Glint ny -
       Glint maxIter
       vector<complexNum> &points -
************************************************************************/
void mandelbrot ( GLint nx, GLint ny, GLint maxIter, vector<point> &points )
{
    complexNum z, zIncr;
    //color ptColor;
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
	
	    /* Set color based on value*/
            if ( iterCount >= maxIter )
            {
                /* Set point color to black. */
                currPoint.r = currColorMap[0].r;
		currPoint.g = currColorMap[0].g;
                currPoint.b = currColorMap[0].b;
                currPoint.colorSpot = 0;
                
            }
            else if ( iterCount > ( maxIter / 8 ) )
            {
                /* Set point color to orange. */
		currPoint.r = currColorMap[1].r;
		currPoint.g = currColorMap[1].g;
                currPoint.b = currColorMap[1].b;
		currPoint.colorSpot = 1;
            }
            else if ( iterCount > ( maxIter / 10 ) )
            {
                /* Set point color to red. */
		currPoint.r = currColorMap[2].r;
		currPoint.g = currColorMap[2].g;
                currPoint.b = currColorMap[2].b;
                currPoint.colorSpot = 2;
            }
            else if ( iterCount > ( maxIter / 20 ) )
            {
                /* Set point color to dark blue. */
		currPoint.r = currColorMap[3].r;
		currPoint.g = currColorMap[3].g;
                currPoint.b = currColorMap[3].b;
                currPoint.colorSpot = 3;
            }
            else if ( iterCount > ( maxIter / 40 ) )
            {
                /* Set point color to yellow. */
		currPoint.r = currColorMap[4].r;
		currPoint.g = currColorMap[4].g;
                currPoint.b = currColorMap[4].b;
                currPoint.colorSpot = 4;
            }
            else if ( iterCount > ( maxIter / 100 ) )
            {
                /* Set point color to dark green. */
		currPoint.r = currColorMap[5].r;
		currPoint.g = currColorMap[5].g;
                currPoint.b = currColorMap[5].b;
                currPoint.colorSpot = 5;
            }
            else
            {
                /* Set point color to cyan. */
		currPoint.r = currColorMap[6].r;
		currPoint.g = currColorMap[6].g;
                currPoint.b = currColorMap[6].b;
                currPoint.colorSpot = 6;
            }
            /* Plot the color point. */
            //glColor3f (ptColor.r, ptColor.g, ptColor.b);
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
void mandelInit ( vector<point> &points )
{
    /* Set number of x and y subdivisions and the max iterations. */
    GLint nx = 1000, ny = 1000, maxIter = 1000;
    glClear ( GL_COLOR_BUFFER_BIT );

    points.empty();

    /* Clear display window. */
    mandelbrot ( nx, ny, maxIter, points );
}

