#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,  bool camera ,const std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1)),
	localTransform(glm::mat4x4(1))
{
	isCamera = camera;
	this->faces = std::vector<Face>(faces);
	this->vertices = std::vector<glm::vec3>(vertices);
	if (!isCamera) {
		for (int i=0 ; i< this->vertices.size();i++)
		{
			this->vertices[i].x += 640.0f;
			this->vertices[i].y += 320.0f;
		}
	}
	
	if (!normals.empty()|| isCamera)
		this->normals = std::vector<glm::vec3>(normals);
	/*else
		calcNormals();*/

	this->scale[0] = { 1,1,1 };
	this->scale[1] = { 1,1,1 };
	this->rotate[0] = { 0,0,0 };
	this->rotate[1] = { 0,0,0 };
	this->translate[0] = { 0,0,0 };
	this->translate[1] = { 0,0,0 };
	this->modelName = modelName;		
	this->boxColor = { 0,0,0,0 };
	this->normColor = { 0,0,1,0 };
	
	
	SetCenterPoint();
	

	for (glm::vec3 vertex : vertices)
	{
		minX = std::fmin(minX, vertex.x);
		maxX = std::fmax(maxX, vertex.x);

		minY = std::fmin(minY, vertex.y);
		maxY = std::fmax(maxY, vertex.y);

		minZ = std::fmin(minZ, vertex.z);
		maxZ = std::fmin(maxZ, vertex.z);
	}

	minimums = glm::vec3(minX, minY, minZ);
	maximums = glm::vec3(maxX, maxY, maxZ);
}
MeshModel::MeshModel(const MeshModel &copy)
{
	this->isCamera = copy.isCamera;
	this->faces = copy.faces;
	this->vertices = copy.vertices;
	this->normals = copy.normals;
	this->worldTransform = copy.worldTransform;
	this->localTransform = copy.localTransform;
	this->color = copy.color;
	this->modelName = copy.modelName;
	this->centerPoint = copy.centerPoint;
	this->minimums = copy.minimums;
	this->maximums = copy.maximums;
	this->minX = copy.minX;
	this->minY = copy.minY;
	this->minZ = copy.minZ;
	this->maxX = copy.maxX;
	this->maxY = copy.maxY;
	this->maxZ = copy.maxZ;
	this->scale[0] = copy.scale[0];
	this->scale[1] = copy.scale[1];
	this->rotate[0] = copy.rotate[0];
	this->rotate[1] = copy.rotate[1];
	this->translate[0] = copy.translate[0];
	this->translate[1] = copy.translate[1];
}

MeshModel::~MeshModel()
{

}


void MeshModel::SetWorldTransformation()
{
	//this->worldTransform = Utils::setFullTransformMat(this->translate[0], this->scale[0], this->rotate[0]);
	this->worldTransform = Utils::rotateMat(rotate[0]);
}

const glm::mat4& MeshModel::GetWorldTransformation() const
{
	return this->worldTransform;
}

void MeshModel::SetLocalTransformation()
{
	glm::vec3 victor = { centerPoint.x,centerPoint.y, centerPoint.z };
	glm::mat4 mat = Utils::TranslationMatrix(victor);
	mat *= Utils::setFullTransformMat(this->translate[1], this->scale[1], this->rotate[1]);
	victor *= -1;
	mat *= Utils::TranslationMatrix(victor);
	this->localTransform = mat;
}

const glm::mat4x4 & MeshModel::GetLocalTransformation() const
{
	return this->localTransform;
}

void MeshModel::updateTransformations()
{
	this->SetLocalTransformation();
	this->SetWorldTransformation();
}

void MeshModel::SetColor(const glm::vec4& color)
{
	this->color = color;
}

const glm::vec4& MeshModel::GetColor() const
{
	return this->color;
}

const std::string& MeshModel::GetModelName()
{
	return this->modelName;
}

const std::vector<Face> MeshModel::GetAllFaces() const
{
	return this->faces;
}

const std::vector<glm::vec3> MeshModel::GetVertices() const
{
	return this->vertices;
}

const glm::vec3 MeshModel::GetVertex(int index) const
{
	return this->vertices[index - 1];
}

const std::vector<glm::vec3> MeshModel::GetNormals() const
{
	return this->normals;
}

const float MeshModel::MinX()
{
	return minX;
}

const float MeshModel::MaxX()
{
	return maxX;
}

const float MeshModel::MinY()
{
	return minY;
}

const float MeshModel::MaxY()
{
	return maxY;
}

const float MeshModel::MinZ()
{
	return minZ;
}

const float MeshModel::MaxZ()
{
	return maxZ;
}


void MeshModel::SetCenterPoint()
{
	float x = 0;
	float y = 0;
	float z = 0;
	size_t size = vertices.size();
	for (size_t i = 0; i < size; i++)
	{
		x += vertices[i].x;
		y += vertices[i].y;
		z += vertices[i].z;
	}
	
	centerPoint = glm::vec4((x / size), (y / size), (z / size), 0);
}

const glm::vec4 & MeshModel::GetCenterPoint() const
{
	return this->centerPoint;
}

void MeshModel::calcNormals() 
{
	
	for (auto face : faces)
	{
		
		int ver0Index = face.GetVertexIndex(0);
		int ver1Index = face.GetVertexIndex(1);
		int ver2Index = face.GetVertexIndex(2);

		glm::vec3 v0 = vertices[ver0Index];
		glm::vec3 v1 = vertices[ver1Index];
		glm::vec3 v2 = vertices[ver2Index];
		glm::vec3 center = v0 + v1 + v2;
		center.x /= 3;
		center.y /= 3;
		center.z /= 3;
		//glm::vec3 normalEnd = glm::normalize(glm::cross((v0 - v1), (v0 - v2)));
		face.setNorm(glm::normalize(glm::cross((v0 - v1), (v0 - v2))));
		face.setCenter(center);
		
	}
}
void MeshModel::SetBoxColor(const glm::vec4& color)
{
	this->boxColor = color;
}
void MeshModel::SetNormColor(const glm::vec4& color)
{
	this->normColor = color;
}
const glm::vec4& MeshModel::GetNormColor() const
{
	return this->normColor;
}
const glm::vec4& MeshModel::GetBoxColor() const
{
	return this->boxColor;
}
