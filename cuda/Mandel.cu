/************************************************************************
  Program: Fractals
  Author: Charles Bonn and Christian Sieh
  Class: CSC433
  Instructor: John Weiss
  Date: 10/21/2016
  Description:  Mandelbrot functions
  Known bugs/missing features: N/A
************************************************************************/

#include "Mandel.h"


static GLint maxIter = 1000;

/* Calculate the square of a complex number. */
/************************************************************************
   Function: complexSquare
   Author: Taken from book
   Description: calculates the square of a complex number
   Parameters:
 complexNum z - a complex number of a point
 ************************************************************************/
__device__ complexNum complexSquare_para ( complexNum z )
{
    complexNum zSquare;
    zSquare.x = z.x * z.x - z.y * z.y;
    zSquare.y = 2 * z.x * z.y;
    return zSquare;
}

/* Calculate the square of a complex number. */
/************************************************************************
   Function: complexSquare
   Author: Taken from book
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
  Author: Taken from book
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
	z = complexSquare( z );
        z.x += z0.x;
        z.y += z0.y;
        count++;
    }
    return count;
}

/************************************************************************
  Function: mandelSqTransf
  Author: Taken from book
  Description: squares complex values
  Parameters:
 complexNum z0 -
       Glint maxIter -
************************************************************************/
__global__ void  mandelSqTransf_para (   int maxIter , point *points )
{
    complexNum z, z0;
    GLint count = 0;

    const int i = threadIdx.x + blockIdx.x * blockDim.x;
    z.x = points[i].x;
    z.y = points[i].y;
    z0.x = points[i].x;
    z0.y = points[i].y;

    /* Quit when z * z > 4 */
    while ( ( z.x * z.x + z.y * z.y <= 4.0 ) && ( count < maxIter ) )
    {
	    z = complexSquare_para ( z );
	    z.x += z0.x;
	    z.y += z0.y;
	    count++;
    }

     points[i].colorSpot = count;  
}
/************************************************************************
  Function: mandelbrot
  Author: Taken from book and modified by Charles Bonn and Christian Sieh
  Description: calculates mandelbrot points
  Parameters:
       GLint nx - x points
       Glint ny - y points 
       Glint maxIter - number of iterations per point
       vector<complexNum> &points - vector of points
************************************************************************/
void mandelbrot_para ( GLint nx, GLint ny, point *points, cX cmplx)
{
    complexNum z, zIncr;
  
    int i = 0;
    int size = nx * ny;

    
    //copy points

    /* initialize complex values */
    zIncr.x = cmplx.cW / ( GLfloat ( nx ) );
    zIncr.y = cmplx.cH / ( GLfloat ( ny ) );


    /* go though x values */
    for ( z.x = cmplx.xCMin; z.x < cmplx.xCMax; z.x += zIncr.x )
    {
        for ( z.y = cmplx.yCMin; z.y < cmplx.yCMax; z.y += zIncr.y )
        {
            /* Save point values to point */
            points[i].x = z.x;
            points[i].y = z.y;
	        i++;
         }	
    }

    point *d_points;

    cudaMalloc( ( void ** )&d_points, ((size * 10) * sizeof(point)) );
    cudaMemcpy( d_points, points, ((size * 10) * sizeof(point)) , cudaMemcpyHostToDevice );

    int nThreads = 1024;
    int nBlocks = (10000000 + nThreads -1 ) / nThreads;

    mandelSqTransf_para<<< nBlocks, nThreads >>>(maxIter,d_points);	
    cudaMemcpy( points, d_points, ((size * 10) * sizeof(point)) , cudaMemcpyDeviceToHost );
    cudaFree( d_points ); //free memory
}

/************************************************************************
  Function: mandelbrot
  Author: Taken from book and modified by Charles Bonn and Christian Sieh
  Description: calculates mandelbrot points
  Parameters:
 GLint nx - x points
       Glint ny - y points 
       Glint maxIter - number of iterations per point
       vector<complexNum> &points - vector of points
************************************************************************/
void mandelbrot ( GLint nx, GLint ny, point *points, cX cmplx)
{
    complexNum z, zIncr;
    point currPoint;
    int i = 0;
    int iterCount;

    /* initialize complex values */
    zIncr.x = cmplx.cW / ( GLfloat ( nx ) );
    zIncr.y = cmplx.cH / ( GLfloat ( ny ) );
	
    /* go though x values */
    for ( z.x = cmplx.xCMin; z.x < cmplx.xCMax; z.x += zIncr.x )
    {
	/* go though y values */
        for ( z.y = cmplx.yCMin; z.y < cmplx.yCMax; z.y += zIncr.y )
        {
	        /* Calculate point value */ 
            iterCount = mandelSqTransf ( z, maxIter );

	        /* Save point values to point */
	        points[i].x = z.x;
	        points[i].y = z.y;
	        points[i].colorSpot = iterCount;
               
		    /* push point to stack */
                
		    i++;
	    }
    }
}

/************************************************************************
  Function: mandelInit
  Author: takenfrom book and modified by Charles Bonn and Christian Sieh
  Description: init for mandelbrot points
  Parameters: vector<point> &points - vector of points
************************************************************************/
void mandelInit ( point *points , cX cmplx, bool parallel)
{
    /* Set number of x and y subdivisions and the max iterations. */
    GLint nx = 1000, ny = 1000;//, maxIter = 1500;
    glClear ( GL_COLOR_BUFFER_BIT );
    chrono::time_point<std::chrono::system_clock> c;
    

    /* Clear display window. */
    if( parallel == false )
    {
        c = chrono::system_clock::now();
        mandelbrot( nx, ny, points, cmplx);
	    chrono::duration<double> d_cpu = chrono::system_clock::now() - c;
    }
    else
    {
        c = chrono::system_clock::now();
	    mandelbrot_para(nx, ny, points, cmplx);
        chrono::duration<double> d_gpu = chrono::system_clock::now() - c;
    }
}

