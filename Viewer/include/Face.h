#pragma once
#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class Face
{
private:
	std::vector<int> vertexIndices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;

public:
	Face(std::istream& issLine);
	virtual ~Face();
	const int Face::GetVertexIndex(int index);
	const int Face::GetNormalIndex(int index);
	const int Face::GetTextureIndex(int index);

	const std::vector<int> GetVertexIndices() const;
	const std::vector<int> GetNormalIndices() const;
	const std::vector<int> GetTextureIndices() const;
};