#include "Colors.h"

void setColorMap( vector<point> &points )
{
    cerr << " set color points " << endl;

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
	    points[i].r = ((float)points[i].colorSpot*ron)/rmod;
	    points[i].g = ((float)points[i].colorSpot*gon)/gmod;
	    points[i].b = ((float)points[i].colorSpot*bon)/bmod;
	}
    }
}
void randomColorMap()
{
}

void printColorMap()
{ 
   
}


void swapColor( vector<point> &points)
{
    colorRotate++;

    if(colorRotate > 3)
        colorRotate = 1;

    

    cerr << "colorRotate: " << colorRotate << endl;
    switch(colorRotate)	{
	case 1:
	    rmod = 1; gmod = 30; bmod = 10;
	    ron = 0; gon = 1; bon = 1;
	    break;
        case 2:
	    rmod = 30; gmod = 10; bmod = 1;
	    ron = 1; gon = 1; bon = 0;
	    break;
	case 3:
	    rmod = 10; gmod = 1; bmod = 30;
	    ron = 1; gon = 0; bon = 1;
	    break;
	default:
	    colorRotate = 0;
	    break;
    }
    setColorMap(points);

    
}
