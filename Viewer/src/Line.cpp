#include "Line.h"

Line::Line(glm::vec3 a, glm::vec3 b)
{
	_pointA = a;
	_pointB = b;
	_inclination = abs((b[1] - a[1])) / abs((b[0] - a[0]));
}

Line Line::fromCamera(Camera& camera)
{	
	glm::vec3 cameraA = Utils::Homogeneous3to4(_pointA) * camera.GetTransformation();;
	glm::vec3 cameraB = Utils::Homogeneous3to4(_pointB) * camera.GetTransformation();
	return Line(cameraA, cameraB);
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