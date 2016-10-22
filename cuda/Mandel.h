 /************************************************************************
   Program: Fractals
   Author: Charles Bonn and Christian Sieh
   Class: CSC433
   Instructor: John Wiess
   Date: 10/21/2016
   Description: Header file for mandelbrot functions
   Known bugs/missing features: N/A
 ************************************************************************/

#ifndef MANDEL_CUH
#define MANDEL_CUH

#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <math.h>
#include "Util.h"
#include <GL/freeglut.h>

using namespace std;

 /*********************** function prototypes ***************************/
complexNum complexSquare(complexNum z);
GLint mandelSqTransf(complexNum z0, GLint maxIter);
void mandelbrot(GLint nx, GLint ny, point *points, cX cmplx);
void mandelInit(point *points, cX cmplx);

#endif
