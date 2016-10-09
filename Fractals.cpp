#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Mandel.h"
#include "Julia.h"
#include "Util.h"

using namespace std;

// Set initial size of display window
GLsizei ScreenWidth = 600, ScreenHeight = 600;

// Set coordinate limits in complex plane
bool juliaSet = false;

// keypresses
const int EscapeKey = 27;

// OpenGL callback function prototypes
void init( void );
void display( void );
void reshape( GLint newWidth, GLint newHeight );
void keyboard( unsigned char key, int x, int y );
void special( int key, int x, int y );
void mouseclick( int button, int state, int x, int y );
void mousedrag( int x, int y );

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    init();

    glutMainLoop();

    return 0;
}

void init(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
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

void display(void)
{
    if(juliaSet)
    {
        GLint numPoints = 10000; // Set number of points to be plotted.
        complexNum lambda = { 3.0, 0.0 }; // Set complex value for lambda.
        complexNum z0 = { 1.5, 0.4 }; // Set initial point in complex plane.

        glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

        glColor3f (0.0, 0.0, 1.0); // Set point color blue.

        selfSqTransf(lambda, z0, numPoints);
    }
    else
    {
	    /* Set number of x and y subdivisions and the max iterations. */
	    GLint nx = 1000, ny = 1000, maxIter = 1000;
	    glClear (GL_COLOR_BUFFER_BIT);
	    /* Clear display window. */
	    mandelbrot (nx, ny, maxIter);
    }

    glFlush ( );
}

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
        case 106:
            if(juliaSet)
                juliaSet = false;
            else
                juliaSet = true;
            glutPostRedisplay();
            break;
        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
    }
}

// callback function that tells OpenGL how to handle keystrokes
// used to move OpenGL bitmap string with arrow keys
void special( int key, int x, int y )
{
    // process keypresses
    switch ( key )
    {
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:;
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
    }
    glutPostRedisplay();
}

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




