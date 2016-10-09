#include "Util.h"

void plotPoint (complexNum z)
{
	glBegin (GL_POINTS);
	glVertex2f (z.x, z.y);
	glEnd ( );
}
