 /************************************************************************
   Program: Fractals
   Author: Charles Bonn and Christian Sieh
   Class: CSC433
   Instructor: John Weiss
   Date: 10/21/2016
   Description: The purpose of this program is to display the Julia and
                Mandelbrot sets. This program will initialize one of the
                two fractals and then the user is able to switch between
                the sets by using the "j" key. The Julia set that is
                generated is based on the mouse position. The user is also
                able to pan and zoom around the fractal. Panning is done
                by using the arrow keys or clicking and dragging with the
                mouse. Zooming is done with the "+" and "-" keys or a
                mouse scroll wheel. The user can also change the color
                map that is used to display the fractal by using the "c"
                key for predifined colors, or the "r" key for a random
                color map. Finally, the user can animate the color map by
                pushing the "a" key.
   Input: None
   Output: Graphical window with Mandelbrot or Julia set
   Compilation instructions: Run make file
   Usage: ./Fractals
   Known Bugs:
        1) Zoom value does not scale with how far zoomed in you are. This causes
        zooming beyond a certain point to take a long time.

        2) There is an occasional bug were the arrow keys will be inverted and
        you will pan the wrong direction.        

   Benchmarks:
        Our starting complex width and height were both 5 and as we zoomed
        in we were looking at a smaller section of the fractal which
        contained more points.

        Complex Width   Complex Height  Sequential  Parallel    Percentage
        5               5               1.165 sec   0.169 sec   689%  
        3.5             3.5             2.427 sec   0.172 sec   1411%
        1.5             1.5             6.34 sec    0.171 sec   3707% 
        0.5             0.5             15.3 sec    0.176 sec   8693%   
        
 ************************************************************************/

#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Mandel.h"
#include "Julia.h"
#include "Colors.h"
#include "Util.h"

using namespace std;

// Set initial size of display window
GLsizei ScreenWidth = 600, ScreenHeight = 600;

// keypresses
const int EscapeKey = 27;

//Global varables
double zoomVal = 0;
viewMod view;
cX cmplx;
bool juliaSet = false;
bool animation = false;
bool parallel = false;
int animationSpeed = 100;
int mouseX = 0;
int mouseY = 0;
int xOffset;
int yOffset;
int zoomX;
int zoomY;
point *points;
//point points[10000000];
complexNum comPoint;

/*********************** function prototypes ***************************/
void init( void );
void display( void );
void update( int value );
void reshape( GLint newWidth, GLint newHeight );
void keyboard( unsigned char key, int x, int y );
void special( int key, int x, int y );
void mouseclick( int button, int state, int x, int y );
void mousedrag( int x, int y );

 /************************************************************************
   Function: Main
   Author: Charles Bonn and Christian Sieh
   Description: The main function of the program which makes initilization 
                calls and starts the main glut loop
   Parameters: 
           int argc - number of arguments
	       char* argv[] - argument values
 ************************************************************************/
int main(int argc, char* argv[])
{

    points = ( point * )malloc( 10000000 *sizeof ( point ) );
    /* main initilizations */
    glutInit(&argc, argv);
    init();
   
    /* initilzie view */
    changeView(view, cmplx); 
    /* initilize points */
    if(juliaSet)
    {
        // Get the origin of the screen so our point
        // is in the correct quadrant
        int xOrigin = ScreenWidth / 2;
        int yOrigin = ScreenHeight / 2;

        // If we start with a Julia set then we don't have any mouse
        // position data so we pick a point close to the origin of the
        // screen so we get an interesting Julia Set
        point initialPoint;
        initialPoint.x = xOrigin - 50;
        initialPoint.y = yOrigin + 50;

        initialPoint.x = initialPoint.x - xOrigin;
        initialPoint.y = initialPoint.y - yOrigin;

        complexNum comPoint;

        // Convert the pixel point into a a point in the complex plane
        comPoint.x = (cmplx.cW / ScreenWidth) * initialPoint.x;
        comPoint.y = (cmplx.cH / ScreenHeight) * initialPoint.y;

        juliaInit(points, comPoint, cmplx, parallel);
        setColorMap(points);
        juliaSet = false;
    }
    else
    {
        mandelInit(points, cmplx, parallel);
	    setColorMap(points);
        juliaSet = true;
    }
    /* start timer */
    glutTimerFunc( animationSpeed, update, 0 );
    /* start main loop */
    glutMainLoop();

    free( points );
    return 0;
}

 /************************************************************************
   Function: init
   Author: Charles Bonn and Christian Sieh
   Description: The main initilizations for GLUT
   Parameters: void
 ************************************************************************/
