#include "../include/Voxel.h"

/** Default constructor
*/
Voxel::Voxel()
{
    this->buffers = 0;
    this->position = new Point();
    this->accel = new glm::vec3(0,0,0);
    this->oldWind   = new glm::vec3(0,0,0);
    this->size = 1;
}

/** Arguments constructor, uses a Point object, a GLuint buffers ref and a float
*/
Voxel::Voxel(Point* position, const GLuint &buffers, float size)
{
    this->buffers   = buffers;
    this->size      = size;
    this->position  = position;
    this->accel     = new glm::vec3(0,0,0);
    this->oldWind   = new glm::vec3(0,0,0);
}

/** Updates the wind vector if there is changes to apply (will only apply the randNumber then, therefore prevents a neverending wind refresh)
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

/** Returns a random float betwen min and max
*/
float Voxel::randNumber(float min, float max)
{
    float r = min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(max-min));
    return r;
}

/** Returns the vec3 of the current object
*/
glm::vec3* Voxel::getAccel()
{
    return this->accel;
}

/** Debug echo
*/
void Voxel::explain()
{
    BaseVBO::explain();
    //printf("n:%d \nrayon:%f \nhauteur:%f \ndecalage:%f\n", n, rayon, hauteur, decalage);
}

/** Debug draw of the current object
*/
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

/** Returns if a Point object is inside the bounds of the current object
*/
bool Voxel::contains(Point* point)
{
    return (
        (point->x >= position->x && point->x < (position->x + size)) &&

        (point->y >= position->y && point->y < (position->y + size)) &&

        (point->z >= position->z && point->z < (position->z + size))
    );
}

/** Returns if a Particle object is inside the bounds of the current object by calling the same function with the Point object argument
*/
bool Voxel::contains(Particle* particle)
{
    return contains(particle->getPosition());
}

bool testVoxel()
{
	Point* p1 = new Point(0.1,0.1,0.1);
	Point* p2 = new Point(0.3,0.3,0.3);
	Point* p3 = new Point(0.4,0.4,0.4);
	Particle* pA = new Particle(0,50,p2,new glm::vec3(0.0,0.0,0.0));
	Voxel* v1 = new Voxel(new Point(), 0, 0.2);
	Voxel* v2 = new Voxel(new Point(0.2,0.0,0.0), 0, 0.2);
	
	glm::vec3* w1 = new glm::vec3(0.1,0.1,0.1);
	
	bool oracle_contains = false;
	if( (v1->contains(p1)==oracle_contains) || (v1->contains(p3)!=oracle_contains) )
	{
		printf("Test de Voxel raté : Erreur dans contains(Point* point)\n");
		return false;
	}
	
	if( v1->contains(pA)!=oracle_contains )
	{
		printf("Test de Voxel raté : Erreur dans contains(Particle* particle)\n");
		return false;
	}
	
	bool oracle_updateVec = true;
	if( v1->getAccel().equals(v2->getAccel())==oracle_updateVec )
	{
		glm::vec3 tmp = &(v1->getAccel()); // current accel value into tmp
		v1->updateVec(w1); // changing accel value
		if( tmp.equals(&(v1->getAccel()))==oracle_updateVec ) // comparing
		{
			printf("Test de Voxel raté : Erreur dans updateVec(glm::vec3* wind) en nouveau changement\n");
			return false;
		}
		tmp = &(v1->getAccel()); // new temporary variable save
		vi->updateVec(w1); // applying the same new wind value to change accel (shouldn't do anything)
		if( tmp.equals(&(v1->getAccel()))!=oracle_updateVec ) // comparing
		{
			printf("Test de Voxel raté : Erreur dans updateVec(glm::vec3* wind) en copie du dernier changement\n");
			return false;
		}
	}
	else
	{
		printf("Test de Voxel raté : Méthode equals non utilisable dans ce cas\n");
		return false;
	}
	
	return true;
}
