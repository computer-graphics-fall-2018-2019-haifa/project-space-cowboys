#pragma once
#include <glm/glm.hpp>

class Line
{
private:
	glm::vec2 _point;	//	(x,y)
	float _inclination;	//	a

public:
	Line(glm::vec2 a, glm::vec2 b);
	Line(glm::vec2 a, float m);
};