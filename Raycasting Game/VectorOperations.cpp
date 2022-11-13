#include "VectorOperations.h"

float magnitude(const sf::Vector2f vect) {
	return std::sqrt(vect.x * vect.x + vect.y * vect.y);
}

void rotateVector(sf::Vector2f* vect, float rot)
{
	float oldX = vect->x;
	vect->x = vect->x * cos(rot) - vect->y * sin(rot);
	vect->y = oldX * sin(rot) + vect->y * cos(rot);
}
