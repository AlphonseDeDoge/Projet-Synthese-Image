#include "../glm/glm.hpp"

#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
    private:
        Point position;

    public:
        Obstacle();
        Obstacle(Point p);
        glm::vec3 calculNormale();
};

#endif // OBSTACLE_H
