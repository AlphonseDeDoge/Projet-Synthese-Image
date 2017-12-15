#include "../include/Voxel.h"

/** Constructeur par defaut
*/
Voxel::Voxel()
{
    this->buffers = 0;
    this->position = new Point();
    this->accel = new glm::vec3(0,0,0);
    this->oldWind   = new glm::vec3(0,0,0);
    this->size = 1;
}

/** Constructeur avec parametres
*/
Voxel::Voxel(Point* position, const GLuint &buffers, float size)
{
    this->buffers   = buffers;
    this->size      = size;
    this->position  = position;
    this->accel     = new glm::vec3(0,0,0);
    this->oldWind   = new glm::vec3(0,0,0);
}

/** Produit scalaire avec v (A MODIFIER)
*/
void Voxel::updateVec(glm::vec3* wind)
{
    if(wind->x != oldWind->x || wind->y != oldWind->y || wind->z != oldWind->z)
    {
        float cx = wind->x*size;
        float cy = wind->y*size;
        float cz = wind->z*size;
        float step = size/16;

        this->accel->x = randNumber(cx-step, cx+step);
        this->accel->y = randNumber(cy-step, cy+step);
        this->accel->z = randNumber(cz-step, cz+step);

        oldWind = wind;
    }
}

float Voxel::randNumber(float min, float max)
{
    float r = min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(max-min));
    return r;
}

/** Accesseur pour le vecteur acceleration
*/
glm::vec3* Voxel::getAccel()
{
    return this->accel;
}

/**
*
*/

void Voxel::update()
{

}

void Voxel::fillId()
{

}

void Voxel::fillVertex()
{

}

void Voxel::fillColor()
{

}

void Voxel::explain()
{
    BaseVBO::explain();
    //printf("n:%d \nrayon:%f \nhauteur:%f \ndecalage:%f\n", n, rayon, hauteur, decalage);
}

void Voxel::drawDebug()
{
    float x = this->position->x;
    float y = this->position->y;
    float z = this->position->z;

    float l = this->size;

    glColor3ub(255, 0, 0); //face haute rouge

    /*glBegin(GL_LINE_LOOP);
    glVertex3f(x, y+l, z);
    glVertex3f(x+l, y+l, z);
    glVertex3f(x+l, y+l, z+l);
    glVertex3f(x, y+l, z+l);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(x, y, z);
    glVertex3f(x+l, y, z);
    glVertex3f(x+l, y, z+l);
    glVertex3f(x, y, z+l);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(x, y+l, z);
    glVertex3f(x, y, z);

    glVertex3f(x+l, y+l, z);
    glVertex3f(x+l, y, z);

    glVertex3f(x+l, y+l, z+l);
    glVertex3f(x+l, y, z+l);

    glVertex3f(x, y+l, z+l);
    glVertex3f(x, y, z+l);
    glEnd();

    glColor3ub(0, 255, 0); //vecteur

    float x_ = x+size/2;
    float y_ = y+size/2;
    float z_ = z+size/2;

    glBegin(GL_LINES);
    glVertex3f(x_, y_, z_);
    glVertex3f(x_+accel->x, y_+accel->y, z_+accel->z);
    glEnd();*/
}

bool Voxel::contains(Point* point)
{
    return (
        (point->x >= position->x && point->x < (position->x + size)) &&

        (point->y >= position->y && point->y < (position->y + size)) &&

        (point->z >= position->z && point->z < (position->z + size))
    );
}

bool Voxel::contains(Particle* particle)
{
    return contains(particle->getPosition());
}
