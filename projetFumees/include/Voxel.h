#include "../include/Point.h"
#include "../glm/glm.hpp"
#include "../include/BaseVBO.h"
#include "../include/Particle.h"

#ifndef VOXEL_H
#define VOXEL_H

class Voxel : public BaseVBO
{
   private:
        Point* position;
        float size;
        glm::vec3* accel;
        glm::vec3* oldWind;
		bool testVoxel();

    public:
        Voxel();
        Voxel(Point* position, const GLuint &buffers, float size);
        void updateVec(glm::vec3* wind);
        glm::vec3* getAccel();
        float randNumber(float min, float max);
        void explain();
        void drawDebug();
        bool contains(Point* point);
        bool contains(Particle* particle);

};

#endif // VOXEL_H
