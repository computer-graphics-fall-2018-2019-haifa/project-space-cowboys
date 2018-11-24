#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include "Utils.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)

Renderer::Renderer(int viewportWidth, int viewportHeight, int viewportX, int viewportY) :
	colorBuffer(nullptr),
	zBuffer(nullptr)
{
	initOpenGLRendering();
	SetViewport(viewportWidth, viewportHeight, viewportX, viewportY);
}

Renderer::~Renderer()
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}
}

void Renderer::putPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewportWidth) return;
	if (j < 0) return; if (j >= viewportHeight) return;
	colorBuffer[INDEX(viewportWidth, i, j, 0)] = color.x;
	colorBuffer[INDEX(viewportWidth, i, j, 1)] = color.y;
	colorBuffer[INDEX(viewportWidth, i, j, 2)] = color.z;
}

/**
 * Draws a line using the (basic) Bresenham Algorithm.
 */
void Renderer::DrawLine(const Line& line, const glm::vec4& color)
{

	float ax = line.GetPointA().x;
	float ay = line.GetPointA().y;
	float bx = line.GetPointB().x;
	float by = line.GetPointB().y;	

	bool aOver1 = line.GetInclination() > 1;
	if (aOver1)
	{
		float tmp = ax;
		ax = ay;
		ay = tmp;

		tmp = bx;
		bx = by;
		by = tmp;
	}

	if (ax > bx)
	{
		float tmp = ax;
		ax = bx;
		bx = tmp;

		tmp = ay;
		ay = by;
		by = tmp;
	}

	//Calculate distance from line
	float dp = bx - ax;
	float dq = abs(by - ay);

	float error = dp / 2.0f;
	
	int updown = (ay < by) ? 1 : -1;
	int y = ay;

	for (int x = ax; x < bx; x++)
	{
		if (aOver1)
		{
			putPixel(y, x, color);
		}
		else
		{
			putPixel(x, y, color);
		}

		error -= dq;
		if (error < 0)
		{
			y += updown;
			error += dp;
		}
	}
}

