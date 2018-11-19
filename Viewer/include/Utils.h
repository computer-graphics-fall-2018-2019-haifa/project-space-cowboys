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
	static MeshModel LoadMeshModel(const std::string& filePath, bool camera);	
	static std::vector<glm::vec3> TriangleFromVertexIndices(const std::vector<int>& vertices, MeshModel& model);
	
	/************************************************************************/
	/* Conversions                                                         */
	/************************************************************************/
	static glm::vec4 Homogeneous3to4(const glm::vec3 source);
	static glm::vec3 Homogeneous4to3(const glm::vec4 source);

	/************************************************************************/
	/* Matrices                                                           */
	/************************************************************************/

	static glm::mat4 TranslationMatrix(const glm::vec3 translation);
	static glm::mat4 scaleMat(glm::vec3 scale);
	static glm::mat4 rotateMat(float angle, char axies);
private:
	static std::string GetFileName(const std::string& filePath);
};


