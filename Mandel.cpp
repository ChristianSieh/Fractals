#include "Mandel.h"

/* Calculate the square of a complex number. */
complexNum complexSquare (complexNum z)
{
	complexNum zSquare;
	zSquare.x = z.x * z.x - z.y * z.y;
	zSquare.y = 2 * z.x * z.y;
	return zSquare;
}

GLint mandelSqTransf (complexNum z0, GLint maxIter)
{
	complexNum z = z0;
	GLint count = 0;

	/* Quit when z * z > 4 */
	while ((z.x * z.x + z.y * z.y <= 4.0) && (count < maxIter)) {
		z = complexSquare (z);
		z.x += z0.x;
		z.y += z0.y;
		count++;
	}
	return count;
}

void mandelbrot (GLint nx, GLint ny, GLint maxIter, vector<complexNum> &points)
{
	complexNum z, zIncr;
	color ptColor;
	GLint iterCount;

	zIncr.x = complexWidth / GLfloat (nx);
	zIncr.y = complexHeight / GLfloat (ny);

	for (z.x = xComplexMin; z.x < xComplexMax; z.x += zIncr.x)
		for (z.y = yComplexMin; z.y < yComplexMax; z.y += zIncr.y) {
			iterCount = mandelSqTransf (z, maxIter);
			if (iterCount >= maxIter)
				/* Set point color to black. */
				ptColor.r = ptColor.g = ptColor.b = 0.0;
			else if (iterCount > (maxIter / 8)) {
				/* Set point color to orange. */
				ptColor.r = 1.0;
				ptColor.g = 0.5;
				ptColor.b = 0.0;
			}
			else if (iterCount > (maxIter / 10)) {
				/* Set point color to red. */
				ptColor.r = 1.0;
				ptColor.g = ptColor.b = 0.0;
			}
			else if (iterCount > (maxIter /20)) {
				/* Set point color to dark blue. */
				ptColor.b = 0.5;
				ptColor.r = ptColor.g = 0.0;
			}
			else if (iterCount > (maxIter / 40)) {
				/* Set point color to yellow. */
				ptColor.r = ptColor.g = 1.0;
				ptColor.b = 0.0;
			}
			else if (iterCount > (maxIter / 100)) {
				/* Set point color to dark green. */
				ptColor.r = ptColor.b = 0.0;
				ptColor.g = 0.3;
			}else {
				/* Set point color to cyan. */
				ptColor.r = 0.0;
				ptColor.g = ptColor.b = 1.0;
			}
			/* Plot the color point. */
			glColor3f (ptColor.r, ptColor.g, ptColor.b);
			points.push_back(z);
	}
}

void mandelInit(vector<complexNum> &points)
{
    /* Set number of x and y subdivisions and the max iterations. */
    GLint nx = 1000, ny = 1000, maxIter = 1000;
    glClear (GL_COLOR_BUFFER_BIT);

    points.empty();

    /* Clear display window. */
    mandelbrot (nx, ny, maxIter, points);
}

