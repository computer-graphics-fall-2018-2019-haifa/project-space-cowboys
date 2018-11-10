#include "Face.h"

Face::Face(std::istream& issLine)
{
	vertexIndices =  { 0, 0, 0 };
	normalIndices =  { 0, 0, 0 };
	textureIndices = { 0, 0, 0 };
	 
	char c;
	for (int i = 0; i < 3; i++)
	{
		issLine >> std::ws >> vertexIndices.at(i) >> std::ws;

		if (issLine.peek() != '/')
		{
			continue;
		}

		issLine >> c >> std::ws;

		if (issLine.peek() == '/')
		{
			issLine >> c >> std::ws >> normalIndices.at(i);
			continue;
		}
		else
		{
			issLine >> textureIndices.at(i);
		}

		if (issLine.peek() != '/')
		{
			continue;
		}

		issLine >> c >> normalIndices.at(i);
	}
}

Face::~Face()
{

}

const int Face::GetVertexIndex(int index)
{
	return vertexIndices[index];
}

const int Face::GetNormalIndex(int index)
{
	return normalIndices[index];
}

const int Face::GetTextureIndex(int index)
{
	return textureIndices[index];
}

const std::vector<int> Face::GetVertexIndices() const
{
	return this->vertexIndices;
}

const std::vector<int> Face::GetNormalIndices() const
{
	return this->normalIndices;
}

const std::vector<int> Face::GetTextureIndices() const
{
	return this->textureIndices;
}


