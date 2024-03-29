 /************************************************************************
   Program: Fractals
   Author: Charles Bonn
   Class: CSC433
   Instructor: John Weiss
   Date: 10/21/201
   Description:   Color functions for Fractals. This file handles color
		options for the pixels.
   Known bugs/missing features: N/A
 ************************************************************************/
#include "Colors.h"

/*********************** global type definitions ***********************/
static int colorRotate = 0;
static GLfloat rmod = 10, gmod = 1, bmod = 30;
static GLfloat ron = 1, gon = 0, bon = 1;
static vector<color> colorMap;

 /************************************************************************
   Function: setColorMap
   Author: Charles Bonn
   Description: setColorMap goes though each of the points generated by 
		the mandlebrot point generator and assigns it a color 
		value based off of the colorSpot ( number of itterations
		on the mandlebrot set) and calcuates the color value 
		based on the algorithm: (colorSpot * on)/mod

		colorSpot -  mandelbrot iteration value
		(r,g,b)on - 1 or 0 value to use the color
                (r,g,b)mod - color intensity

   Parameters: 
        vector<point> &points - vector of points
 ************************************************************************/ 
void setColorMap( point *points )
{
    for(unsigned int i = 0; i < 1000000; i++)
    {
        if( points[i].colorSpot == 1000 )
	    {
	        points[i].r = 0.0;
	        points[i].g = 0.0;
	        points[i].b = 0.0;
	    }
	    else
	    {
	        /* set color values */
	        points[i].r = ((float)points[i].colorSpot*ron)/rmod;
	        points[i].g = ((float)points[i].colorSpot*gon)/gmod;
	        points[i].b = ((float)points[i].colorSpot*bon)/bmod;
	    }
    }
}

 /************************************************************************
   Function: randomColorMap
   Author: Charles Bonn
   Description: Generates random color values for the color set
   Parameters: 
        vector<point> &points - vector of points 
 ************************************************************************/
void randomColorMap( point *points)
{
    srand(time(NULL));
    rmod = rand() % 30 + 1;
    gmod = rand() % 30 + 1;
    bmod = rand() % 30 + 1;
    ron = rand() % 2;
    gon = rand() % 2;
    bon = rand() % 2;

    setColorMap(points);
}

 /************************************************************************
   Function: swapColor
   Author: Charles Bonn
   Description: Swaps the current color pallet between preset color values
   Parameters: 
        vector<point> &points - vector of points
 ************************************************************************/
void swapColor( point *points)
{
    colorRotate++;

    if(colorRotate > 4)
        colorRotate = 1;

    /*preset color pallets*/
    switch(colorRotate)	{
	case 1:  //yellow
	    rmod = 1; gmod = 30; bmod = 10;
	    ron = 0; gon = 1; bon = 1;
	    break;
        case 2: //blue
	    rmod = 30; gmod = 10; bmod = 1;
	    ron = 1; gon = 1; bon = 0;
	    break;
	case 3: //red
	    rmod = 10; gmod = 1; bmod = 30;
	    ron = 1; gon = 0; bon = 1;
	    break;
        case 4: //grey
	    rmod = 15; gmod = 15; bmod = 15;
	    ron = 1; gon = 1; bon = 1;
	default:
	    colorRotate = 0;
	    break;
    }
    setColorMap(points);
}
 /************************************************************************
   Function: animateColor
   Author: Charles Bonn
   Description: Animate color takes the color pallet and shifts it to 
		create animation effect. it replaces the current r,g,b 
		values using the algorithm 
			pixel = fmod( (pixel + shift) * on, 1 )

		pixel - r,g,b value
		shift - how much to shift the color value
		on - if the color is on or off

   Parameters: 
        vector<point> &points - vector of points
 ************************************************************************/
void animateColor( point *points )
{
    /* value to shift pixel color */
    double shift = .05; 

    for(unsigned int i = 0; i < 1000000; i++)
    {
        points[i].r = fmod((points[i].r + shift)*ron, 1);
        points[i].g = fmod((points[i].g + shift)*gon, 1);
	points[i].b = fmod((points[i].b + shift)*bon, 1);

    }
}
