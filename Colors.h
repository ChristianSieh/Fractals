/************************************************************************
   Program: Fractals
   Author: Charles Bonn
   Class: csc433
   Date: 10/27/2016
   Description: Header file for the Color functions
   Known bugs/missing features:
   Modifications:
   Date                Comment            
   ----    ------------------------------------------------
 ************************************************************************/

#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>
#include <iostream>
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
