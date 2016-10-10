#include "Util.h"

void plotPoint (complexNum z)
{
    glColor3f (0.0, 0.0, 1.0); // Set point color blue.

	glBegin (GL_POINTS);
	    glVertex2f (z.x, z.y);
	glEnd ( );
}
