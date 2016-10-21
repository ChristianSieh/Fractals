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
#include "Julia.h"
#include "Colors.h"
#include "Util.h"

using namespace std;

// Set initial size of display window
GLsizei ScreenWidth = 800, ScreenHeight = 600;

bool juliaSet = false;
bool animation = false;
int animationSpeed = 100;
int mouseX = 0;
int mouseY = 0;
int xOffset;
int yOffset;
int zoomX;
int zoomY;
vector<point> points;
vector<point> jpoints;
// keypresses
const int EscapeKey = 27;

//Global varables
double zoomVal = 0;
viewMod view;

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
   Description: The main function of the program which makes initilization 
                calls and starts the main glut loop
   Parameters: 
           int argc - number of arguments
	       char* argv[] - argument values
 ************************************************************************/
int main(int argc, char* argv[])
{
    /* main initilizations */
    glutInit(&argc, argv);
    init();
    view.zoom = 1;
    
    /* initilize points */
    if(juliaSet)
    {
        point initialPoint;
        initialPoint.x = 100;
        initialPoint.y = 100;

        complexNum comPoint;
        comPoint.x = (complexWidth / ScreenWidth) * initialPoint.x;
        comPoint.y = (complexHeight / ScreenHeight) * initialPoint.y;
        juliaInit(points, comPoint);
        setColorMap(points);
        juliaSet = false;
    }
    else
    {
        mandelInit(points, view);
	    setColorMap(points);
        juliaSet = true;
    }
    /* start timer */
    glutTimerFunc( animationSpeed, update, 0 );
    /* start main loop */
    glutMainLoop();

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
    float xScale = complexWidth / (ScreenWidth * 10);
    float yScale = complexHeight / (ScreenHeight * 10);

    glClear(GL_COLOR_BUFFER_BIT);
 

    for(unsigned int i = 0; i < points.size(); i++)
    {
        points[i].x += (xOffset * xScale);
        points[i].y += (yOffset * yScale);
        plotPoint(points[i]);
    }

    glPushMatrix();
  
    glLoadIdentity();
    glColor3f( 1.0, 1.0, 1.0 );
    //glTranslatef( 50, 50, 0);
    glRecti( ScreenWidth - 100 , ScreenHeight - 100, ScreenWidth,ScreenHeight );
    //glPushMatrix(); 
    //glPopMatrix();

    glPopMatrix();
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

    gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
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
<<<<<<< HEAD
                complexNum comPoint;
                int xOrigin = ScreenWidth / 2;
                int yOrigin = ScreenHeight / 2;

                x = x - xOrigin;
                y = y - yOrigin;

                comPoint.x = (complexWidth / ScreenWidth) * x;
                comPoint.y = (complexHeight / ScreenHeight) * y;

                juliaInit(points, comPoint);
                setColorMap(points);
=======
                mandelInit(points, view);
        	    setColorMap(points);
>>>>>>> 39444fb7e7e74205d23ddc3eecf0b37dff1132cf
                juliaSet = false;
            }
            else
            {
                mandelInit(points);
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
	        if( view.zoom > 1 )
	        {
	            view.zoom /= 1;
                }
	        glutPostRedisplay();
	        break;

	    // key: = - alt for + on laptops
	    case 61:

	    // key: + - zoom in
	    case 43:
	        //ew.zoom *= pow() ;
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
   Function: mouseclick
   Author: Charles Bonn and Christian Sieh
   Description: handles mouse clicks   
   Parameters: 
        int button - Which mouse button was pressed
		int state - The state of mouse button
		int x - The x coordinate of where the mouse was clicked
		int y - The y coordinate of where the mouse was clicked
 ************************************************************************/
void mouseclick( int button, int state, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;

    unsigned char pick_col[3];
    color rgb;

    // handle mouse click events
    switch ( button )
    {
        case GLUT_LEFT_BUTTON:
            if ( state == GLUT_DOWN )
            {
                mouseX = x;
                mouseY = y;
                cerr << "mouse click: left press at    (" << x << "," << y << ")\n";		    
            }
            else if ( state == GLUT_UP )
            {
                mouseX = 0;
                mouseY = 0;
                cerr << "mouse click: left release at  (" << x << "," << y << ")\n";
            }
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

    xOffset = x - mouseX;
    yOffset = y - mouseY;
}




