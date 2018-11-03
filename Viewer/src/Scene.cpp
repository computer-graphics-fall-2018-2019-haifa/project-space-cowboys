#include "Scene.h"
#include "MeshModel.h"
#include <string>

using namespace std;

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

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

const std::vector<std::string> Scene::getModelsNames() const
{
	 std::vector<std::string> names;
	for (size_t i = 0; i < models.size; i++)
	{
		names.push_back(models[i]->GetModelName());
	}

	return names;
}
