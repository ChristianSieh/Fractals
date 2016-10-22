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

static GLint maxIter = 1000;

 /************************************************************************
   Function: juliaComplexSquare
   Author: Taken from book
   Description: This function squares a complex number and returns it.
                This function is the parallel version.
   Parameters:
        complexNum z - The point that is used as z in z^2 + c
 ************************************************************************/
__device__ complexNum juliaComplexSquare_para ( complexNum z )
{
    complexNum zSquare;
    zSquare.x = z.x * z.x - z.y * z.y;
    zSquare.y = 2 * z.x * z.y;
    return zSquare;
}

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
   Function: juliaSqTransf
   Author: Taken from book
   Description: This function computes z = z^2 + c repeatedly until z is
             greater than 4 or we reach maxIter. We then return count
             so we are able to tell how long it took z to diverge.
             This function is the parallel version.
   Parameters:
        complexNum c - The initial point that is used as c in z^2 + c
        complexNum z - The point that is used as z in z^2 + c
        GLint maxIter - If count == maxIter then the point doesn't diverge
            and we return.
 ************************************************************************/
__global__ void juliaSqTransf_para ( point *points, int maxIter, complexNum c )
{
    complexNum z;
    GLint count = 0;

    const int i = threadIdx.x + blockIdx.x * blockDim.x;
    z.x = points[i].x;
    z.y = points[i].y;

    /* Quit when z * z > 4 */
    while ( ( z.x * z.x + z.y * z.y <= 4.0 ) && ( count < maxIter ) )
    {
        z = juliaComplexSquare_para(z);
        z.x += c.x;
        z.y += c.y;
        count++;
    }

    points[i].colorSpot = count;
}

 /************************************************************************
   Function: julia_para
   Author: Christian Sieh
   Description: This function goes through the complex plane a zIncr number
                of times in order to calculate the point for that pixel.
                The iterCount is how long it takes for the point to diverge
                and colorspot is used by Color.cpp to create a color map.
                This function is the parallel version.
   Parameters:
        GLint nx - The number of x points our points vector will have
        Glint ny - The number of y points our points vector will have
        GLint maxIter - The maximum number of times we will run juliaSqTransf
        vector<point> points - A vector that will hold our computed points
            for the Julia set 
        complexNum c - The initial point that is used as c in z^2 + c
 ************************************************************************/
void julia_para ( GLint nx, GLint ny, point *points, complexNum c, cX cmplx )
{
    complexNum z, zIncr;
    point currPoint;

    int i = 0;
    int size = nx * ny;

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

    juliaSqTransf_para<<< nBlocks, nThreads >>>(d_points, maxIter, c);	
    cudaMemcpy( points, d_points, ((size * 10) * sizeof(point)) , cudaMemcpyDeviceToHost );
    cudaFree( d_points ); //free memory
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
void julia ( GLint nx, GLint ny, point *points, complexNum c, cX cmplx )
{
    complexNum z, zIncr;
    point currPoint;
    int i = 0;
    GLint iterCount;

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
            iterCount = juliaSqTransf ( c, z, maxIter );

	        /* Save point values to point */
	        currPoint.x = z.x;
	        currPoint.y = z.y;
	
	        currPoint.colorSpot = iterCount;

            i++;
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
void juliaInit(point *points, complexNum c, cX cmplx, bool parallel)
{
    /* Set number of x and y subdivisions and the max iterations. */
    GLint nx = 1000, ny = 1000;
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
    chrono::time_point<std::chrono::system_clock> clock;

    /* Clear display window. */
    if( parallel == false )
    {
        clock = chrono::system_clock::now();
        julia(nx, ny, points, c, cmplx);
	    chrono::duration<double> d_cpu = chrono::system_clock::now() - clock;
    }
    else
    {
        clock = chrono::system_clock::now();
	    julia_para(nx, ny, points, c, cmplx);
        chrono::duration<double> d_gpu = chrono::system_clock::now() - clock;
    }
}
