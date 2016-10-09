#ifndef JULIA_H
#define JULIA_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Util.h"
#include <GL/freeglut.h>

using namespace std;

void plotPoint(complexNum z);
void solveQuadraticEq(complexNum lambda, complexNum * z);
void selfSqTransf(complexNum lambda, complexNum z, GLint numPoints);

#endif
