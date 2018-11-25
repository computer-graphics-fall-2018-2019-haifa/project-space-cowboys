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

void Camera::SetCameraLookAt(const glm::vec4& eye, const glm::vec4 at, const glm::vec4& up)
{
	glm::vec4 z = glm::normalize(eye - at);
	
	glm::vec3 tempx =  glm::cross(glm::vec3(up.x,up.y,up.z) ,glm::vec3(z.x,z.y,z.z));
	glm::vec4 x = glm::normalize(glm::vec4(tempx.x, tempx.y, tempx.z,0 ));

	glm::vec3 tempy = glm::cross(glm::vec3(z.x, z.y, z.z), glm::vec3(x.x, x.y, x.z));
	glm::vec4 y = glm::normalize(glm::vec4(tempy.x, tempy.y, tempy.z, 0));
	glm::vec4 t = { 0.0f,0.0f,0.0f,1.0f };
	glm::mat4 c = glm::mat4(x, y, z, t);
	this->SetTransformation(c * Utils::TranslationMatrix(glm::vec3 (-eye.x, -eye.y, -eye.z)));
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