void init(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutCreateWindow("Fractals");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( special );
    glutMouseFunc( mouseclick );
    glutMotionFunc( mousedrag );

    // Set color of display window to white
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

 /************************************************************************
   Function: display
   Author: Charles Bonn and Christian Sieh
   Description: The main display function for the program that draws the
                fractal to the screen using the points vector. 
   Parameters: void
 ************************************************************************/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(view.change)
    {
        changeView(view, cmplx);
        if(!juliaSet)
        {
            juliaInit(points, comPoint, cmplx, parallel);
        }
        else
        {
             mandelInit(points, cmplx, parallel);
        }
        
	    setColorMap(points);

        // Use the current viewport coordinates to reshape after we
        // zoom or pan
        GLint nViewport[4];
        glGetIntegerv(GL_VIEWPORT, nViewport);
        reshape(nViewport[1], nViewport[3]);

        view.change = false;
    } 

    // Draw the fractal
    for(int i = 0; i < 1000000; i++)
    {
        plotPoint(points[i]);
    }

    xOffset = 0;
    yOffset = 0;

    glutSwapBuffers();
    glFlush ( );
}

 /************************************************************************
   Function: update
   Author: Charles Bonn 
   Description: The animation loop for the mandelbrot, calls animation in
		color class  
   Parameters:
        int value - 
 ************************************************************************/
void update( int value )
{
    if( animation )
    	animateColor(points);

    glutPostRedisplay();
    glutTimerFunc( animationSpeed, update, 0 );
}

 /************************************************************************
   Function: reshape
   Author: Charles Bonn and Christian Sieh
   Description: The GLUT function that handles when the window is resized.  
   Parameters:
        GLint newWidth - The width value after the window has been resized
		GLint newHeight - The height value after the window has been resized.
 ************************************************************************/
