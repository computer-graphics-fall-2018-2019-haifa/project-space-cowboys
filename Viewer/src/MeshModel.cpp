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
	/*if (!isCamera) {
		for (int i=0 ; i< this->vertices.size();i++)
		{
			this->vertices[i].x += 640.0f;
			this->vertices[i].y += 320.0f;
		}
	}*/
	
	if (!normals.empty()|| isCamera)
		this->normals = std::vector<glm::vec3>(normals);
	else
		calcNormals();

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
	calcBoxPoints();

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
	this->scale[0] = copy.scale[0];
	this->scale[1] = copy.scale[1];
	this->rotate[0] = copy.rotate[0];
	this->rotate[1] = copy.rotate[1];
	this->translate[0] = copy.translate[0];
	this->translate[1] = copy.translate[1];
}

MeshModel::MeshModel(const int type)
{
	switch (type)
	{
	case 0:
		createPol();
	default:
		break;
	}
}

MeshModel::~MeshModel()
{

}


void MeshModel::SetWorldTransformation()
{
	glm::vec3 center = { centerPoint.x,centerPoint.y, centerPoint.z };
	this->worldTransform = Utils::setFullTransformMat(this->translate[0], this->scale[0], this->rotate[0],center,false);
	//this->worldTransform = Utils::rotateMat(rotate[0]);
}

const glm::mat4& MeshModel::GetWorldTransformation() const
{
	return this->worldTransform;
}

void MeshModel::SetLocalTransformation()
{
	glm::vec3 center = { centerPoint.x,centerPoint.y, centerPoint.z };
		
	this->localTransform = Utils::setFullTransformMat(this->translate[1], this->scale[1], this->rotate[1], center, true);
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



const glm::vec3 MeshModel::getMaximus() const
{
	return maximums;
}

const glm::vec3 MeshModel::getMinmums() const
{
	return minimums;
}

void MeshModel::calcBoxPoints()
{
	float minX = vertices[0].x;
	float minY = vertices[0].y;
	float minZ = vertices[0].z;
	float maxX = vertices[0].x;
	float maxY = vertices[0].y;
	float maxZ = vertices[0].z;
	for (glm::vec3 vertex : vertices)
	{
		minX = std::fmin(minX, vertex.x);
		maxX = std::fmax(maxX, vertex.x);

		minY = std::fmin(minY, vertex.y);
		maxY = std::fmax(maxY, vertex.y);

		minZ = std::fmin(minZ, vertex.z);
		maxZ = std::fmax(maxZ, vertex.z);
	}

	minimums = glm::vec3(minX, minY, minZ);
	maximums = glm::vec3(maxX, maxY, maxZ);
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
	size_t size = faces.size();
	for (size_t i=0 ;i< size;i++)
	{
		
		int ver0Index = faces[i].GetVertexIndex(0);
		int ver1Index = faces[i].GetVertexIndex(1);
		int ver2Index = faces[i].GetVertexIndex(2);

		glm::vec3 v0 = vertices[ver0Index-1];
		glm::vec3 v1 = vertices[ver1Index-1];
		glm::vec3 v2 = vertices[ver2Index-1];
		glm::vec3 center = v0 + v1 + v2;
		center.x /= 3.0f;
		center.y /= 3.0f;
		center.z /= 3.0f;
		glm::vec3 normalEnd = glm::normalize(glm::cross((v0 - v1), (v0 - v2)));
		faces[i].setNorm((20.0f*normalEnd)+center);
		faces[i].setCenter(center);
		
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

void MeshModel::createPol(){

	this->worldTransform = glm::mat4x4(1);
	this->localTransform = glm::mat4x4(1);
	this->modelName = "poligon.obj";
	glm::vec3 v0 = { 123.0f,122.0f,-30.0f };
	glm::vec3 v1 = { 61.0f,0.0f,-5.0f };
	glm::vec3 v2 = { 1.0f,122.0f,-10.0f };
	this->vertices.push_back(v0);
	this->vertices.push_back(v1);
	this->vertices.push_back(v2);
	
	Face f = Face({ 1, 2, 3 });
	this->faces.push_back(f);
	
	this->scale[0] = { 1,1,1 };
	this->scale[1] = { 1,1,1 };
	this->rotate[0] = { 0,0,0 };
	this->rotate[1] = { 0,0,0 };
	this->translate[0] = { 0,0,0 };
	this->translate[1] = { 0,0,0 };
	this->boxColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	this->normColor = { 0,0,1,0 };
	this->isCamera = false;
	SetCenterPoint();
	calcBoxPoints();
	calcNormals();
}
