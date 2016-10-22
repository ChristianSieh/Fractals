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
    GLfloat x = 0, y = 0;      //point
    GLfloat r = 0, g = 0, b = 0;  //color value
    GLint colorSpot = 0;
};

// Stores data needed by zooming function
struct viewMod
{
    GLfloat z = 1;
    GLfloat x = 0 ,y = 0;
    bool change = false;
};

//stores complex valuse
struct cX
{
    GLfloat xCMin = -5.00, xCMax = 5.00;
    GLfloat yCMin =-5.00, yCMax = -5.00;
    GLfloat cW = 10;
    GLfloat cH = 10;
};

void plotPoint(point z);
void printPoint(point z);
void changeView(viewMod view, cX &cmplx);
#endif
