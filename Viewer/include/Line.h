#pragma once
#include <glm/glm.hpp>

class Line
{
private:
	glm::vec2 _pointA;	//	(x,y)
	glm::vec2 _pointB;	//	(x,y)
	float _inclination;	//	a

public:
	Line(glm::vec2 a, glm::vec2 b);
	glm::vec2 GetPointA() const;
	glm::vec2 GetPointB() const;
	float GetInclination() const;
};