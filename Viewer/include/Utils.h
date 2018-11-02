#pragma once
#include "Global.h"
#include <glm/glm.hpp>
#include <string>
#include "MeshModel.h"

/*
 * Utils class.
 * This class is consisted of static helper methods that can have many clients across the code.
 */
class Utils
{
public:
	static glm::vec3 Vec3fFromStream(std::istream& issLine);
	static glm::vec2 Vec2fFromStream(std::istream& issLine);
	static MeshModel LoadMeshModel(const std::string& filePath);	
	static std::vector<glm::vec3> TriangleFromVertexIndices(const std::vector<int>& vertices, MeshModel& model);

private:
	static std::string GetFileName(const std::string& filePath);
};
