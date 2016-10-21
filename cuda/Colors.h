 /************************************************************************
   Program: Fractals
   Author: Charles Bonn
   Class: CSC433
   Instructor: John Wiess
   Date: 10/21/2016
   Description: Header file for color functions
   Known bugs/missing features: N/A
 ************************************************************************/

#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Util.h"
#include <vector>
#include <math.h>

using namespace std;

/*********************** function prototypes ***************************/
void setColorMap(vector<point> &points);
void randomColorMap(vector<point> &points);
void printColorMap();
void swapColor(vector<point> &points);
void animateColor(vector<point> &points);

#endif
