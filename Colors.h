#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Util.h"

using namespace std;

//static int currColorMapNum = 0;
//static const int maxColorMapNum = 2;  // total number of color maps



static GLfloat rmod = 10, gmod = 1, bmod = 30;
static GLfloat ron = 1, gon = 0, bon = 1;
static int colorRotate = 0;

void setColorMap(vector<point> &points);
void randomColorMap();
void printColorMap();
void swapColor(vector<point> &points);
#endif
