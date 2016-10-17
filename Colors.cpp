#include "Colors.h"

void setColorMap( vector<point> &points )
{
    for(unsigned int i = 0; i < points.size(); i++)
    {
        if( points[i].colorSpot == 1000 )
	    {
	        points[i].r = 1.0;
	        points[i].g = 1.0;
	        points[i].b = 1.0;
	    }
	    else
	    {
	        points[i].r = ((float)points[i].colorSpot*ron);
	        points[i].g = ((float)points[i].colorSpot*gon);
	        points[i].b = ((float)points[i].colorSpot*bon);
	    }
    }
}

void randomColorMap(vector<point> &points)
{
    float red = color(mt);
    float green = color(mt);
    float blue = color(mt);

    for(unsigned int i = 0; i < points.size(); i++)
    {
        points[i].r = ((float)points[i].colorSpot*red);
        points[i].g = ((float)points[i].colorSpot*green);
        points[i].b = ((float)points[i].colorSpot*blue);
    }
}

void printColorMap()
{ 
   
}

void swapColor( vector<point> &points)
{
    colorRotate++;

    if(colorRotate > 3)
        colorRotate = 1;

    switch(colorRotate)	
    {
	    case 1:
	        ron = 0; gon = float(1) / 30; bon = .1;
	        break;
        case 2:
	        ron = float(1) / 30; gon = .1; bon = 0;
	        break;
	    case 3:
	        ron = .1; gon = 0; bon = float(1) / 30;
	        break;
	    default:
	        colorRotate = 0;
	        break;
    }
    setColorMap(points);
}
