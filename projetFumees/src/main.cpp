#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <vector>
// Include GLM
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>
//Model
#include "../include/BaseVBO.h"
#include "../include/Point.h"
#include "../include/Voxel.h"
#include "../include/Particle.h"
#include "../include/Field.h"
#include "../include/Obstacle.h"
#include "../include/Hyperboloide.h"
#ifndef NULL
#define NULL 0
#endif // NULL
using namespace std;
using namespace glm;

char* title="Projet Fumée";
int width = 500;
int height = 500;
int originX = 200;
int originY = 200;

//mouse
char press;
int anglex, angley, xold, yold;

//buffers
GLuint buffers;

//Initialize functions
void initGL(int* argc,char **argv);
void initBuffer(int n);
//Display functions
void display();
void reshape(int x, int y);
void idle();
//Interactive functions
void keyboard(unsigned char key, int x, int y);
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
//Shapes
void draw();
void drawAxes();
//Elements handler
#define SIZE_ELEMENTS 100000
int indexElements = 0;
BaseVBO* elements[SIZE_ELEMENTS];
void addElements(BaseVBO* elt);
void removeElements(BaseVBO* elt);

Field* f;
Point* p;
Particle* pp;

int main(int argc,char **argv)
{
    initGL(&argc, argv);
    initBuffer(1);
    srand(time(NULL));

    f = new Field(2, buffers);
    f->setWind(0.3,0.8,0.1);
    addElements(f);
    p = new Point(0.8,0.2,2);
    pp = new Particle();

    f->containsDebug(p);

    // Entering the glut main loop
    glutMainLoop();

    return 0;
}

// Call to
void draw()
{
    //f->update();
    //f->drawDebug();
    //p->drawDebug();
    for(int i=0; i<indexElements ;i++)
    {
        elements[i]->update();
        elements[i]->draw();
    }
    //f->drawDebug();

}

// Adding one BaseVBO object to a matrix of elements to be drawn
void addElements(BaseVBO* elt)
{
    if(indexElements < SIZE_ELEMENTS && elt != 0 && elt->getBuffers() != 0)
    {
        elements[indexElements] = elt;
        indexElements++;
    }
}

// Removing one BaseVBO object from the elements matrix
void removeElements(BaseVBO* elt)
{
    if(elt != 0)
    {
        for(int i=(indexElements-1); i>= 0 ; i--)
        {
            if(elements[i] == elt)
            {
                for(int j=i; j<(indexElements-1) ; j++)
                {
                    elements[j] = elements[j+1];
                }
                if(indexElements > 0)
                {
                    indexElements--;
                }
            }
        }
    }
}

// overall initialization
void initGL(int* argc, char **argv)
{
    // Glut initialization and window generation
    glutInit(argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(originX, originY);
    glutInitWindowSize(width, height);
    glutCreateWindow(title);
    glewInit();

    // OpenGL initialization
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutIdleFunc(idle);
}

// Buffer init
void initBuffer(int n)
{
    glGenBuffers(n, &buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers);
}

// Field of view display initialization
void display()
{
    // Recast of the background for the redisplay

    // Field of vieW
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 3, -3, 3, -3, 3);

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glLoadIdentity();

    // Camera
    gluLookAt(0.0,0.0,1,0.0,0.0,0.0,0.0,1,0.0);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    // Call to draw functions
    draw();
    drawAxes();

    //Swaping buffers
    glutSwapBuffers();
}

// Drawing the x, y, z axis
void drawAxes()
{
    // x axis in red
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(1, 0,0.0);
    glEnd();
    // y axis in green
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 1,0.0);
    glEnd();
    // z axis in blue
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 0,1.0);
    glEnd();
    glFlush();
}

// Automatic animation/redisplay call
void idle()
{
  glutPostRedisplay();
}

// Keyboard actions handler
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'p': // full shape display
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glutPostRedisplay();
            break;
        case 'f': // string display
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glutPostRedisplay();
            break;
        case 's' : // dot display
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            glutPostRedisplay();
            break;
        case 'd': // Enabling depth
            glEnable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        case 'D': // Disabling depth
            glDisable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        case 'q' : // To quit the program
            exit(0);
    }
}


void reshape(int x, int y)
{
    if (x<y)
    {
        glViewport(0,(y-x)/2,x,x);
    }
    else
    {
        glViewport((x-y)/2,0,y,y);
    }
}

// Mouse button actions handler
void mouse(int button, int state, int x, int y)
{
    // Left clic pressing
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        press = 1; // boolean goes to 1 (true)
        xold = x; // saving cursor position
        yold=y;
    }
    // Left clic releasing
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        press=0; // boolean goes to 0 (false)
    }
}

// Mouse motion handler
void mousemotion(int x, int y)
{
    if (press) // if left clic is pressed
    {
        /* asigning new object rotation depending on the actual
        cursor position compared to the last one saved */
        anglex=anglex+(x-xold);
        angley=angley+(y-yold);
        glutPostRedisplay(); // redisplay call
    }

    // Current position of the cursor
    xold=x;
    yold=y;
}
