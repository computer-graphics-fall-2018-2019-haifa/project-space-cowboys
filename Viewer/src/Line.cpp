#include "Line.h"

Line::Line(glm::vec2 a, glm::vec2 b)
{
	_point = a;
	_inclination = (b[1] - a[1]) / (b[0] - a[0]);
}

Line::Line(glm::vec2 a, float m)
{
	_point = a;
	_inclination = m;
}