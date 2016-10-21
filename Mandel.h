 /************************************************************************
   Program: Fractals
   Author: Charles Bonn and Christian Sieh
   Class: CSC433
   Instructor: John Wiess
   Date: 10/21/2016
   Description: Header file for mandelbrot functions
   Known bugs/missing features: N/A
 ************************************************************************/

#ifndef MANDEL_H
#define MANDEL_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Util.h"
#include <GL/freeglut.h>

using namespace std;

 /*********************** function prototypes ***************************/
complexNum complexSquare(complexNum z);
GLint mandelSqTransf(complexNum z0, GLint maxIter);
void mandelbrot(GLint nx, GLint ny, vector<point> &points, viewMod view);
void mandelInit(vector<point> &points, viewMod view);

#endif
