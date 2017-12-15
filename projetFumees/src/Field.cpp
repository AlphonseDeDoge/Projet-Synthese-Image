#include "../include/Field.h"

/** Define empty functions that will be detailed in daughter classes
*/
void Field::fillId(){}
void Field::fillVertex(){}
void Field::fillColor(){}

/** Default constructor
*/
Field::Field()
{
    this->nbParticles   = 500;
    this->origin    = new Point();
    this->grid      = 0;
    this->step      = 0.1;
    this->length    = 0;
    this->wind      = new glm::vec3();
    this->buffers   = 0;
    this->particles = 0;
    generateMatrix();
    generateParticles();

}

/** Argument constructor, the argument is the length of the field in the 3 axis (x,y,z)
*/
Field::Field(int length)
{
    this->nbParticles   = 500;
    this->length        = length;
    this->step          = 0.1;
    this->origin        = new Point();
    this->grid          = new Voxel*[getGridLength()];
    this->particles     = new Particle*[nbParticles];
    this->wind          = new glm::vec3();
    this->buffers       = 0;
    generateMatrix();
    generateParticles();

}

/** Arguments constructor, first argument is the length of the field in the 3 axis (x,y,z), second is the buffers needed for the VBO
*/
Field::Field(int length, const GLuint &buffers)
{
    this->nbParticles   = 5000;
    this->length    = length;
    this->step      = 0.2;
    this->origin    = new Point();
    this->grid      = new Voxel*[getGridLength()];
    this->particles = new Particle*[nbParticles];
    this->wind      = new glm::vec3();
    this->buffers   = buffers;
    generateMatrix();
    generateParticles();

}

/** Particles generator, with a Point object for each position that is used to generate a particle
*/
void Field::generateParticles()
{
    int i;
    for(i = 0; i < nbParticles; i++)
    {
        Point* p = new Point(randNumber(0.0,length),0.0,randNumber(0.0,length));
        particles[i] = new Particle(buffers, 500, p, new glm::vec3(0,0.01,0));
    }
}

/** Matrix generator, fills a table with voxels that represent small parts of the field
*/
void Field::generateMatrix()
{
    int i = 0;
    for(float x = 0; x < length ; x+=step)
    {
        for(float y = 0; y < length ; y+=step)
        {
            for(float z = 0 ; z < length ; z+=step)
            {
                this->grid[i] = new Voxel(new Point(x,y,z), buffers, step);
                i++;
            }
        }
    }
}

/** Checks if a Point object is in the field
*/
bool Field::contains(Point* p)
{
    int l = Field::getGridLength();

    for(int i=0 ; i<l ; i++)
    {
        if(grid[i]->contains(p))
        {
            return true;
        }
    }
    return false;
}

/** Checks if a particle is in the field (calls the above function contains(Point* p))
*/
void Field::contains(Particle* p)
{
    int l = Field::getGridLength();

    for(int i=0 ; i<l ; i++)
    {
        Voxel* v = grid[i];
        if(v->contains(p->getPosition()) )
        {

        }
    }
}

/** Debug Checks if a Point object is in the field (calls contains(Point* p))
*/
void Field::containsDebug(Point* p)
{
    if(this->contains(p))
    {
        printf("Oui\n");
    }
    else
    {
        printf("Non\n");
    }
}
/** Updates the field, calls to update the wind in he field and if the particles are still in the field,
if not, calls resetParticle, if yes calls calcSpeed
*/

void Field::update()
{
    int l = Field::getGridLength();

    for(int i=0; i<l ; i++)
    {
        grid[i]->updateVec(this->wind);
        grid[i]->update();
    }

    for(int i = 0; i < nbParticles; i++)
    {
        if(particles[i]->isAlive()
            && particles[i]->getPosition()->x < 2 && particles[i]->getPosition()->x >= 0
            && particles[i]->getPosition()->y < 2 && particles[i]->getPosition()->y >= 0
            && particles[i]->getPosition()->z < 2 && particles[i]->getPosition()->z >= 0)
        {
            for(int j=0; j<l ; j++)
            {
                if (grid[j]->contains(particles[i]))
                {
                    particles[i]->calcSpeed(grid[j]->getAccel());
                }
            }
            particles[i]->update();
        }
        else
            resetParticle(particles[i]);
    }
}

/** Debug echo
*/
void Field::explain()
{
    BaseVBO::explain();
    //printf("n:%d \nrayon:%f \nhauteur:%f \ndecalage:%f\n", n, rayon, hauteur, decalage);
}

/** Returns the total number of subparts of the field, used to set the length of the grid matrix
*/
int Field::getGridLength()
{
    float tmp = round(length/step);
    return tmp*tmp*tmp;
}

/** Debug : calls to the debug draw of particles and "voxels" to handle some checks
*/
void Field::drawDebug()
{
    int l = Field::getGridLength();
    for(int i=0 ; i<l ; i++)
    {
        this->grid[i]->drawDebug();
    }
    for(int i = 0; i < nbParticles; i++)
    {
        particles[i]->drawDebug();
    }
    /*
    glColor3ub(0, 255, 0); //face haute rouge

    glBegin(GL_LINE_LOOP);
    glVertex3f(0, length, 0);
    glVertex3f(2, 2, 0);
    glVertex3f(2, 2, 2);
    glVertex3f(0, 2, 2);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(2, 0, 2);
    glVertex3f(0, 0, 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, 0);

    glVertex3f(2, 2, 0);
    glVertex3f(2, 0, 0);

    glVertex3f(2, 2, 2);
    glVertex3f(2, 0, 2);

    glVertex3f(0, 2, 2);
    glVertex3f(0, 0, 2);
    glEnd();*/
}

/** Returns the step, it's the length of each subparts of the field
*/
float Field::getStep()
{
    return step;
}

/** Returns the vec3 that defines the wind of the field
*/
glm::vec3* Field::getWind()
{
    return wind;
}

/** Sets the wind using 3 floats
*/
void Field::setWind(float x, float y, float z)
{
    this->wind->x = x;
    this->wind->y = y;
    this->wind->z = z;
}

/** Returns a random float between min and max
*/
float Field::randNumber(float min, float max)
{
    float r = min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(max-min));
    return r;
}

/** Call to the reset function of the particle
*/
void Field::resetParticle(Particle* particle)
{
    particle -> resetParticle(this->length);
}

int Field::getNbParticles()
{
    return this->nbParticles;
}

/** Returns a Particle object
*/
Particle* Field::getParticle(int i)
{
    return this->particles[i];
}

/** Call to the function that draws the particles
*/
void Field::draw()
{
    for(int i = 0; i < nbParticles; i++)
    {
        particles[i]->draw();
        //particles[i]->drawDebug();
    }
}
