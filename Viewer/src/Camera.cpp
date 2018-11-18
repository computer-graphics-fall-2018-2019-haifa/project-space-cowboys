#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) : MeshModel(Utils::LoadMeshModel("C:\\Users\\Yanshul\\Documents\\GitHub\\project-space-cowboys\\Data\\camera.obj",true))
{
	zoom = 1.0;
	SetTransformation(glm::mat4x4(1.0f));
	SetCameraLookAt(eye, at, up);
}

Camera::~Camera()
{

}

void Camera::SetTransformation(const glm::mat4x4 & transform)
{
	viewTransformation = glm::mat4x4(transform);
}

const glm::mat4x4 Camera::GetTransformation() const
{
	return viewTransformation;
}

void Camera::SetCameraLookAt(const glm::vec3& eye,
	const glm::vec3& at,
	const glm::vec3& up)
{
	auto z = glm::normalize(eye - at);
	auto x = glm::normalize(cross(up, z));
	auto y = glm::normalize(cross(x, z));
	glm::mat4x4 t = Utils::TranslationMatrix(eye);
	this->SetTransformation(t);
}

void Camera::SetOrthographicProjection(
	const float height,
	const float aspectRatio,
	const float near,
	const float far)
{

}

void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{

}

void Camera::SetFrustumProjection(
	const float fovy,
	const float aspect,
	const float near,
	const float far)
{

}

void Camera::SetZoom(const float zoom)
{
	this->zoom = zoom;
}

const float Camera::getZoom()
{
	return zoom;
}

void Camera::Translate(glm::vec3 translation)
{	
	glm::mat4x4 transmat = Utils::TranslationMatrix(translation);
	SetTransformation(GetTransformation() * transmat);	
}
