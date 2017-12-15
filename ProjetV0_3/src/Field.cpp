#include "../include/Field.h"

/** Constructeur par defaut
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

/** Constructeur avec parametre
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

/** Constructeur avec parametres
*/
Field::Field(int length, const GLuint &buffers)
{
    this->nbParticles   = 500;
    this->length    = length;
    this->step      = 0.1;
    this->origin    = new Point();
    this->grid      = new Voxel*[getGridLength()];
    this->particles = new Particle*[nbParticles];
    this->wind      = new glm::vec3();
    this->buffers   = buffers;
    generateMatrix();
    generateParticles();

}

/** generation aleatoire de voxel (A MODIFIER)
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

/** generation aleatoire de voxel (A MODIFIER)
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

/** verifie que la particule est dans le champ (A MODIFIER)
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

/** verifie que la particule est dans le champ (A MODIFIER)
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

/** verifie que la particule est dans le champ (A MODIFIER)
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
/**
*
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

void Field::fillId()
{

}

void Field::fillVertex()
{

}

void Field::fillColor()
{

}

void Field::explain()
{
    BaseVBO::explain();
    //printf("n:%d \nrayon:%f \nhauteur:%f \ndecalage:%f\n", n, rayon, hauteur, decalage);
}

int Field::getGridLength()
{
    float tmp = round(length/step);
    return tmp*tmp*tmp;
}

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

float Field::getStep()
{
    return step;
}

glm::vec3* Field::getWind()
{
    return wind;
}

void Field::setWind(float x, float y, float z)
{
    this->wind->x = x;
    this->wind->y = y;
    this->wind->z = z;
}

float Field::randNumber(float min, float max)
{
    float r = min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(max-min));
    return r;
}

void Field::resetParticle(Particle* particle)
{
    particle -> resetParticle(this->length);
}

int Field::getNbParticles()
{
    return this->nbParticles;
}

Particle* Field::getParticle(int i)
{
    return this->particles[i];
}

void Field::draw()
{
    for(int i = 0; i < nbParticles; i++)
    {
        particles[i]->draw();
        //particles[i]->drawDebug();
    }
}

bool Field::testField()
{
	generateParticles();
	for(int i=0;i<nbParticules;i++)
	{
		if(particles[i]==NULL){
			printf("error : Particle null\n");
			return false;
		}
	}
	
	int oracle_getGridLength = 8000;
	
	if(oracle_getGridLength != getGridLength())
	{
		printf("error : bad grid length\n");
		return false;
	}
	
	float oracle_randNumberMin = 0;
	float oracle_randNumberMax = 2;
	
	if(oracle_randNumberMin > randNumber(oracle_randNumberMin(), oracle_randNumberMax()) && oracle_randNumberMax < randNumber(oracle_randNumberMin(), oracle_randNumberMax()))
	{
		printf("error : Random value outside the range");
		return false;
	}
	
	return true;	
}



