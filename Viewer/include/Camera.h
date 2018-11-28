#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "MeshModel.h"
#include "Global.h"

/*
 * Camera class. This class takes care of all the camera transformations and manipulations.
 *
 * Implementation suggestion:
 * --------------------------
 * Make the Camera class be a subclass of MeshModel, so you can easily and elegantly render 
 * the cameras you have added to the scene.
 */
class Camera :public MeshModel
{
private:
	glm::mat4x4 viewTransformation;
	glm::mat4x4 projectionTransformation;
	float zoom;
	glm::vec4 eye;
	glm::vec4 at;
	glm::vec4 up;

public:
	bool projection;
	Camera(const glm::vec4 eye, const glm::vec4 at, const glm::vec4 up);
	~Camera();

	void SetTransformation(const glm::mat4x4& transform);
	const glm::mat4x4 GetTransformation() const;

	void SetCameraLookAt(const glm::vec4& eye, const glm::vec4 at, const glm::vec4& up);

	void SetOrthographicProjection(float l, const float r, const float b, const float t, const float n, const float f);


	void SetPerspectiveProjection(const float l, const float r, const float b, const float t,
									const float n, const float f);
	
	void SetZoom(const float zoom);

	const float getZoom();

	void Translate(glm::vec3 translation);
	const glm::mat4 getProjectionTransformation();
	void setProjectionTransformation(int width,int hight);
};
