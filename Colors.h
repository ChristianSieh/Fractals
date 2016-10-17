#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Util.h"

using namespace std;

//static int currColorMapNum = 0;
//static const int maxColorMapNum = 2;  // total number of color maps

random_device rd;
mt19937 mt(rd());
uniform_real_distribution<double> color(0.0, 1.0);

static GLfloat ron = .1, gon = 0, bon = float(1) / 30;
static int colorRotate = 0;

void setColorMap(vector<point> &points);
void randomColorMap(vector<point> &points);
void printColorMap();
void swapColor(vector<point> &points);
#endif
