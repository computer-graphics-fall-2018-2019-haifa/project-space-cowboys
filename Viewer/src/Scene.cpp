#include "Scene.h"
#include "MeshModel.h"
#include <string>

using namespace std;

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{
	//Add default camera
	AddCamera(
		Camera::Camera(
			glm::vec4(0, 0, 0, 0),
			glm::vec4(0, 0, 0, 0),
			glm::vec4(0, 0, 0, 0)
		)
	);
}

void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
}

const int Scene::GetModelCount() const
{
	return models.size();
}

void Scene::AddCamera(const Camera& camera)
{
	cameras.push_back(camera);
}

const int Scene::GetCameraCount() const
{
	return cameras.size();
}

void Scene::SetActiveCameraIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < cameras.size())
	{
		activeCameraIndex = index;
	}
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

const Camera Scene::GetCamera(int index) const
{
	return cameras[index];
}

Camera& Scene::GetActiveCamera()
{
	if (cameras.size() > activeCameraIndex)
		return cameras[activeCameraIndex];
}

const Camera Scene::GetDefaultCamera() const
{
	return cameras[0];
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		activeModelIndex = index;
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}

const std::vector<std::shared_ptr<MeshModel>>& Scene::GetAllModels() const
{
	return models;
}