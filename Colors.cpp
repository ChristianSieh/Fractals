#include "Colors.h"

void setColorMap(int map)
{
    cerr << "setting color map" << endl;
    for(int i = 0; i < 7; i++ )
    {
	currColorMap[i].r = colorMaps[map][i].r;
	currColorMap[i].g = colorMaps[map][i].g;
	currColorMap[i].b = colorMaps[map][i].b;
    }
}

void randomColorMap()
{
}

void printColorMap()
{
    for(int i = 0; i < 7; i++)
    {
	cerr << "Color map color: " << i << endl;
	cerr << "R: " << currColorMap[i].r << endl;
	cerr << "G: " << currColorMap[i].g << endl;
	cerr << "B: " << currColorMap[i].b << endl;
    }
}

void changeColorMap()
{
    currColorMapNum++;

    if( currColorMapNum >= maxColorMapNum )
    {
        currColorMapNum = 0;
    }
}

void swapColor()
{
}
