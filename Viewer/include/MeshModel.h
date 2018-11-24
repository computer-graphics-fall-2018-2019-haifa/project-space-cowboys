#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Face.h"

/*
 * MeshModel class.
 * This class represents a mesh model (with faces and normals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */
class MeshModel
{
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 worldTransform;
	glm::mat4 localTransform;
	glm::vec4 color;
	glm::vec4 normColor;
	glm::vec4 boxColor;
	std::string modelName;
	glm::vec4 centerPoint = glm::vec4(0, 0, 0, 0);
	glm::vec3 minimums;
	glm::vec3 maximums;
	
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float minZ = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();
	float maxZ = std::numeric_limits<float>::min();
	bool isCamera;
public:
	glm::vec3 scale[2];
	glm::vec3 rotate[2];
	glm::vec3 translate[2];

	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, bool camera, const std::string& modelName = ""  );
	MeshModel(const MeshModel &copy);
	virtual ~MeshModel();

	void SetWorldTransformation();
	const glm::mat4x4& GetWorldTransformation() const;

	void SetLocalTransformation();
	const glm::mat4x4& GetLocalTransformation() const;

	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

	const std::string& GetModelName();

	const std::vector<Face> GetAllFaces() const;
	const std::vector<glm::vec3> GetVertices() const;
	const std::vector<glm::vec3> GetNormals() const;

	const float MinX();
	const float MaxX();

	const float MinY();
	const float MaxY();

	const float MinZ();
	const float MaxZ();

	const glm::vec3 GetVertex(int index) const;
	const glm::vec4& GetCenterPoint() const;

	void calcNormals();

	void SetBoxColor(const glm::vec4 & color);

	void SetNormColor(const glm::vec4 & color);

	const glm::vec4 & GetNormColor() const;

	const glm::vec4 & GetBoxColor() const;

	void SetCenterPoint();

};
