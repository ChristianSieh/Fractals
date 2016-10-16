#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Util.h"

using namespace std;

static int currColorMapNum = 0;
static const int maxColorMapNum = 2;  // total number of color maps
static color currColorMap[7] = {{0.0, 0.0, 0.0},{1.0, 0.5, 0.0},{1.0, 0.0, 0.0},
			   {0.0,0.0,0.5},{1.0, 1.0, 0.0},{0.0,0.0,0.3},{0.0, 1.0, 1.0}};

// 2 color maps
static const color colorMaps[][7] ={
	{{0.0, 0.0, 0.0},{1.0, 0.5, 0.0},{1.0, 0.0, 0.0},{0.0,0.0,0.5},{1.0, 1.0, 0.0},{0.0,0.0,0.3},{0.0, 1.0, 1.0}},
	{{1.0, 0.0, 0.0},{0.3, 0.5, 0.0},{0.5, 0.0, 0.5},{1.0,0.0,0.5},{1.0, 0.0, 0.0},{0.2,0.8,0.3},{0.8, 0.0, 1.0}}

	};

void setColorMap(int map);
void randomColorMap();
void printColorMap();
void changeColorMap();
void swapColor();
#endif
