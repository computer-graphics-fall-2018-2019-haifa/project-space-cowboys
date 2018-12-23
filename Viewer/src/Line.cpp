#include "Line.h"

Line::Line(glm::vec3 a, glm::vec3 b)
{
	_pointA = a;
	_pointB = b;
	if ((b[0] - a[0]) == 0 || (b[1] - a[1]) == 0) {
		_inclination = 0;
	}
	else
		_inclination = abs((b[1] - a[1])) / abs((b[0] - a[0]));
}

glm::vec3 Line::GetPointA() const
{
	return _pointA;
}

glm::vec3 Line::GetPointB() const
{
	return _pointB;
}

float Line::GetInclination() const
{
	return _inclination;
}