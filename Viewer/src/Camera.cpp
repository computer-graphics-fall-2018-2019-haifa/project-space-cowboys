#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(const glm::vec4 eye, const glm::vec4 at, const glm::vec4 up) : MeshModel(Utils::LoadMeshModel("C:\\Users\\Yanshul\\Documents\\GitHub\\project-space-cowboys\\Data\\camera.obj",true))
{
	this->eye = eye;
	this->at = at;
	this->up = up;
	zoom = 1.0;
	SetTransformation(glm::mat4x4(1.0f));
	SetCameraLookAt(eye, at, up);
	projection = false;
	

	this->left = -1;
	this->right = 1;
	this->bottom = -1;
	this->top = 1;
	this->zNear = 1;
	this->zFar = 200;
	this->fovy = 45;
	this->aspect = 1;
}

Camera::~Camera()
{

}

void Camera::SetTransformation(const glm::mat4x4 & transform)
{
	this->viewTransformation = glm::mat4x4(transform);
}

const glm::mat4x4 Camera::GetTransformation() const
{
	return this->viewTransformation;
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

//as shown in the viewing ppt slide 46
void Camera::SetOrthographicProjection(float l, const float r, const float b, const float t, const float n, const float f)
{
	projectionTransformation = glm::mat4((2.0f / (r - l)), 0.0f, 0.0f, -((r + l) / (r - l)),
										 0.0f, (2.0f / (t - b)), 0.0f, -((t + b) / (t - b)),
										 0.0f, 0.0f, (2.0f /( n - f)), -((f + n) / (f - n)),
										 0.0f, 0.0f, 0.0f, 1.0f);
}

void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspect,
	const float near,
	const float far)
{
	float top = zNear * tan(fovy * M_PI / 180.0);
	
	
	projectionTransformation = glm::mat4(
		 zNear /( top * aspect), 0, 0, 0 ,
		 0, zNear / top, 0, 0 ,
		 0,0, (-zFar + zNear) / (zFar - zNear), -1 ,
		 0, 0, -2 * zFar * zNear / (zFar - zNear), 0);
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

const glm::mat4 Camera::getProjectionTransformation()
{
	return projectionTransformation;
}

void Camera::setProjectionTransformation(int width, int hight)
{
	float l = eye[0] - (width / 2);
	float r = eye[0] + (width / 2);
	float b = eye[1] - (hight / 2);
	float t = eye[1] + (hight / 2);
	float f = 200;
	float n = 1;
	
	
		SetOrthographicProjection(l,r,b,t,n,f);
	
}
