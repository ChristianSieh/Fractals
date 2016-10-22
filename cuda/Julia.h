 /************************************************************************
   Program: Fractals
   Author: Charles Bonn and Christian Sieh
   Class: CSC433
   Instructor: John Wiess
   Date: 10/21/2016
   Description: Header file for julia functions
   Known bugs/missing features: N/A
 ************************************************************************/

#ifndef JULIA_H
#define JULIA_H

#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Util.h"

using namespace std;

complexNum juliaComplexSquare ( complexNum z );
GLint juliaSqTransf ( complexNum z0, complexNum z, GLint maxIter );
void julia ( GLint nx, GLint ny, GLint maxIter, point *points, complexNum c );
void juliaInit(point *points, complexNum c);

#endif
