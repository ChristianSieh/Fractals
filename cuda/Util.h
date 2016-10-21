 /************************************************************************
   Program: Fractals
   Author: Charles Bonn and Christian Sieh
   Class: CSC433
   Instructor: John Wiess
   Date: 10/21/2016
   Description: Header file for utility functions and structures
   Known bugs/missing features: N/A
 ************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

// Stores a complex value
struct complexNum
{
    GLfloat x,y;
};

// Stores RGP color values
struct color 
{ 
    GLfloat r, g, b; 
};

// Holds position and color data for a point
struct point
{
    GLfloat x, y;      //point
    GLfloat r, g, b;  //color value
    GLint colorSpot;
};

// Stores data needed by zooming function
struct viewMod
{
    GLfloat z = 1;
    GLfloat x = 0 ,y = 0;
    bool change = false;
};

//static GLfloat xComplexMin = -5.00, xComplexMax = 5.00;
//static GLfloat yComplexMin = -5.00, yComplexMax = 5.00;

//static GLfloat xComplexMin, xComplexMax;
//static GLfloat yComplexMin, yComplexMax;
//static GLfloat xComplexMin = -1.00, xComplexMax = .20;
//static GLfloat yComplexMin = -.75, yComplexMax = .75;
//static GLfloat complexWidth;// = fabs(xComplexMax - xComplexMin);
//static GLfloat complexHeight;// = fabs(yComplexMax - yComplexMin);

void plotPoint(point z);
void printPoint(point z);
void changeView(viewMod view);
float getXMin();
float getXMax();
float getYMin();
float getYMax();
float getWidth();
float getHeight();
#endif
