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
#include "Util.h"
 /************************************************************************
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
void plotPoint (complexNum z)
{
    glColor3f (0.0, 0.0, 1.0); // Set point color blue.

	glBegin (GL_POINTS);
	    glVertex2f (z.x, z.y);
	glEnd ( );
}
