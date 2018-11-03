#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
#include "Global.h"

class Line
{
private:
	glm::vec3 _pointA;	//	(x,y)
	glm::vec3 _pointB;	//	(x,y)
	float _inclination;	//	a

public:
	Line(glm::vec3 a, glm::vec3 b);
	glm::vec3 GetPointA() const;
	glm::vec3 GetPointB() const;
	float GetInclination() const;	
};