#ifndef UTIL_H
#define UTIL_H

#include <GL/freeglut.h>

static GLfloat xComplexMin = -2.00, xComplexMax = 0.50;
static GLfloat yComplexMin = -1.25, yComplexMax = 1.25;
static GLfloat complexWidth = xComplexMax - xComplexMin;
static GLfloat complexHeight = yComplexMax - yComplexMin;

struct complexNum
{
    GLfloat x,y;
};

struct color 
{ 
    GLfloat r, g, b; 
};

void plotPoint(complexNum z);

#endif
