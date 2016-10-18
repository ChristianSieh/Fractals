#ifndef JULIA_H
#define JULIA_H

#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Util.h"

using namespace std;

void solveQuadraticEq(complexNum lambda, complexNum * z);
void selfSqTransf(complexNum lambda, complexNum z, GLint numPoints, vector<point> &points);
void juliaInit(vector<point> &points);

#endif
