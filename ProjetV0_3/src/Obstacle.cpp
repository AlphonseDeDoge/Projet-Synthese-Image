#include "../include/Point.h"
#include "../include/Obstacle.h"

/** Constructeur par defaut
*/
Obstacle::Obstacle()
{
    this->position = Point();
}

/** Constructeur avec parametres
*/
Obstacle::Obstacle(Point p)
{
    this->position = p;
}

/** Calcul de la normale (A MODIFIER)
*/
glm::vec3 Obstacle::calculNormale()
{
    return glm::vec3();
}
