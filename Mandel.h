#ifndef MANDEL_H
#define MANDEL_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Util.h"
#include <GL/freeglut.h>

using namespace std;

complexNum complexSquare(complexNum z);
GLint mandelSqTransf(complexNum z0, GLint maxIter);
void mandelbrot(GLint nx, GLint ny, GLint maxIter, vector<complexNum> &points);
void mandelInit(vector<complexNum> &points);

#endif
