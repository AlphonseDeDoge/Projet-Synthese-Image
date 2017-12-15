#include "../include/Point.h"
#include "../include/Obstacle.h"

/** Default constructor
*/
Obstacle::Obstacle()
{
    this->position = Point();
}

/** Argument constructor, position the Obstacle object on the Point object position
*/
Obstacle::Obstacle(Point p)
{
    this->position = p;
}

/** TO BE DEFINED
*/
glm::vec3 Obstacle::calculNormale()
{
    return glm::vec3();
}
