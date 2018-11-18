#pragma once
#include "Scene.h"
#include "Global.h"
#include "Line.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include "ImguiMenus.h"

/*
 * Renderer class.
 */
class Renderer
{
private:
	float *colorBuffer;
	float *zBuffer;
	int viewportWidth;
	int viewportHeight;
	int viewportX;
	int viewportY;

	void putPixel(int x, int y, const glm::vec3& color);
	void createBuffers(int viewportWidth, int viewportHeight);

	GLuint glScreenTex;
	GLuint glScreenVtc;

	void createOpenGLBuffer();
	void initOpenGLRendering();

public:
	Renderer(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	~Renderer();

	void Render(Scene & scene);	
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	void SetViewport(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	void DrawLine(const Line& line, Camera& camera, const glm::vec4& color);
	void DrawTriangle(std::vector<glm::vec3>& vertices, const glm::vec4& color, Camera & camera);
	void Renderer::DrawNormals(const glm::vec3& faceCenter, const glm::vec3& normal, const glm::vec4& color, Camera & camera);
	void DrawBoundingBox(MeshModel& model, Camera& camera);
};
