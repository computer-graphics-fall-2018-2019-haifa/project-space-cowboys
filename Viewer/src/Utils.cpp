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

MeshModel Utils::LoadMeshModel(const std::string& filePath, bool camera)
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

	return MeshModel(faces, vertices, normals,camera, Utils::GetFileName(filePath));
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
	//return glm::vec3(source[0] , source[1] , source[2] );
}

/* calculate the post transformetion and prespective view points
	w and h are half of the hight and width of the current screen
*/
glm::vec3 Utils::transformVertic(const glm::vec3 vertic, glm::mat4 transformMetrix,int w,int h) {
	glm::vec4 temp = Utils::Homogeneous3to4(vertic);
	glm::vec4 temp2 = temp * transformMetrix  ;
	glm::vec3 temp3 = Utils::Homogeneous4to3(temp2);
	//temp3.x = (temp3.x + 1)*w; *bug
	//temp3.y = (temp3.y + 1)*h; *bug
	return temp3;
}

glm::mat4 Utils::TranslationMatrix(const glm::vec3 translation)
{
	return glm::mat4(
		1.0f, 0.0f, 0.0f, translation.x,
		0.0f, 1.0f, 0.0f, translation.y,
		0.0f, 0.0f, 1.0f, translation.z,
		0.0f, 0.0f, 0.0f, 1.0f);
}

glm::mat4 Utils::scaleMat(const glm::vec3 scale)
{
	return glm::mat4(scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1);

}
glm::mat4 Utils::rotateMat(const glm::vec3 angle)
{
	
	glm::mat4 x = glm::mat4(1, 0, 0, 0, 0, cosf(angle.x), -sinf(angle.x), 0, 0, sinf(angle.x), cosf(angle.x), 0, 0, 0, 0, 1);
	
	
	glm::mat4 y = glm::mat4(cosf(angle.y), 0, sinf(angle.y), 0, 0, 1, 0, 0, -sinf(angle.y), 0, cosf(angle.y), 0, 0, 0, 0, 1);
	
	
	glm::mat4 z = glm::mat4(1, 0, 0, 0, 0, cosf(angle.z), -sinf(angle.z), 0, 0, sinf(angle.z), cosf(angle.z), 0, 0, 0, 0, 1);
	
	
	return x * y * z;

}
glm::mat4 Utils::setFullTransformMat(const glm::vec3 translation, const glm::vec3 scale, const glm::vec3 angle, glm::vec3 center, bool isLocal)
{
	if (isLocal) {

		/*glm::mat4 rot = TranslationMatrix(center)*rotateMat(angle)*TranslationMatrix(-center);
		glm::mat4 sca1 = scaleMat(scale);
		glm::mat4 sca = TranslationMatrix(center)*sca1*TranslationMatrix(-center);
		glm::mat4 trans = TranslationMatrix(translation);
		glm::mat4 toreturn = trans * rot*sca;
		return toreturn;*/
		return TranslationMatrix(center)*TranslationMatrix(translation)*scaleMat(scale)*rotateMat(angle)*TranslationMatrix(-center);
		 
	}
	else
		return TranslationMatrix(translation)*rotateMat(angle)*scaleMat(scale);
}

glm::mat4 Utils::setFinallTransformMat(glm::mat4 worldTrans, glm::mat4 localTrans, glm::mat4 cameraTrans, glm::mat4 cameraProjection) {
	// cameraProjection *bug
	return   worldTrans * localTrans;//* glm::inverse(cameraTrans);
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