void Renderer::DrawTriangle(std::vector<glm::vec3>& vertices, const glm::vec4& color)
{
	DrawLine(Line::Line(vertices[0], vertices[1]), color);
	DrawLine(Line::Line(vertices[1], vertices[2]), color);
	DrawLine(Line::Line(vertices[2], vertices[0]), color);	
}
void Renderer::DrawNormals(const glm::vec3& faceCenter, const glm::vec3& normal, const glm::vec4& color, Camera & camera)
{
	DrawLine(Line::Line(faceCenter, normal), color);
}
void Renderer::createBuffers(int viewportWidth, int viewportHeight)
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}

	colorBuffer = new float[3 * viewportWidth * viewportHeight];
	for (int x = 0; x < viewportWidth; x++)
	{
		for (int y = 0; y < viewportHeight; y++)
		{
			putPixel(x, y, glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewportWidth; i++)
	{
		for (int j = 0; j < viewportHeight; j++)
		{
			putPixel(i, j, color);
		}
	}
}

void Renderer::SetViewport(int viewportWidth, int viewportHeight, int viewportX, int viewportY)
{
	this->viewportX = viewportX;
	this->viewportY = viewportY;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	createBuffers(viewportWidth, viewportHeight);
	createOpenGLBuffer();
}

void Renderer::Render(Scene & scene)
{
	Camera activeCamera = scene.GetActiveCamera();
	
	auto models = scene.GetAllModels();
	
	for (auto model : models)
	{
		for (auto face : model->GetAllFaces())
		{
			std::vector<int> vertices = face.GetVertexIndices();
			DrawTriangle(Utils::TriangleFromVertexIndices(vertices, *model), model->GetColor()
			);			
		}
		if (scene.settings.showBoundingBox)
		{
			DrawBoundingBox(*model, activeCamera);
		}
		
		
	}
	if (scene.settings.showNormals)
	{
		for(auto face : models[scene.GetActiveModelIndex()]->GetAllFaces())
			DrawNormals(face.getCenter(),face.getNorm(), models[scene.GetActiveModelIndex()]->GetNormColor(), activeCamera);
	}
	auto cameras = scene.GetAllCameras();
	for (auto camera : cameras)
	{
		for (auto face : camera.GetAllFaces())
		{
			std::vector<int> vertices = face.GetVertexIndices();
			DrawTriangle(Utils::TriangleFromVertexIndices(vertices, camera), camera.GetColor());
		}
		
	}
}

void Renderer::DrawBoundingBox(MeshModel& model, Camera& camera)
{
	// need to redo

	////Lower Square
	//DrawLine(Line::Line(
	//	glm::vec3(model.MinX(), model.MinY(), model.MinZ()),
	//	glm::vec3(model.MaxX(), model.MinY(), model.MinZ())
	//), camera, model.GetColor());
	//DrawLine(Line::Line(
	//	glm::vec3(model.MinX(), model.MinY(), model.MinZ()),
	//	glm::vec3(model.MinX(), model.MinY(), model.MaxZ())
	//), camera, model.GetColor());
	//DrawLine(Line::Line(
	//	glm::vec3(model.MinX(), model.MinY(), model.MaxZ()),
	//	glm::vec3(model.MaxX(), model.MinY(), model.MaxZ())
	//), camera, model.GetColor());
	//DrawLine(Line::Line(
	//	glm::vec3(model.MaxX(), model.MinY(), model.MaxZ()),
	//	glm::vec3(model.MaxX(), model.MinY(), model.MinZ())
	//), camera, model.GetColor());

	////Upper Square
	//DrawLine(Line::Line(
	//	glm::vec3(model.MinX(), model.MaxY(), model.MinZ()),
	//	glm::vec3(model.MaxX(), model.MaxY(), model.MinZ())
	//), camera, model.GetColor());
	//DrawLine(Line::Line(
	//	glm::vec3(model.MinX(), model.MaxY(), model.MinZ()),
	//	glm::vec3(model.MinX(), model.MaxY(), model.MaxZ())
	//), camera, model.GetColor());
	//DrawLine(Line::Line(
	//	glm::vec3(model.MinX(), model.MaxY(), model.MaxZ()),
	//	glm::vec3(model.MaxX(), model.MaxY(), model.MaxZ())
	//), camera, model.GetColor());
	//DrawLine(Line::Line(
	//	glm::vec3(model.MaxX(), model.MaxY(), model.MaxZ()),
	//	glm::vec3(model.MaxX(), model.MaxY(), model.MinZ())
	//), camera, model.GetColor());

	////Pillars

	//DrawLine(Line::Line(
	//	glm::vec3(model.MinX(), model.MinY(), model.MinZ()),
	//	glm::vec3(model.MinX(), model.MaxY(), model.MinZ())
	//), camera, model.GetColor());

	//DrawLine(Line::Line(
	//	glm::vec3(model.MaxX(), model.MinY(), model.MinZ()),
	//	glm::vec3(model.MaxX(), model.MaxY(), model.MinZ())
	//), camera, model.GetColor());

	//DrawLine(Line::Line(
	//	glm::vec3(model.MaxX(), model.MinY(), model.MaxZ()),
	//	glm::vec3(model.MaxX(), model.MaxY(), model.MaxZ())
	//), camera, model.GetColor());

	//DrawLine(Line::Line(
	//	glm::vec3(model.MinX(), model.MinY(), model.MaxZ()),
	//	glm::vec3(model.MinX(), model.MaxY(), model.MaxZ())
	//), camera, model.GetColor());
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::initOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &glScreenTex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &glScreenVtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(glScreenVtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[] = {
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[] = {
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1 };

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc) + sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)sizeof(vtc));

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"), 0);
}

void Renderer::createOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewportWidth, viewportHeight);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewportWidth, viewportHeight, GL_RGB, GL_FLOAT, colorBuffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(glScreenVtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}