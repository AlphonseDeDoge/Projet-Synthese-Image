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
//#include "shader.hpp"
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

//souris
char press;
int anglex, angley, xold, yold;

//buffers
GLuint buffers;

//Fonctions d'initialisation
void initGL(int* argc,char **argv);
void initBuffer(int n);
//Fonctions affichage
void display();
void reshape(int x, int y);
void idle();
//Fonctions interaction
void keyboard(unsigned char key, int x, int y);
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
//Formes
void draw();
void drawAxes();
//Gestion des elements
#define SIZE_ELEMENTS 100000
int indexElements = 0;
BaseVBO* elements[SIZE_ELEMENTS];
void addElements(BaseVBO* elt);
void removeElements(BaseVBO* elt);

Field* f;
Point* p;
Particle* pp;

Hyperboloide* h;

int main(int argc,char **argv)
{
    initGL(&argc, argv);
    initBuffer(1);
    srand(time(NULL));

    //Instanciation des objets
    //Hyperboloide* h = new Hyperboloide(buffers);
    //h->explain();
    //addElements(h);
    //addElements(new Hyperboloide(buffers));
    f = new Field(2, buffers);
    f->setWind(0.3,0.8,0.1);
    addElements(f);
    p = new Point(0.8,0.2,2);
    pp = new Particle();

    f->containsDebug(p);
    //addElements(new Particle(buffers));

    // Entree dans la boucle principale glut
    glutMainLoop();

    return 0;
}

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

void addElements(BaseVBO* elt)
{
    if(indexElements < SIZE_ELEMENTS && elt != 0 && elt->getBuffers() != 0)
    {
        elements[indexElements] = elt;
        indexElements++;
    }
}

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
    //printf("taille:%d\n", indexElements);
}
void initGL(int* argc, char **argv)
{
    //initialisation de glut et creationde la fenetre
    glutInit(argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(originX, originY);
    glutInitWindowSize(width, height);
    glutCreateWindow(title);
    glewInit();

    // Initialisation d'OpenGL
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);

    // enregistrement des fonctions de rappel
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutIdleFunc(idle);
}

void initBuffer(int n)
{
    glGenBuffers(n, &buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers);
}

void display()
{
    // effacement de l'image avec la couleur de fond
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 3, -3, 3, -3, 3);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glLoadIdentity();

    gluLookAt(0.0,0.0,1,0.0,0.0,0.0,0.0,1,0.0);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    draw();
    drawAxes();

    //On echange les buffers
    glutSwapBuffers();
}

void drawAxes()
{
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 0,1.0);
    glEnd();
    glFlush();
}

void idle()
{
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'p': // display du carre plein
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glutPostRedisplay();
            break;
        case 'f': // display en mode fil de fer
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glutPostRedisplay();
            break;
        case 's' : // display en mode sommets seuls
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            glutPostRedisplay();
            break;
        case 'd':
            glEnable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        case 'D':
            glDisable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        case 'q' : //la key 'q' permet de quitter le programme
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

void mouse(int button, int state, int x, int y)
{
    // si on appuie sur le bouton gauche
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        press = 1; // le booleen press passe a 1 (vrai)
        xold = x; // on sauvegarde la position de la souris
        yold=y;
    }
    //si on relache le bouton gauche
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        press=0; //le booleen press passe a 0 (faux)
    }
}

void mousemotion(int x, int y)
{
    if (press) // si le bouton gauche est press
    {
        /* on modifie les angles de rotation de l'objet
        en fonction de la position actuelle de la souris et de la derniere
        position sauvegardee */
        anglex=anglex+(x-xold);
        angley=angley+(y-yold);
        glutPostRedisplay(); // on demande un rafraichissement de l'display
    }

    xold=x; // sauvegarde des valeurs courante de le position de la souris
    yold=y;
}
