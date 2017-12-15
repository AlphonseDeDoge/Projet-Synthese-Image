#include "../include/Point.h"
#include "../include/Particle.h"

/** Constructeur par defaut
*/
Particle::Particle()
{
    this->lifeTime = 50;
    this->timeLived = 0;
    this->position = new Point();
    this->speed = new glm::vec3(0.01,0.01,0.01);
    this->accel = new glm::vec3(0,0,0);
    this->mass = 0.;
    this->density = 0.;

    this->n = 8;
    this->rayon = 0.5;
    this->hauteur = 0.5;
    this->decalage = 0.0;
    this->buffers = 0;
    this->initId(n*6);
    this->initVertex(n*6);
    this->initColor(n*6);
    this->fill();
}

/** Constructeur avec parametres
*/
Particle::Particle(int life, Point* p, glm::vec3* speed, glm::vec3* accel, float mass, float density)
{
    this->lifeTime = life;
    this->timeLived = 0;
    this->position = p;
    this->speed = speed;
    this->accel = accel;
    this->mass = mass;
    this->density = density;

    this->n = 8;
    this->rayon = 0.05;
    this->hauteur = 0.05;
    this->decalage = 0.0;
    this->buffers = 0;
    this->initId(n*6);
    this->initVertex(n*6);
    this->initColor(n*6);
    this->fill();
}

/** Constructeur avec parametres
*/
Particle::Particle(const GLuint&  buffers, int life, Point* p, glm::vec3* speed)
{
    this->lifeTime = life;
    this->timeLived = 0;
    this->position = p;
    this->speed = speed;

    this->n = 8;
    this->rayon = 0.05;
    this->hauteur = 0.05;
    this->decalage = 0.0;
    this->buffers = buffers;
    this->initId(n*6);
    this->initVertex(n*6);
    this->initColor(n*6);
    this->fill();
}

/** modification du vecteur vitesse
*/
void Particle::calcSpeed(glm::vec3* v)
{
    glm::vec3* a = new glm::vec3(v->x + this->speed->x, v->y + this->speed->y, v->z + this->speed->z);
    *a = glm::normalize(*a);
    a -> x = (a -> x * sqrt(pow(v->x,2) + pow(v->y,2) + pow(v->z,2)))/3;
    a -> y = (a -> y * sqrt(pow(v->x,2) + pow(v->y,2) + pow(v->z,2)))/3;
    a -> z = (a -> z * sqrt(pow(v->x,2) + pow(v->y,2) + pow(v->z,2)))/3;
    this -> speed = a;
}

/** Mise à jour de la durée de vie et déplacement
*/
void Particle::update()
{
    if(isAlive())
    {
        fillVertex();
        timeLived++;
        move();
    }
}

/** Return true si en vie
*/
bool Particle::isAlive()
{
    return (timeLived < lifeTime);
}

Point* Particle::getPosition()
{
    return position;
}

void Particle::move()
{
    this->position->x = this->position->x + this->speed->x;
    this->position->y = this->position->y + this->speed->y;
    this->position->z = this->position->z + this->speed->z;
}

void Particle::drawDebug()
{
    float x = this->position->x;
    float y = this->position->y;
    float z = this->position->z;

    float l = 0.1;

    glColor3ub(255, 0, 0); //face haute rouge
    glPushMatrix();

    glTranslatef(x,y,z);

    glutSolidSphere(0.008,20,20);
    glPopMatrix();

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
    glEnd();*/

}

float Particle::randNumber(float min, float max)
{
    float r = min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(max-min));
    return r;
}

void Particle::resetParticle(float length)
{
    Point* p = new Point(randNumber(0.0,length),0.0,randNumber(0.0,length));

    this->lifeTime = 500;
    this->timeLived = 0;
    this->position = p;
    this->speed = new glm::vec3(0,0.01,0);
}


void Particle::fillId()
{
    int j=0;
    for(int i=0;i<n;i++){
        id[j]=i;
        id[j+1]=(i+1)%n;
        id[j+2]=(n+((i+1)%n));

        id[j+3]=(n+((i+1)%n));
        id[j+4]=(n+(i%n));
        id[j+5]=i;
        j=j+6;
    }
}

void Particle::fillVertex()
{
    float x = this->position->x;
    float y = this->position->y;
    float z = this->position->z;

    int j=0;
    for(int i=0;i<n;i++)
    {
        vertex[j]           =   x + rayon*sin((2*i*M_PI)/n);
        vertex[j+1]         =   y + -hauteur;
        vertex[j+2]         =   z + rayon*cos((2*i*M_PI)/n);

        vertex[3*n+j]       =   x + rayon*sin(((2*i*M_PI)/n)+(float)decalage);
        vertex[3*n+(j+1)]   =   y + hauteur;
        vertex[3*n+(j+2)]   =   z + rayon*cos(((2*i*M_PI)/n)+(float)decalage);

        j=j+3;
    }
}

void Particle::fillColor()
{
    int j=0;
    for(int i=0;i<n;i++){
        float g,b;
        if(i<=n/2){
            g=(float)i/(float)n;
            b=((float)n-(float)i)/(float)n;
        }
        else{
            b=(float)i/(float)n;
            g=((float)n-(float)i)/(float)n;
        }
        color[j]=0;
        color[j+1]=g;
        color[j+2]=b;

        color[3*n+j]=0;
        color[(j+1)+n*3]=g;
        color[(j+2)+n*3]=b;
        j=j+3;
    }
}

void Particle::explain()
{
    BaseVBO::explain();
    printf("n:%d \nrayon:%f \nhauteur:%f \ndecalage:%f\n", n, rayon, hauteur, decalage);
}

int Particle::getN()
{
    return n;
}
