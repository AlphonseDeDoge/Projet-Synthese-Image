#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "BaseVBO.h"

#ifndef HYPERBOLOIDE_H
#define HYPERBOLOIDE_H

class Hyperboloide: public BaseVBO
{
    public:
        Hyperboloide();
        Hyperboloide(const GLuint&  buffers);
        void fillId();
        void fillVertex();
        void fillColor();
        void explain();
        int getN();
        void update();
    private:
        int n;
        float rayon;
        float hauteur;
        float decalage;
};

#endif
