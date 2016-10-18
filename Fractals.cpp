 /************************************************************************
   Program: Fractals
   Author: Charles Bonn and Christian Sieh
   Class: csc433
   Instructor: John Weiss
   Date: 10/27/2016
   Description:    (program requirements)
   Input: None
   Output: Graphical window with Mandelbrot set
   Compilation instructions: run make file
   Usage: ./Fractals
   Known bugs/missing features:
   Modifications:
   Date                Comment            
   ----    ------------------------------------------------
 ************************************************************************/

#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Mandel.h"
//#include "Julia.h"
#include "Colors.h"
#include "Util.h"

using namespace std;

// Set initial size of display window
GLsizei ScreenWidth = 600, ScreenHeight = 600;

// Set coordinate limits in complex plane
bool juliaSet = false;
bool animation = false;
int animationSpeed = 100;
vector<point> points;

// keypresses
const int EscapeKey = 27;

//Global varables
double zoomVal = 0;


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
   Function: main
   Author: Charles Bonn and Christian Sieh
   Description: main function of the program. makes initilization calls
		and starts the main glut loop
   Parameters: int argc - number of arguments
	       char* argv[] - argument values
 ************************************************************************/
int main(int argc, char* argv[])
{
    /* main initilizations */
    glutInit(&argc, argv);
    init();
    /* initilize points */
    mandelInit(points);
    setColorMap(points);
    /* start timer */
    glutTimerFunc( animationSpeed, update, 0 );
    /* start main loop */
    glutMainLoop();

    return 0;
}

 /************************************************************************
   Function: init
   Author: Charles Bonn and Christian Sieh
   Description: main initilizations for the GUI
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

    // Set color of display window to white
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

 /************************************************************************
   Function: display
   Author: Charles Bonn and Christian Sieh
   Description: main display loop for the window.  
   Parameters: void
 ************************************************************************/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(unsigned int i = 0; i < points.size(); i++)
    {
        plotPoint(points[i]);
    }
    glutSwapBuffers();
    glFlush ( );
}

 /************************************************************************
   Function: update
   Author: Charles Bonn 
   Description: animation loop for the mandelbrot, calls animation in
		color class  
   Parameters: void
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
   Description: main reshaping loop for the window.  
   Parameters: void
 ************************************************************************/
void reshape(GLint newWidth, GLint newHeight)
{
    // Maintain an aspect ration of 1.0, assuming that width
    // of complex window = height of complex window.
    glViewport(0, 0, newHeight, newHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

 /************************************************************************
   Function: display
   Author: Charles Bonn and Christian Sieh
   Description: handles keyboard presses   
   Parameters: unsigned char key - value of key press
		int x - x coord on screen
		int y - y coord on screen
 ************************************************************************/
void keyboard( unsigned char key, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
    cerr << "keypress: " << key << " (" << int( key ) << ") at (" << x << "," << y << ")\n";

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
                mandelInit(points);
                juliaSet = false;
            }
            else
            {
                //juliaInit(points);
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
	// key: r - generate random color map
	case 114:
	    randomColorMap(points);
            glutPostRedisplay();
	    break;
	// key: h - prints debug help
	case 104:
	    cerr << "size of points: " << points.size() << "\n";
	    cerr << "zoomVal: " << zoomVal << endl;
	    //printColorMap();
	    break;
	// key: - - zoom out
	case 45:
	    if( zoomVal > 0 )
	    {
	        zoomVal -= 1;
            }
	    glutPostRedisplay();
	    break;
	// key: = - alt for + on laptops
	case 61:
	// key: + - zoom in
	case 43:
	    zoomVal += 1;
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
   Description: handles special keypresses  
   Parameters: int key - key press value
		int x -
		int y -
 ************************************************************************/
void special( int key, int x, int y )
{
    // process keypresses
    switch ( key )
    {
        case GLUT_KEY_LEFT:
            for(unsigned int i = 0; i < points.size(); i++)
            {
                points[i].x -= .1;
            }
            break;
        case GLUT_KEY_RIGHT:;
            for(unsigned int i = 0; i < points.size(); i++)
            {
                points[i].x += .1;
            }
            break;
        case GLUT_KEY_UP:
            for(unsigned int i = 0; i < points.size(); i++)
            {
                points[i].y += .1;
            }
            break;
        case GLUT_KEY_DOWN:
            for(unsigned int i = 0; i < points.size(); i++)
            {
                points[i].y -= .1;
            }
            break;
    }
    glutPostRedisplay();
}
 /************************************************************************
   Function: mouseClick
   Author: Charles Bonn and Christian Sieh
   Description: handles mouse clicks   
   Parameters: int button - mouse button
		int state - state of mouse button
		int x - x coord of mouse click
		int y - y coord of mouse click
 ************************************************************************/
void mouseclick( int button, int state, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
`
    unsigned char pick_col[3];
    color rgb;

    // handle mouse click events
    switch ( button )
    {
        case GLUT_LEFT_BUTTON:              // left button
            if ( state == GLUT_DOWN )           // press
                cerr << "mouse click: left press at    (" << x << "," << y << ")\n";
		
            else if ( state == GLUT_UP )        // release
                cerr << "mouse click: left release at  (" << x << "," << y << ")\n";
            break;

        case GLUT_RIGHT_BUTTON:             // right button
            if ( state == GLUT_DOWN )           // press
                cerr << "mouse click: right press at   (" << x << "," << y << ")\n";
            else if ( state == GLUT_UP )        // release
                cerr << "mouse click: right release at (" << x << "," << y << ")\n";
            break;
    }

    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE, pick_col);
    rgb.r = pick_col[0]/255.0;
    rgb.g = pick_col[1]/255.0;
    rgb.b = pick_col[2]/255.0;
    cerr << "R: " << rgb.r << " G: " << rgb.g << " B: " << rgb.b << endl;
 
}




