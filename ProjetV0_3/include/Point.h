#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#ifndef POINT_H
#define POINT_H

class Point{
    public:
        float x,y,z;
        Point();
        Point(float x,float y,float z);
        Point(const Point& p);
        void drawDebug();
        float setX(float x);
};
#endif
