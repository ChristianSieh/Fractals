 /************************************************************************
   Program: 
   Author: 
   Class:
   Instructor:
   Date:
   Description:    (program requirements)
   Input:
   Output:
   Compilation instructions:
   Usage:
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
#include "Julia.h"
#include "Colors.h"
#include "Util.h"

using namespace std;

// Set initial size of display window
GLsizei ScreenWidth = 600, ScreenHeight = 600;

// Set coordinate limits in complex plane
bool juliaSet = true;
vector<point> points;

// keypresses
const int EscapeKey = 27;

//Global varables
double zoomVal = 0;


/*********************** function prototypes ***************************/
void init( void );
void initRendering();
void display( void );
void reshape( GLint newWidth, GLint newHeight );
void keyboard( unsigned char key, int x, int y );
void special( int key, int x, int y );
void mouseclick( int button, int state, int x, int y );
void mousedrag( int x, int y );

 /************************************************************************
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    init();

    if(juliaSet)
    {
        juliaInit(points);
    }
    else
    {
        mandelInit(points);
	    setColorMap(points);
	    //cerr << " before main loop points: " << points.size() << endl;
    }
    glutMainLoop();

    return 0;
}

 /************************************************************************
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
void init(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );// | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutCreateWindow("Fractals");
    //initRendering();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( special );
    glutMouseFunc( mouseclick );

    // Set color of display window to white
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

 /************************************************************************
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //cerr << "preplot: " << points.size() << endl;
    for(unsigned int i = 0; i < points.size(); i++)
    {
        plotPoint(points[i]);
    }
    //cerr << "end plot" << endl;
    glutSwapBuffers();
    glFlush ( );
}

 /************************************************************************
   Function:
   Author:
   Description:
   Parameters:
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
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
// callback function that tells OpenGL how to handle keystrokes
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
        	    setColorMap(points);
                juliaSet = false;
            }
            else
            {
                juliaInit(points);
                juliaSet = true;
            }
            glutPostRedisplay();
            break;
	// key: c - change color map
	case 99:
	    swapColor(points); 
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
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
// callback function that tells OpenGL how to handle keystrokes
// used to move OpenGL bitmap string with arrow keys
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
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
// callback function for mouse button click events
void mouseclick( int button, int state, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;

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
}




