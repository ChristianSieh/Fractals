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
void julia ( GLint nx, GLint ny, GLint maxIter, vector<point> &points, point initialPoint );
void juliaInit(vector<point> &points, point initialPoint);

#endif
