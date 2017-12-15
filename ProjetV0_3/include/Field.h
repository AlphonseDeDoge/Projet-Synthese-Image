#include "../include/BaseVBO.h"
#include "../include/Voxel.h"
#include "../include/Obstacle.h"
#include "../include/Particle.h"

#ifndef FIELD_H
#define FIELD_H

class Field: public BaseVBO
{
    private:
        int length;
        Voxel** grid;
        float step;
        Point* origin;
        glm::vec3* wind;
        Particle** particles;
        int nbParticles;

    public:
        Field();
        Field(int length);
        Field(int length, const GLuint &buffers);
        void generateMatrix();
        int  getGridLength();
        bool addObstacle(Obstacle Obs);
        bool contains(Point* p);
        void containsDebug(Point* p);
        void contains(Particle* p);
        void fillId();
        void fillVertex();
        void fillColor();
        void update();
        void explain();
        void drawDebug();
        void generateParticles();
        void resetParticle(Particle* particle);
        void draw();

        float getStep();
        glm::vec3* getWind();
        void setWind(float x, float y, float z);
        float randNumber(float min, float max);

        int getNbParticles();
        Particle* getParticle(int i);
};

#endif // FIELD_H
