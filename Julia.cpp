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

#include "Julia.h"

 /************************************************************************
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/

void solveQuadraticEq(complexNum lambda, complexNum * z)
{
    GLfloat lambdaMagSq, discrMag;
    complexNum discr;
    static complexNum fourOverLambda = {0.0, 0.0};
    static GLboolean firstPoint = true;

    if(firstPoint)
    {
        // Compute the complex number: 4.0 divided by  lambda.
        lambdaMagSq = lambda.x * lambda.x + lambda.y * lambda.y;
        fourOverLambda.x = 4.0 * lambda.x / lambdaMagSq;
        fourOverLambda.y = -4.0 * lambda.y / lambdaMagSq;
        firstPoint = false;
    }

    discr.x = 1.0 - (z->x * fourOverLambda.x - z->y * fourOverLambda.y);
    discr.y = z->x * fourOverLambda.y + z->y * fourOverLambda.x;
    discrMag = sqrt(discr.x * discr.x + discr.y * discr.y);

    // Update z, checking to avoid the square root of a negative number
    if(discrMag + discr.x < 0)
        z->x = 0;
    else
        z->x = sqrt ((discrMag + discr.x) / 2.0);

    if(discrMag - discr.x < 0)
        z->y = 0;
    else
        z->y = 0.5 * sqrt ((discrMag - discr.x) / 2.0);

    // For half the points use negative root, placing point in quadrant 3.
    if(rand() < RAND_MAX / 2)
    {
        z->x = -z->x;
        z->y = -z->y;
    }

    // When imaginary part of discriminant is negative, point
    // should lie in quadrant 2 or 4, so reverse sign of x.
    if(discr.y < 0)
        z->x = -z->x;

    //  Complete the calculation for the real part of z.
    z->x = 0.5 * (1 - z->x);   
}

 /************************************************************************
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
void selfSqTransf(complexNum lambda, complexNum z, GLint numPoints, vector<complexNum> &points)
{
    GLint k;

    //  Skip the first few points.
    for(k = 0; k < 10; k++)
    {        
        solveQuadraticEq(lambda, &z);
    }
    //  Plot the specified number of transformation points.
    for(k = 0; k < numPoints; k++)
    {
        solveQuadraticEq(lambda, &z);
        points.push_back(z);
    }
}

 /************************************************************************
   Function:
   Author:
   Description:
   Parameters:
 ************************************************************************/
void juliaInit(vector<complexNum> &points)
{
    GLint numPoints = 10000; // Set number of points to be plotted.
    complexNum lambda = { 3.0, 0.0 }; // Set complex value for lambda.
    complexNum z0 = { 1.5, 0.4 }; // Set initial point in complex plane.

    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

    points.empty();

    selfSqTransf(lambda, z0, numPoints, points);
}
