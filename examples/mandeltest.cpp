#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double dividecubesby  = 500;
double left = -2.0;
double right = 2.0;
double bottom = -2.0;
double top = 2.0;
int maxiteration = 128;
int zoomlevel = 3;
double baseSize = 4.0;
double SizeReal;
double SizeImage;
double xco=0.0;
double yco=0.0;

void whatcoordinate(int x,int y)
{
    int xp=x;
    int yp=y;
    double delta1 = (right-left);
    double tempx;   
    double tempy;
    double delta=0.0;   
    double l = dividecubesby/2;

    delta = delta1/dividecubesby;

    if((xp > l) && (yp < l))
    {
        tempx = xp*delta;
        tempy = yp*delta;

        xco = right - tempx;
        yco = top - tempy;

        if(xco <0)xco=xco*-1;
        if(yco <0)yco=yco*-1;
    }
    else if( (x < l) && (y < l))
    {
        tempx = xp*delta;
        tempy = yp*delta;

        xco = right - tempx;
        yco = top - tempy;

        if(xco >0)xco=xco*-1;
        if(yco <0) yco =yco*-1;
    }
    else if((x < l) && (y > l))
    {
        tempx = xp*delta;
        tempy = yp*delta;

        xco = right - tempx;
        yco = top - tempy;

        if(xco >0)xco=xco*-1;
        if(yco >0)yco=yco*-1;
    }
    else if((x > l) && (y > l))
    {
        tempx = xp*delta;
        tempy = yp*delta;

        xco = right - tempx;
        yco = right - tempy;

        if(xco <0)xco=xco*-1;
        if(yco >0)yco=yco*-1;
    }
}

void keyPressed(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'z':
        printf("z pressed  x= %d, y= %d \n",x,y);

        whatcoordinate(x,y);

        SizeReal = (pow(2.0, (-zoomlevel)))*baseSize;
        SizeImage = (pow(2.0, (-zoomlevel)))*baseSize;

        baseSize = right-left;

        left   =  xco- (SizeReal/2);
        right  =  xco + (SizeReal/2);
        bottom = yco - (SizeReal/2);
        top    = yco + (SizeReal/2);    
        dividecubesby = dividecubesby+500;      
        maxiteration  = maxiteration+500; 
        zoomlevel=zoomlevel+1;

        glutPostRedisplay();

        break;
    }
}

int mandtest(double Cr, double Ci)
{
    double Zr = 0.0;
    double Zi = 0.0;
    int times = 0;
    double temp;
    Zr = Zr+Cr;
    Zi = Zi+Ci;

    while ((((Zr*Zr)+(Zi*Zi))<=4) && (times < maxiteration))
    {
        temp = (Zr*Zr)-(Zi*Zi);
        Zi = 2*Zr*Zi;

        Zr = temp+Cr;
        Zi = Zi+Ci;                

        times = times+1;  

    }

    return times;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,1.0f,1.0f);
    double deltax = ((right - left)/(dividecubesby-1));//this means length/700 
    double deltay = ((top- bottom)/(dividecubesby-1));// this means length/700

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left,right,bottom,top);
    glBegin(GL_POINTS);

    for(double x= left;x<=right;x += deltax )
    {
        for(double y= bottom; y<=top;y +=  deltay )
        {
            if((mandtest(x,y))==maxiteration)
            {
                glColor3f(1.0f,1.0f,1.0f); 
                glVertex2f(x,y);
            }
            else 
            {
                glColor3f((float)mandtest(x,y)/10,0.0f,(float)mandtest(x,y)/30);
                glVertex2f(x,y);
            }
        }
    }
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int main(int argc, char ** argv)
{   
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(dividecubesby,dividecubesby);
    glutCreateWindow("A Simple OpenGL Windows Application with GLUT");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutMainLoop();

    return 0;
}
