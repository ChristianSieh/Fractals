#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

struct complexNum
{
    GLfloat x,y;
};

struct color 
{ 
    GLfloat r, g, b; 
};

struct point
{
    GLfloat x, y;      //point
    GLfloat r, g, b;  //color value
    GLint colorSpot;
};


struct viewMod
{
    GLint zoom;
    GLfloat x ,y;
};

static GLfloat xComplexMin = -5.00, xComplexMax = 5.00;
static GLfloat yComplexMin = -5.00, yComplexMax = 5.00;

//static GLfloat xComplexMin = -2.00, xComplexMax = 1.00;
//static GLfloat yComplexMin = -1.25, yComplexMax = 1.25;
//static GLfloat xComplexMin = -1.00, xComplexMax = .20;
//static GLfloat yComplexMin = -.75, yComplexMax = .75;
static GLfloat complexWidth = fabs(xComplexMax - xComplexMin);
static GLfloat complexHeight = fabs(yComplexMax - yComplexMin);


void plotPoint(point z);
void printPoint(point z);
#endif
