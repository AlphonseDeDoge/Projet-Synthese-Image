#include "../glm/glm.hpp"
#include "BaseVBO.h"

#ifndef PARTICLE_H
#define PARTICLE_H

/** Constructeur par defaut
*/
class Particle: public BaseVBO
{
    private:
        int lifeTime;
        int timeLived;
        Point* position;
        glm::vec3* speed;
        glm::vec3* accel;
        float mass,density;

        int n;
        float rayon;
        float hauteur;
        float decalage;

    public:
        Particle();
        Particle(int life, Point* p, glm::vec3* speed, glm::vec3* accel, float mass, float density);
        Particle(const GLuint&  buffers, int life, Point* p, glm::vec3* speed);
        void calcSpeed(glm::vec3* v);
        void update();
        bool isAlive();
        void move();
        void drawDebug();

        Point* getPosition();
        void resetParticle(float length);
        float randNumber(float min, float max);

        void fillId();
        void fillVertex();
        void fillColor();
        void explain();
        int getN();
};

#endif // PARTICLE_H
