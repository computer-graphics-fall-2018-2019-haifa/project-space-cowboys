#pragma once
#include "Global.h"
#include <glm/glm.hpp>
#include <string>
#include "MeshModel.h"

#define PI 3.14159265 / 180
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
	static glm::vec3 transformVertic(const glm::vec3 vertic, glm::mat4 transformMetrix);
	/************************************************************************/
	/* Matrices                                                           */
	/************************************************************************/

	static glm::mat4 TranslationMatrix(const glm::vec3 translation);
	static glm::mat4 scaleMat(const glm::vec3 scale);
	static glm::mat4 rotateMat(const glm::vec3 angle);
	static glm::mat4 setFullTransformMat(const glm::vec3 translation, const glm::vec3 scale, const glm::vec3 angle,const glm::vec3 center, bool isLocal);
	static glm::mat4 setFinallTransformMat(glm::mat4 worldTrans, glm::mat4 localTrans, glm::mat4 cameraTrans);
private:
	static std::string GetFileName(const std::string& filePath);
};