void reshape(GLint newWidth, GLint newHeight)
{
    // Maintain an aspect ration of 1.0, assuming that width
    // of complex window = height of complex window.
    glViewport(0, 0, newHeight, newHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(cmplx.xCMin, cmplx.xCMax , cmplx.yCMin, cmplx.yCMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

 /************************************************************************
   Function: display
   Author: Charles Bonn and Christian Sieh
   Description: This function handles all the key presses that are not
                GLUT special key presses. 
   Parameters: 
        unsigned char key - The value of the key that is pressed.
		int x - The x coordinate for where the mouse is when the key is
                pressed.
		int y - The y coordinate for where the mouse is when the key is
                pressed.
 ************************************************************************/
void keyboard( unsigned char key, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;

    // process keypresses
    switch ( key )
    {
        // Escape quits program
        case EscapeKey:
            exit( 0 );
            break;

	    // key: j - switches between julia and mandelbrot sets
        case 106: 
            if(juliaSet)
            {
                // Get the origin of the screen so our point
                // is in the correct quadrant
                int xOrigin = ScreenWidth / 2;
                int yOrigin = ScreenHeight / 2;

                x = x - xOrigin;
                y = y - yOrigin;

                // Convert the pixel point into a a point in the complex plane
                comPoint.x = (cmplx.cW / ScreenWidth) * x;
                comPoint.y = (cmplx.cH / ScreenHeight) * y;

                juliaInit(points, comPoint, cmplx, parallel);
                setColorMap(points);
                juliaSet = false;
            }
            else
            {
                mandelInit(points, cmplx, parallel);
        	    setColorMap(points);
                juliaSet = true;
            }
            glutPostRedisplay();
            break;

	    // key: c - change color map
	    case 99:
	        swapColor(points);
	        glutPostRedisplay();
	        break;

	    // key: a - animate color map
        case 97:
	        if( !animation )
            	animation = true;
	        else
		        animation = false;
            glutPostRedisplay();
	        break;

        // key: q - switch between sequential and parallel
        case 113:
            if(parallel)
                parallel = false;
            else
                parallel = true;
            glutPostRedisplay();
            break;

	    // key: r - generate random color map
	    case 114:
            randomColorMap(points);
            glutPostRedisplay();
	        break;

	    // key: - - zoom out
	    case 45:
	        if( view.z > 1 )
	        {
	            view.z -= .02;
		        view.change = true;
            }
	        glutPostRedisplay();
	        break;

	    // key: = - alt for + on laptops
	    case 61:
	    // key: + - zoom in
	    case 43:
		    if( view.z < 21556.6 )
		    {
	            view.z += .02 ;
	            view.change = true;
            }
	        glutPostRedisplay();
	        break;

        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
    }
}

 /************************************************************************
   Function: special
   Author: Charles Bonn and Christian Sieh
   Description: This function handles special GLUT keypresses, but we
                are only using it for the up, down, left, and right arrow
                keys. This is used to handle panning around the scene. 
   Parameters: 
        int key - The key value that was pressed
		int x - The x coordinate for the mouse when the key is pressed
		int y - The y coordinate for the mouse when the key is pressed
 ************************************************************************/
void special( int key, int x, int y )
{
    // process keypresses
    switch ( key )
    {
        case GLUT_KEY_LEFT:
            view.x += .01;
	        view.change = true;
            break;
        case GLUT_KEY_RIGHT:;
            view.x -= .01;
	        view.change = true;
            break;
        case GLUT_KEY_UP:
            view.y -= .01;
            view.change = true;
            break;
        case GLUT_KEY_DOWN:
            view.y += .01;
            view.change = true;
            break;
    }

    glutPostRedisplay();
}

 /************************************************************************
   Function: mouseclick
   Author: Charles Bonn and Christian Sieh
   Description: handles mouse clicks   
   Parameters: 
        int button - Which mouse button was pressed
		int state - The state of mouse button
  ************************************************************************/     
void mouseclick(int button, int state, int x, int y)
{
    y = ScreenHeight - y;

	switch( button )
     {
        // Zoom in
        case 3:
		    if( view.z < 21556.6 )
		    {
	            view.z += .02 ;
	            view.change = true;
            }
            break;

        // Zoom Out
        case 4:
	        if( view.z > 1 )
	        {
	            view.z -= .02;
		        view.change = true;
            }
            break;

        // Left mouse click
        case GLUT_LEFT_BUTTON:
            // Store  mouseX and mouseY in case of click and drag
	        if ( state == GLUT_DOWN )
            {
                mouseX = x;
                mouseY = y;	    
            }
            break;
    }
}

 /************************************************************************
   Function: mousedrag
   Author: Christian Sieh
   Description: GLUT motionfunc that handles when the mouse is clicked and 
                dragged across the screen to get the mouse position.
   Parameters: 
		int x - The x coordinate of where the mouse is currently
		int y - The y coordinate of where the mouse is currently
 ************************************************************************/
void mousedrag(int x, int y)
{
    y = ScreenHeight - y;

    // Get ratio of complex coords to pixel coords
    float xScale = cmplx.cW / (ScreenWidth);
    float yScale = cmplx.cH / (ScreenHeight);

    // Get the diff from where the mouse was clicked to where it was dragged
    // Scale to complex coords
    // Mulitply by .01 to slow down panning
    view.x += (mouseX - x) * xScale * .01;
    view.y += (mouseY - y) * yScale * .01;

    view.change = true;
}
