#include "Point.h"

/** Constructeur par defaut
*/
Point::Point()
{
    x = 0.;
    y = 0.;
    z = 0.;
}

/** Constructeur avec parametres
*/
Point::Point(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}


/** Constructeur en copie
*/
Point::Point(const Point& p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

void Point::drawDebug()
{
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    glEnd();
}
