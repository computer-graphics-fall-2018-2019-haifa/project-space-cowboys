#include "Utils.h"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

glm::vec3 Utils::Vec3fFromStream(std::istream& issLine)
{
	float x, y, z;
	issLine >> x >> std::ws >> y >> std::ws >> z;
	return glm::vec3(x, y, z);
}

glm::vec2 Utils::Vec2fFromStream(std::istream& issLine)
{
	float x, y;
	issLine >> x >> std::ws >> y;
	return glm::vec2(x, y);
}

MeshModel Utils::LoadMeshModel(const std::string& filePath)
{
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::ifstream ifile(filePath.c_str());

	// while not end of file
	while (!ifile.eof())
	{
		// get line
		std::string curLine;
		std::getline(ifile, curLine);

		// read the type of the line
		std::istringstream issLine(curLine);
		std::string lineType;

		issLine >> std::ws >> lineType;

		// based on the type parse data
		if (lineType == "v")
		{
			vertices.push_back(Utils::Vec3fFromStream(issLine));
		}
		else if (lineType == "vn")
		{
			// Add the required code here...
		}
		else if (lineType == "vt")
		{
			// Texture coordinates
		}
		else if (lineType == "f")
		{
			faces.push_back(Face(issLine));
		}
		else if (lineType == "#" || lineType == "")
		{
			// comment / empty line
		}
		else
		{
			std::cout << "Found unknown line Type \"" << lineType << "\"";
		}
	}

	return MeshModel(faces, vertices, normals, Utils::GetFileName(filePath));
}

std::vector<glm::vec3> Utils::TriangleFromVertexIndices(const std::vector<int>& vertices, MeshModel& model)
{
	glm::vec3 a = model.GetVertex(vertices[0]);
	glm::vec3 b = model.GetVertex(vertices[1]);
	glm::vec3 c = model.GetVertex(vertices[2]);
	std::vector<glm::vec3> triangle = std::vector<glm::vec3>();
	triangle.push_back(a);
	triangle.push_back(b);
	triangle.push_back(c);
	return triangle;
}

glm::vec4 Utils::Homogeneous3to4(const glm::vec3 source)
{
	return glm::vec4(source[0], source[1], source[2], 1.0f);
}

glm::vec3 Utils::Homogeneous4to3(const glm::vec4 source)
{
	return glm::vec3(source[0] / source[3], source[1] / source[3], source[2] / source[3]);
}

glm::mat4x4 Utils::TranslationMatrix(const glm::vec3 translation)
{
	return glm::mat4x4(
		1.0f, 0, 0, translation.x,
		0, 1.0f, 0, translation.y,
		0, 0, 1.0f, translation.z,
		0, 0, 0, 1.0f);
}

std::string Utils::GetFileName(const std::string& filePath)
{
	if (filePath.empty()) {
		return {};
	}

	auto len = filePath.length();
	auto index = filePath.find_last_of("/\\");

	if (index == std::string::npos) {
		return filePath;
	}

	if (index + 1 >= len) {

		len--;
		index = filePath.substr(0, len).find_last_of("/\\");

		if (len == 0) {
			return filePath;
		}

		if (index == 0) {
			return filePath.substr(1, len - 1);
		}

		if (index == std::string::npos) {
			return filePath.substr(0, len);
		}

		return filePath.substr(index + 1, len - index - 1);
	}

	return filePath.substr(index + 1, len - index);
}